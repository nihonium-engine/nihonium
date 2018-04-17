#ifndef NH_SCREEN_GLFW_H
#define NH_SCREEN_GLFW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base.hpp"

namespace nh {

class GLFWScreen : public BaseScreen {

  public:
  void initialise();
  void uninitialise();

  void update();

  private:
  GLFWwindow* window;

   
};
  
}

#endif