#ifndef NH_SHADER_GL_H
#define NH_SHADER_GL_H

#include "../../include/glad/glad.h"

#include "shader_base.hpp"

namespace nh {

class shader_gl_t : public shader_base_t {

  public:
  shader_gl_t(file_reader_base_t* x, file_reader_base_t* y) : shader_base_t(x, y) {}

  void initialise();

  GLuint program;

};

}

#endif
