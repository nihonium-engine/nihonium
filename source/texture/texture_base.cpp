#include "texture_base.hpp"

namespace nh {

static int read(void* user, char* data, int size) {
  file_reader_base_t* reader = (file_reader_base_t*)user;
  return reader->read_bytes(size, (uint8_t*)data);
}

static void skip(void* user, int n) {
  file_reader_base_t* reader = (file_reader_base_t*)user;
  if (n > 0) { 
    reader->set_pos_forwards(n);
  } else {
    reader->set_pos_backwards(-n);
  }
}

static int eof(void* user) {
  file_reader_base_t* reader = (file_reader_base_t*)user;
  return reader->eof;
}

texture_base_t::texture_base_t(file_reader_base_t* reader) {

  stbi_io_callbacks callbacks = {read, skip, eof};

  stbi_load_from_callbacks(&callbacks, reader, &this->width, &this->height, &this->channels, 4);

}

}
