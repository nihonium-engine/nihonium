#include "mount_base.hpp"

namespace nh {

uint16_t file_base_t::read_uint16() {
  uint16_t out = 0;
  this->read(sizeof(uint16_t), (uint8_t*)&out);
  return out;
}

uint32_t file_base_t::read_uint32() {
  uint32_t out = 0;
  this->read(sizeof(uint32_t), (uint8_t*)&out);
  return out; 
}

uint64_t file_base_t::read_uint64() {
  uint64_t out = 0;
  this->read(sizeof(uint64_t), (uint8_t*)&out);
  return out; 
}

}
