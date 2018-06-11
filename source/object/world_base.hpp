#ifndef NH_WORLD_BASE_H
#define NH_WORLD_BASE_H

namespace nh {

class world_base_t {

  public:

  virtual void update(double delta_time) = 0;
  virtual void draw() = 0;

};

}

#endif
