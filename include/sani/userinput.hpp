//@PURPOSE: Provide a class representing common frp user inputs
//
//@CLASSES:
//  sani::UserInput: A collection of behaviors for user input
//
//@DESCRIPTION: This component provides a struct that collects common user input
// behaviors for use in frp applications.
//
// Usage
// -----
// This section illustrates intended use of this component.
//
// Example 1: Use of 'UserInput' in a frp application
// - - - - - - - - - - - - - - - - - - - - - - - - -
// In this example, we implement a function that takes 'UserInput' as a
// parameter and returns a 'std::string' behavior representing the mouse
// position at every click.
//..
// // Return a string representation of the specified 'mousePos'. Note that
// // the specified 'mouseButton' is completely unused. It is only there
// // so it can be used with 'pmEvLift' below.
// std::string combine( const int & mouseButton, const QPointF & mousePos )
// {
//   return boost::lexical_cast<std::string>(mousePos.x()) + " " +
//          boost::lexical_cast<std::string>(mousePos.y());
// }
// 
// sfrp::Behavior<boost::optional<std::string>> mousePressPositions(
//     const sani::UserInput& userInput)
// {
//   return sfrp::pmEvLift(combine, userInput.mousePress, userInput.mousePos);
// }
//..

#ifndef SANI_USERINPUT_HPP_
#define SANI_USERINPUT_HPP_

#include <boost/optional.hpp>
#include <sfrp/behavior.hpp>

class QPointF;

namespace sani {

// This class implements a collection of behaviors that represent common user
// input behaviors.
struct UserInput {
  // Create a 'UserInput' object that has no value at any time fore each of its
  // behaviors.
  UserInput();

  // Create a 'UserInput' object with the specified 'mousePos', 'mousePress',
  // 'mouseRelease', 'keyPress', and 'keyRelease' behaviors.
  UserInput(sfrp::Behavior<QPointF> mousePos,
            sfrp::Behavior<boost::optional<int>> mousePress,
            sfrp::Behavior<boost::optional<int>> mouseRelease,
            sfrp::Behavior<boost::optional<int>> keyPress,
            sfrp::Behavior<boost::optional<int>> keyRelease);

  sfrp::Behavior<QPointF> mousePos;  // The position of a mouse

  sfrp::Behavior<boost::optional<int>> mousePress;  // Instances of when the
                                                    // mouse is pressed. The
                                                    // 'int' indicates which
                                                    // button was pressed.

  sfrp::Behavior<boost::optional<int>> mouseRelease;  // Instances of when the
                                                      // mouse is released. The
                                                      // 'int' indicates which
                                                      // button was pressed.

  sfrp::Behavior<boost::optional<int>> keyPress;  // Instances of when a key on
                                                  // a keyboard is pressed. The
                                                  // 'int' corresponds to the
                                                  // key code.

  sfrp::Behavior<boost::optional<int>> keyRelease;  // Instances of when a key
                                                    // on a keyboard is
                                                    // released. The 'int'
                                                    // corresponds to the key
                                                    // code.
};
}
#endif
