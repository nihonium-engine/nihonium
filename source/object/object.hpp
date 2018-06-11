#ifndef NH_OBJECT_H
#define NH_OBJECT_H

#include <cstdio>
#include <vector>

namespace nh {

class object_t {

  public:

  object_t* parent;
  std::vector<object_t*> children;

  void update(double delta_time);
  void draw();

};

}

#endif
