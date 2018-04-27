#ifndef NH_MESH_GL_H
#define NH_MESH_GL_H

#include <cstring>

#include <map>
#include <vector>

#include "../../include/glad/glad.h"

#include "mesh_base.hpp"

namespace nh {

struct GLMeshVertex {
  NHMVec3 position;
  NHMVec3 normal;
  NHMVec2 albedo_uv;
  NHMVec2 normal_uv;
  NHMVec2 metallic_uv;
  NHMVec2 roughness_uv;
  NHMVec2 ao_uv;
};

struct GLMeshIndex {
  uint32_t position_index;
  uint32_t normal_index;
  uint32_t albedo_uv_index;
  uint32_t normal_uv_index;
  uint32_t metallic_uv_index;
  uint32_t roughness_uv_index;
  uint32_t ao_uv_index;
};

class GLMesh : public BaseMesh {

  public:

  GLuint vao, vbo, ebo;

  std::vector<GLMeshVertex> vertices;
  std::vector<GLuint> indices;
};

class GLMeshFactory : public BaseMeshFactory {

  public:

  virtual BaseMesh* create_mesh(BaseFileReader* reader) = 0;

};
  
}

#endif