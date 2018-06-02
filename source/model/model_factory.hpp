#ifndef NH_MODEL_FACTORY_H
#define NH_MODEL_FACTORY_H

#include <map>

#include "../filesystem/mount_base.hpp"
#include "model.hpp"

namespace nh {

class model_factory_t {

  public:

  template <typename T> model_t* load_model(file_base_t* reader) {
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
  
      uint8_t metadata[4];
      reader->read(4, metadata);
      uint32_t num_vertices = reader->read_uint32();
      uint32_t num_faces = reader->read_uint32();

      float* mesh_data = new float[num_vertices * 8];
      reader->read(num_vertices * 8 * sizeof(float), (uint8_t*)mesh_data);

      uint16_t* faces = new uint16_t[num_faces * 3];
      reader->read(num_faces * 3 * sizeof(uint16_t), (uint8_t*)faces);

      for (int i = 0; i < num_vertices * 8; i += 8) {
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

      for (int i = 0; i < num_faces * 3; i++) {
        mesh->indices.push_back(faces[i]);
      }

      mesh->initialise();
      model->meshes.push_back(mesh);
    }

    return model;

  }

};

}

#endif
