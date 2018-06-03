#ifndef NH_SHADER_GL_H
#define NH_SHADER_GL_H

#include "../../external/glad/glad.h"

#include "shader_base.hpp"

namespace nh {

class shader_gl_t : public shader_base_t {

  public:
  shader_gl_t(file_base_t* x, file_base_t* y) : shader_base_t(x, y) {}

  void initialise(logger_t* logger);

  GLuint program;

};

}

#endif
