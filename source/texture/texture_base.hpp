#ifndef NH_TEXTURE_BASE_H
#define NH_TEXTURE_BASE_H

#include <cstddef>
#include <cstdint>

namespace nh {

class texture_base_t {

  public:
  size_t width, height;
  uint8_t* data;

};  

}

#endif
