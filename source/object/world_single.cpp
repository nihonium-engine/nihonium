#include "world_single.hpp"

namespace nh {

void world_single_t::update(double delta_time) {
  for (auto i = this->objects.begin(); i != this->objects.end(); i++) {
    (*i)->update(delta_time);
  }
}

void world_single_t::draw() {
  for (auto i = this->objects.begin(); i != this->objects.end(); i++) {
    (*i)->draw();
  }
}

}
