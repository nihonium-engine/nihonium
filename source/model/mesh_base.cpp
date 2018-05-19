#include "mesh_base.hpp"

namespace nh {

bool operator<(const mesh_vertex_indices_t& a, const mesh_vertex_indices_t& b) {
  (void)a; (void)b;
  return true;
}
            
}
