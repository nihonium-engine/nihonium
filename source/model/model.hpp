#ifndef NH_MODEL_H
#define NH_MODEL_H

#include <string>
#include <map>

#include "../filesystem/mount_base.hpp"
#include "../material/material.hpp"
#include "mesh_base.hpp"

namespace nh {

class model_t {

  public:

  std::map<std::string, mesh_base_t*> meshes;
  std::map<std::string, material_t*> materials;

};

class model_factory_base_t {
  public:
  virtual model_t* load_model(file_base_t* reader) = 0;
};

template <typename T> class model_factory_t : public model_factory_base_t {

  public:

  model_t* load_model(file_base_t* reader) {
    uint8_t header[4];
    reader->read(4, header);

    if (memcmp(header, "NMDL", 4) != 0) {
      throw std::exception();
    }

    uint32_t version = reader->read_uint32();

    if (version != 1) {
      throw std::exception();
    }

    model_t* model = new model_t();

    uint32_t num_meshes = reader->read_uint32();

    for (uint32_t i = 0; i < num_meshes; i++) {

      mesh_base_t* mesh = new T();

      // Metadata
      uint8_t metadata[4];
      reader->read(4, metadata);

      // Name length
      uint32_t name_length = reader->read_uint32();

      // Default material path length
      uint32_t default_material_path_length = reader->read_uint32();

      // Number of vertices
      uint32_t num_vertices = reader->read_uint32();

      // Number of faces
      uint32_t num_faces = reader->read_uint32();

      // Name
      char* name_c = new char[name_length];
      reader->read(name_length, (uint8_t*)name_c);
      std::string name = std::string(name_c);
      delete [] name_c;

      // Default material path
      char* default_material_path_c = new char[default_material_path_length];
      reader->read(default_material_path_length, (uint8_t*)default_material_path_c);
      std::string default_material_path = std::string(default_material_path_c);
      delete [] default_material_path_c;

      // Vertices
      float* mesh_data = new float[num_vertices * 8];
      reader->read(num_vertices * 8 * sizeof(float), (uint8_t*)mesh_data);

      // Faces
      uint16_t* faces = new uint16_t[num_faces * 3];
      reader->read(num_faces * 3 * sizeof(uint16_t), (uint8_t*)faces);

      for (uint32_t i = 0; i < num_vertices * 8; i += 8) {
        mesh_vertex_t vertex = {
          mesh_data[i + 0],
          mesh_data[i + 1],
          mesh_data[i + 2],

          mesh_data[i + 3],
          mesh_data[i + 4],
          mesh_data[i + 5],

          mesh_data[i + 6],
          mesh_data[i + 7]
        };
        mesh->vertices.push_back(vertex);
      }

      for (uint32_t i = 0; i < num_faces * 3; i++) {
        mesh->indices.push_back(faces[i]);
      }

      delete [] mesh_data;
      delete [] faces;

      mesh->initialise();
      model->meshes[name] = mesh;
    }

    return model;

  }

};

extern model_factory_base_t* global_model_factory;

}

#endif
