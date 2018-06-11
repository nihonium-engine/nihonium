#ifndef NH_WORLD_SINGLE_H
#define NH_WORLD_SINGLE_H

#include <vector>

#include "object.hpp"
#include "world_base.hpp"

namespace nh {

class world_single_t : public world_base_t {

  public:

  std::vector<object_t*> objects;

  void update(double delta_time) override;
  void draw() override;

};

}

#endif
