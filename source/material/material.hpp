#ifndef NH_MATERIAL_H
#define NH_MATERIAL_H

#include "../../external/rapidjson/document.h"

#include "../filesystem/filesystem.hpp"

#include "../shader/shader_base.hpp"
#include "../texture/texture_base.hpp"

#include <map>
#include <string>

namespace nh {

class invalid_material_exception : std::exception {
  public:
  invalid_material_exception(std::string e) : std::exception(), message(e) {}
  
  const char* what() {
    return message.c_str();
  }

  private:
  std::string message;
};

struct material_value_t {
  bool is_map;
  texture_base_t* map;
  float* single;
  size_t num_single_values;
};

class material_t {

  public:

  shader_base_t* shader;

  std::map<std::string, material_value_t> values;

};

material_t* load_material(file_base_t* file);

}

#endif
