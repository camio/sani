#ifndef SANI_INTERACTIVEANIMATION_HPP_
#define SANI_INTERACTIVEANIMATION_HPP_

#include <sani/animation.hpp>
#include <boost/function.hpp>

namespace sani {

struct UserInput;

typedef boost::function<Animation(const sani::UserInput&)> InteractiveAnimation;
}
#endif
