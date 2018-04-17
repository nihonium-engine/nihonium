#ifndef NH_ROLES_SINGLE_H
#define NH_ROLES_SINGLE_H

#include <vector>

#include "base.hpp"

#include "../common/object.hpp"
#include "../screen/base.hpp"

namespace nh {

class SingleRole : public BaseRole {

  public:
  
  void initialise();
  void uninitialise();
  void main_loop();

  private:

  std::vector<nh::Object> object;

  nh::BaseScreen* screen;
  //nh::BaseGraphics* graphics;
  //nh::BaseInput* input;
  //nh::BaseAudio* audio;
  
};

};

#endif