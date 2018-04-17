#ifndef NH_MESH_GL_H
#define NH_MESH_GL_H

#include "../../include/glad/glad.h"

#include "mesh_base.hpp"

namespace nh {

class GLMesh : public BaseMesh {

  public:

  GLint vao, vbo, ebo;

  void generate_buffers();
};

class GLMeshFactory : public BaseMeshFactory {

  public:

  virtual BaseMesh* create_mesh(BaseFileReader* reader) = 0;

};
  
}

#endif