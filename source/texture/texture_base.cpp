#include "texture_base.hpp"

namespace nh {

static int read(void* user, char* data, int size) {
  file_base_t* reader = (file_base_t*)user;
  return reader->read(size, (uint8_t*)data);
}

static void skip(void* user, int n) {
  file_base_t* reader = (file_base_t*)user;
  reader->seek_current(n);
}

static int eof(void* user) {
  file_base_t* reader = (file_base_t*)user;
  return reader->eof();
}

texture_base_t::texture_base_t(file_base_t* reader) {

  stbi_io_callbacks callbacks = {read, skip, eof};

  this->data = stbi_load_from_callbacks(&callbacks, reader, &this->width, &this->height, &this->channels, 4);

}

texture_factory_base_t* global_texture_factory;

}
