#include "renderer_glfw_gl.hpp"

namespace nh {

renderer_glfw_gl_t::renderer_glfw_gl_t() {

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->window = glfwCreateWindow(800, 600, "Nihonium Engine", NULL, NULL);

  if (!window) {
    // TODO: Error.
  }

  glfwMakeContextCurrent(this->window);

  glfwSwapInterval(1);

  gladLoadGL();

  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_BLEND);
  //glEnable(GL_MULTISAMPLE);
  //glEnable(GL_CULL_FACE);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void renderer_glfw_gl_t::frame_start() {
  glfwSwapBuffers(this->window);
  glfwPollEvents();

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

renderer_glfw_gl_t::~renderer_glfw_gl_t() {

  glfwDestroyWindow(window);

  glfwTerminate();

}

}
