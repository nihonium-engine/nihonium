#ifndef NH_INPUT_GLFW_H
#define NH_INPUT_GLFW_H

#include "input_base.hpp"
#include "../renderer/renderer_glfw_gl.hpp"

namespace nh {

class input_glfw_t : public input_base_t {

  public:

  input_glfw_t(renderer_glfw_gl_t* in_renderer) : renderer(in_renderer) {};

  bool is_down(std::string key);

  private:

  renderer_glfw_gl_t* renderer;

};

}

#endif
