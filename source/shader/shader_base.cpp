#include "shader_base.hpp"

namespace nh {

shader_base_t::shader_base_t(file_base_t* vert_reader, file_base_t* frag_reader) {

  vert_reader->seek_end(0);
  frag_reader->seek_end(0);
  this->vert_source_length = vert_reader->tell();
  this->frag_source_length = frag_reader->tell();

  this->vert_source = new char[this->vert_source_length];
  this->frag_source = new char[this->frag_source_length];

  vert_reader->seek_start(0);
  frag_reader->seek_start(0);

  vert_reader->read(this->vert_source_length, (uint8_t*)vert_source);
  frag_reader->read(this->frag_source_length, (uint8_t*)frag_source);

}

shader_base_t::~shader_base_t() {
  delete vert_source;
  delete frag_source;
}

shader_factory_base_t* global_shader_factory;

}
