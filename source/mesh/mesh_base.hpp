#ifndef NH_MESH_BASE_H
#define NH_MESH_BASE_H

#include <cstddef>
#include <cstdint>

#include "../../external/nhmaths/nhmaths.h"

#include "../file_reader/file_reader_base.hpp"

namespace nh {

class BaseMesh {

  public:

  std::string name;

};

class BaseMeshFactory {

  public:

  virtual BaseMesh* create_mesh(BaseFileReader* reader) = 0;

};

}

#endif