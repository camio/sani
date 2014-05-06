#include <sani/interactiveanimationview.hpp>

#include <boost/function.hpp>
#include <boost/optional.hpp>
#include <QApplication>
#include <QBasicTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTime>
#include <sani/animation.hpp>
#include <sani/drawing.hpp>
#include <sani/userinput.hpp>
#include <sfrp/util.hpp>  // sfrp::pmTriggerInfStep
#include <iostream>
#include <memory>

namespace sani {

// 17ms ≈ 60Hz
const int frameIntervalMs = 17;

namespace {
// Return an 'int' corresponding to the specified 'button' or '0' if
// 'button' is 'Qt::NoButton' or an unrecognized button.
int intFromMouseButton(const Qt::MouseButton& button) {
  switch (button) {
    case Qt::LeftButton:
      return 1;
    case Qt::RightButton:
      return 2;
    case Qt::MiddleButton:
      return 3;
    case Qt::XButton1:
      return 4;
    case Qt::XButton2:
      return 5;
    default:
      return 0;
  }
}
}

struct InteractiveAnimationView::Impl {

  Impl() : m_nextFrameContents(drawNothing) {}

  QGraphicsScene m_scene;
  QTime m_animationStartTime;
  Drawing m_nextFrameContents;
  boost::optional<Animation> m_opAnimation;
  boost::function<void(const QPointF&)> m_updateMousePos;
  boost::function<void(const int)> m_notifyMousePress;
  boost::function<void(const int)> m_notifyMouseRelease;
  boost::function<void(const int)> m_notifyKeyPress;
  boost::function<void(const int)> m_notifyKeyRelease;
  QBasicTimer m_timer;
};

InteractiveAnimationView::InteractiveAnimationView() : m_impl(new Impl()) {
  setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setScene(&m_impl->m_scene);
  setMouseTracking(true);
  m_impl->m_timer.start(frameIntervalMs, this);
}

InteractiveAnimationView::~InteractiveAnimationView() {}

void InteractiveAnimationView::drawBackground(QPainter* painter,
                                              const QRectF& rect) {
  draw(m_impl->m_nextFrameContents, *painter);
}

void InteractiveAnimationView::setInteractiveAnimation(
    const InteractiveAnimation& interactiveAnimation) {
  sani::UserInput userInput;

  const QPoint curMousePos = mapFromGlobal(QCursor::pos());
  std::tie(userInput.mousePos, m_impl->m_updateMousePos) =
      sfrp::pmTriggerInfStep(rect().contains(curMousePos)
                                 ? mapToScene(curMousePos)
                                 : QPointF(0.0, 0.0));

  std::tie(userInput.mousePress, m_impl->m_notifyMousePress) =
      sfrp::pmTriggerInf<int>();

  std::tie(userInput.mouseRelease, m_impl->m_notifyMouseRelease) =
      sfrp::pmTriggerInf<int>();

  std::tie(userInput.keyRelease, m_impl->m_notifyKeyRelease) =
      sfrp::pmTriggerInf<int>();

  std::tie(userInput.keyPress, m_impl->m_notifyKeyPress) =
      sfrp::pmTriggerInf<int>();

  m_impl->m_opAnimation = interactiveAnimation(userInput);
  m_impl->m_animationStartTime.restart();
}

void InteractiveAnimationView::mousePressEvent(QMouseEvent* event) {
  if (m_impl->m_notifyMousePress)
    m_impl->m_notifyMousePress(intFromMouseButton(event->button()));
}

void InteractiveAnimationView::mouseReleaseEvent(QMouseEvent* event) {
  if (m_impl->m_notifyMouseRelease)
    m_impl->m_notifyMouseRelease(intFromMouseButton(event->button()));
}

void InteractiveAnimationView::keyPressEvent(QKeyEvent* e) {
  if (m_impl->m_notifyKeyPress)
    m_impl->m_notifyKeyPress(e->key());
}

void InteractiveAnimationView::keyReleaseEvent(QKeyEvent* e) {
  if (m_impl->m_notifyKeyRelease)
    m_impl->m_notifyKeyRelease(e->key());
}
void InteractiveAnimationView::timerEvent(QTimerEvent *event)
{
  pullNewFrameFromAnimation();
}

void InteractiveAnimationView::pullNewFrameFromAnimation() {
  QTime framePullStart;
  framePullStart.start();
  if (m_impl->m_opAnimation) {
    const int curTimeMilliseconds = m_impl->m_animationStartTime.elapsed();

    const double curTimeSeconds = curTimeMilliseconds / 1000.0;

    const boost::optional<sani::Drawing> opDrawing =
        m_impl->m_opAnimation->pull(curTimeSeconds);

    if (opDrawing) {
      m_impl->m_nextFrameContents = *opDrawing;
    } else {
      m_impl->m_opAnimation = boost::none;
      m_impl->m_updateMousePos.clear();
    }
    m_impl->m_scene.invalidate();
  }
  const int framePullDuration = framePullStart.elapsed();
  // Process pending events to ensure that the timer's events don't monopolize
  // the event buffer and cause weird behavior, such as mouse freezing. See
  // issue 216696 for more information.
  qApp->processEvents();
}

void InteractiveAnimationView::mouseMoveEvent(QMouseEvent* e) {
  const QPointF p = mapToScene(e->pos());
  if (m_impl->m_updateMousePos)
    m_impl->m_updateMousePos(p);
}
}
