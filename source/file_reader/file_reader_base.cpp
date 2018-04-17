#include "file_reader_base.hpp"

namespace nh {

uint8_t BaseFileReader::read_uint8() {

  uint8_t destination;
  this->read_bytes(1, (uint8_t*)&destination);

  return destination;
}

uint32_t BaseFileReader::read_uint32() {

  uint32_t destination;
  this->read_bytes(4, (uint8_t*)&destination);

  return destination;
}

uint64_t BaseFileReader::read_uint64() {

  uint64_t destination;
  this->read_bytes(8, (uint8_t*)&destination);

  return destination;
}

}