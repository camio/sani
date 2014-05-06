#include <sani/userinput.hpp>

#include <boost/lexical_cast.hpp>
#include <QPointF>
#include <sfrp/eventmap.hpp>

namespace sani {

UserInput::UserInput() {}

UserInput::UserInput(sfrp::Behavior<QPointF> mousePos_,
                     sfrp::Behavior<boost::optional<int>> mousePress_,
                     sfrp::Behavior<boost::optional<int>> mouseRelease_,
                     sfrp::Behavior<boost::optional<int>> keyPress_,
                     sfrp::Behavior<boost::optional<int>> keyRelease_)
    : mousePos(std::move(mousePos_)),
      mousePress(std::move(mousePress_)),
      keyPress(std::move(keyPress_)),
      keyRelease(std::move(keyRelease_)) {}
}

// Used only for compilation testing
static std::string combine(const int& mouseButton, const QPointF& mousePos) {
  return boost::lexical_cast<std::string>(mousePos.x()) + " " +
         boost::lexical_cast<std::string>(mousePos.y());
}

// Used only for compilation testing
static sfrp::Behavior<boost::optional<std::string>> mousePressPositions(
    const sani::UserInput& userInput) {
  return sfrp::EventMap()(combine, userInput.mousePress, userInput.mousePos);
}
