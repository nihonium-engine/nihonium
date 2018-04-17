#ifndef NH_MESH_BASE_H
#define NH_MESH_BASE_H

#include <cstddef>
#include <cstdint>

#include "../../external/nhmaths/nhmaths.h"

#include "../file_reader/file_reader_base.hpp"

namespace nh {

class BaseMesh {

  NHMVec3* vertex_data;
  size_t num_vertices;

  NHMVec3* normal_data;
  size_t num_normals;

  NHMVec2* uv_data;
  size_t size_uvs;
  
  int* index_data;
  size_t num_indices;
};

class BaseMeshFactory {

  public:

  virtual BaseMesh* create_mesh(BaseFileReader* reader) = 0;

};

}

#endif