#ifndef NH_MESH_BASE_H
#define NH_MESH_BASE_H

#include <cstddef>
#include <cstdint>
#include <cstring>

#include <vector>

#include "../../external/nhmaths/nhmaths.h"

#include "../file_reader/file_reader_base.hpp"

namespace nh {

struct mesh_vertex_indices_t {
  uint32_t position_index;
  uint32_t normal_index;
  uint32_t uv_index;
};

bool operator<(const mesh_vertex_indices_t& a, const mesh_vertex_indices_t& b);

struct mesh_vertex_t {
  nhm_vec3_t position;
  nhm_vec3_t normal;
  nhm_vec2_t uv;
};

class mesh_base_t {

  public:

  std::string name;

  std::vector<mesh_vertex_t> vertices;
  std::vector<uint32_t> indices;

  virtual void initialise() = 0;

};

}

#endif
