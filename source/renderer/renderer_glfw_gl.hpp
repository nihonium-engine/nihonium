#ifndef NH_RENDERER_GLFW_GL_H
#define NH_RENDERER_GLFW_GL_H

#include "../../external/hmm/HandmadeMath.h"

#include "../../external/glad/glad.h"
#include "../../external/glfw/glfw3.h"

#include "../model/mesh_gl.hpp"
#include "../shader/shader_gl.hpp"

#include "renderer_base.hpp"

namespace nh {

class renderer_glfw_gl_t : public renderer_base_t {

  public:
  renderer_glfw_gl_t();
  ~renderer_glfw_gl_t();

  void frame_start();

  void render();

  private:
  GLFWwindow* window;

};

}

#endif
