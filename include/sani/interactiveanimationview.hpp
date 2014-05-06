#ifndef SANI_INTERACTIVEANIMATIONVIEW_HPP_
#define SANI_INTERACTIVEANIMATIONVIEW_HPP_

//@PURPOSE: Provide a Widget that views 'InteractiveAnimation's
//
//@CLASSES:
//  sani::InteractiveAnimationView: viewer widget for InteractiveAnimations
//
//@SEE_ALSO: sani_interactiveanimation
//
//@DESCRIPTION: This component provides a single class,
// 'InteractiveAnimationView', that is a widget capable of rendering an
// 'InteractiveAnimation'. Mouse and keyboard events are sent to the visible
// animation to provide interactivitity.
//
// The unit of 'time' that is sent to the interactive animations is corresponds
// to actual seconds.
//
// Usage
// -----
// This section illustrates intended use of this component.
//
// Example 1: Visualize a ball that tracks the mouse position
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//
// First, we create a drawing of a ball.
//..
// const sani::Drawing circle =
//     sani::drawEllipse(QPen(), QBrush(Qt::red), QRectF(-0.5, -0.5, 1.0, 1.0));
//..
// Now we define our interactive animation, but first we need a couple helper
// functions.
//..
// qreal pointGetX(const QPointF& p) { return p.x(); }
// qreal pointGetY(const QPointF& p) { return p.y(); }
//..
// Now the animation is declared
//..
// // An interactive animation where 'circle' follows the mouse position
// const sani::InteractiveAnimation circleFollowsMouse =
//     ([circle](const sani::UserInput & userInput)
//          ->sfrp::Behavior<sani::Drawing> {
//       // Get the individual x and y mouse positions
//       const sfrp::Behavior<qreal> xMousePosBeh =
//           sfrp::pmLift(pointGetX, userInput.mousePos);
//       const sfrp::Behavior<qreal> yMousePosBeh =
//           sfrp::pmLift(pointGetY, userInput.mousePos);
//
//       // Convert those positions into a translation behavior
//       const sfrp::Behavior<QTransform> transformBeh = sfrp::pmLift(
//           &QTransform::fromTranslate, xMousePosBeh, yMousePosBeh);
//
//       // Translate a constant circle by 'transformBeh'
//       const sfrp::Behavior<sani::Drawing> movedDrawing = sfrp::pmLift(
//           sani::transformDrawing, transformBeh, sfrp::pmConst(circle));
//
//       return movedDrawing;
//     });
//..
// Finally, we view the animation in an 'InteractiveAnimationView'
//..
// sani::InteractiveAnimationView view;
// view.setInteractiveAnimation( circleFollowsMouse );
// view.show();
//..

#include <QGraphicsView>
#include <sani/interactiveanimation.hpp>
#include <memory>

class QTimer;

namespace sani {

// This class implements a 2D display that views 'InteractiveAnimation's.
class InteractiveAnimationView : public QGraphicsView {
  Q_OBJECT
 public:
  // Create an 'InteractiveAnimationView' object with a viewed animation
  // that always shows a blank window and has no reaction to user inputs.
  InteractiveAnimationView();

  ~InteractiveAnimationView();

  // Draw the current frame in the animation using the specified 'painter' and
  // 'rect'.
  void drawBackground(QPainter* painter, const QRectF& rect) final;

  // Set the visible animation to the specified 'interactiveAnimation'.
  void setInteractiveAnimation(
      const InteractiveAnimation& interactiveAnimation);

  // Notify the current animation that the mouse was moved using the specified
  // 'event' to discover the mouse's position.
  void mouseMoveEvent(QMouseEvent* event) final;

  // Notify the current animation that the mouse was pressed using the specified
  // 'event' to discover which button was used.
  void mousePressEvent(QMouseEvent* event) final;

  // Notify the current animation that the mouse was released using the
  // specified 'event' to discover which button was used.
  void mouseReleaseEvent(QMouseEvent* event) final;

  // Notify the current animation that the keyboard was pressed using the
  // specified 'event' to discover which key was used.
  void keyPressEvent(QKeyEvent* event) final;

  // Notify the current animation that the keyboard was released using the
  // specified 'event' to discover which key was used.
  void keyReleaseEvent(QKeyEvent* event) final;

 protected:
  // Call 'pullNewFrameFromAnimation()'.
  void timerEvent(QTimerEvent *event) final;

 private
Q_SLOTS:

  // Pull a new 'Drawing' from the current interactive animation and set the
  // currently viewed to it.
  void pullNewFrameFromAnimation();

 private:
  struct Impl;
  const std::unique_ptr<Impl> m_impl;
};
}

#endif
