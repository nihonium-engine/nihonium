#ifndef NH_TEXTURE_BASE_H
#define NH_TEXTURE_BASE_H

#include <cstddef>
#include <cstdint>

#include "../../external/stb_image/stb_image.h"

#include "../filesystem/mount_base.hpp"

namespace nh {

class texture_base_t {

  public:
  texture_base_t(file_base_t* reader);

  virtual void initialise() = 0;
  
  int width, height, channels;
  uint8_t* data;

};

class texture_factory_base_t {
  public:
  virtual texture_base_t* load_texture(file_base_t* reader) = 0;
};

template <typename T> class texture_factory_t : public texture_factory_base_t {

  texture_base_t* load_texture(file_base_t* reader) {
    texture_base_t* texture = new T(reader);
    texture->initialise();
    return texture;
  }

};

extern texture_factory_base_t* global_texture_factory;

}

#endif
