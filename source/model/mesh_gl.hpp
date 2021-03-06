#ifndef NH_MESH_GL_H
#define NH_MESH_GL_H

#include "../../external/glad/glad.h"

#include "mesh_base.hpp"

namespace nh {

class mesh_gl_t : public mesh_base_t {

  public:

  GLuint vao, vbo, ebo;

  void initialise();

};

}

#endif
