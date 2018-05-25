#include "shader_base.hpp"

namespace nh {

shader_base_t::shader_base_t(file_reader_base_t* vert_reader, file_reader_base_t* frag_reader) {

  this->vert_source_length = vert_reader->get_length();
  this->frag_source_length = frag_reader->get_length();

  this->vert_source = new char[this->vert_source_length];
  this->frag_source = new char[this->frag_source_length];

  vert_reader->read_bytes(this->vert_source_length, (uint8_t*)vert_source);
  frag_reader->read_bytes(this->frag_source_length, (uint8_t*)frag_source);

}

shader_base_t::~shader_base_t() {
  delete vert_source;
  delete frag_source;
}

}
