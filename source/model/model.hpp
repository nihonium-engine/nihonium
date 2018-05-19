#ifndef NH_MODEL_H
#define NH_MODEL_H

#include <string>
#include <vector>

#include "mesh_base.hpp"

namespace nh {

class model_t {

  public:

  // TODO: Consider switching to multimap.
  std::vector<mesh_base_t*> meshes;

};

}

#endif
