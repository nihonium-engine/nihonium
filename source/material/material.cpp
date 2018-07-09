#include "material.hpp"

namespace nh {

static void validate_parameter(const rapidjson::Value& param) {

  if (!param.IsObject()) {
    throw invalid_material_exception("all values in 'parameters' must be objects");
  }

  if (!param.HasMember("name")) {
    throw invalid_material_exception("parameter was given without a name");
  }

  if (!param.HasMember("type")) {
    throw invalid_material_exception("parameter was given without a type");
  }

  if (!param["name"].IsString()) {
    throw invalid_material_exception("parameter name must be a string");
  }

  if (!param["type"].IsString()) {
    throw invalid_material_exception("parameter type must be a string");
  }

  std::string type = param["type"].GetString();

  if (type == "single") {

    if (!param.HasMember("value")) {
      throw invalid_material_exception("parameter of type 'single' was given without a 'value'");
    }

    if (!param["value"].IsArray()) {
      throw invalid_material_exception("'value' of parameter of type 'single' must be an array");
    }

    const rapidjson::Value& value = param["value"];
  
    for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
      if (!value[i].IsNumber()) {
        throw invalid_material_exception("all components of 'value' of parameter of type 'single' must be numbers");
      }
    }

  } else if (type == "map") {

    if (!param.HasMember("components")) {
      throw invalid_material_exception("parameter of type 'map' was given without a 'components'");
    }

    if (!param.HasMember("path")) {
      throw invalid_material_exception("parameter of type 'map' was given without a 'path'");
    }

    if (!param["components"].IsInt()) {
      throw invalid_material_exception("'components' of parameter of type 'map' must be an integer");
    }

    if (!param["path"].IsString()) {
      throw invalid_material_exception("'path' of parameter of type 'map' must be a string");
    }

  } else {
    throw invalid_material_exception("parameter type must be either 'single' or 'map'");
  }

}

material_t* load_material(file_base_t* file) {

  material_t* material = new material_t();

  file->seek_end(0);
  size_t length = file->tell();

  char* source = new char[length + 1];

  file->seek_start(0);

  file->read(length, (uint8_t*)source);
  source[length] = '\0';

  rapidjson::Document doc;

  doc.Parse(source);

  if (!doc.IsObject()) {
    throw invalid_material_exception("top-level value of material must be an object");
  }

  if (!doc.HasMember("vertex_shader")) {
    throw invalid_material_exception("top-level object must give a value for 'vertex_shader'");
  }

  if (!doc["vertex_shader"].IsString()) {
    throw invalid_material_exception("'vertex_shader' must be a string");
  }

  if (!doc.HasMember("fragment_shader")) {
    throw invalid_material_exception("top-level object must give a value for 'fragment_shader'");
  }

  if (!doc["fragment_shader"].IsString()) {
    throw invalid_material_exception("'fragment_shader' must be a string");
  }

  if (!doc.HasMember("parameters")) {
    throw invalid_material_exception("top-level object must give a value for 'parameters'");
  }

  if (!doc["parameters"].IsArray()) {
    throw invalid_material_exception("'parameters' must be an array");
  }

  const rapidjson::Value& params = doc["parameters"];

  for (rapidjson::SizeType i = 0; i < params.Size(); i++) {
    validate_parameter(params[i]);
  }

  file_base_t* vert_shader = global_filesystem->open_file(doc["vertex_shader"].GetString());
  file_base_t* frag_shader = global_filesystem->open_file(doc["fragment_shader"].GetString());

  material->shader = global_shader_factory->load_shader(vert_shader, frag_shader);

  for (rapidjson::SizeType i = 0; i < params.Size(); i++) {

    material_value_t value;

    const rapidjson::Value& param = params[i];
    if (param["type"].GetString() == std::string("single")) {
      value.is_map = false;
      value.map = nullptr;
      value.single = new float[param["value"].Size()];
      value.num_single_values = param["value"].Size();

      for (rapidjson::SizeType j = 0; j < param["value"].Size(); j++) {
        value.single[j] = param["value"][j].GetFloat();
      }
    } else {
      value.is_map = true;
      value.single = nullptr;
      value.num_single_values = 0;
      file_base_t* file = global_filesystem->open_file(param["path"].GetString());
      value.map = global_texture_factory->load_texture(file);
    }

    material->values[param["name"].GetString()] = value;
  }

  // TODO: Consider moving this further back.
  delete source;

  return material;

}

}
