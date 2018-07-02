#ifndef NH_TEXTURE_GL_H
#define NH_TEXTURE_GL_H

#include "../../external/glad/glad.h"

#include "texture_base.hpp"

namespace nh {

class texture_gl_t : public texture_base_t {

  public:
  texture_gl_t(file_base_t* reader) : texture_base_t(reader) {}
  
  void initialise();

  GLuint texture;

};

}

#endif
