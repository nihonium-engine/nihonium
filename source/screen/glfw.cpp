#include "glfw.hpp"

namespace nh {

void GLFWScreen::initialise() {

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  this->window = glfwCreateWindow(800, 600, "Nihonium Engine", NULL, NULL);

  if (!window) {
    // TODO: Error.
  }

  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

  gladLoadGL();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_CULL_FACE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

 
}

void GLFWScreen::uninitialise() {

  glfwDestroyWindow(window);

  glfwTerminate();

}

void GLFWScreen::update() {

  glfwSwapBuffers(this->window);

  glfwPollEvents();

  glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

}