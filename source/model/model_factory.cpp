#include "model_factory.hpp"

namespace nh {
/*
template <typename T> model_t* model_factory_t::load_model(file_reader_base_t* reader) {
      
  uint8_t header[4];
  reader->read_bytes(4, header);

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

    uint8_t metadata[8];
    reader->read_bytes(8, metadata);
    uint32_t mesh_name_length = reader->read_uint32();
    uint32_t mesh_material_length = reader->read_uint32();
    uint32_t num_positions = reader->read_uint32();
    uint32_t num_normals = reader->read_uint32();
    uint32_t num_uvs = reader->read_uint32();
    uint32_t num_faces = reader->read_uint32();

    char* mesh_name_c_str = new char[mesh_name_length];
    reader->read_bytes(mesh_name_length, (uint8_t*)mesh_name_c_str);
    mesh->name = std::string(mesh_name_c_str);
    delete mesh_name_c_str;

    nhm_vec3_t* position_data = new nhm_vec3_t[num_positions];
    reader->read_bytes(num_positions * 3 * sizeof(nhm_float_t), (uint8_t*)position_data);

    nhm_vec3_t* normal_data = new nhm_vec3_t[num_normals];
    reader->read_bytes(num_normals * 3 * sizeof(nhm_float_t), (uint8_t*)normal_data);

    nhm_vec2_t* uv_data = new nhm_vec2_t[num_uvs];
    reader->read_bytes(num_uvs * 2 * sizeof(nhm_float_t), (uint8_t*)uv_data);

    uint16_t* faces = new uint16_t[num_faces * 3 * 3];
    reader->read_bytes(num_faces * 3 * 3 * sizeof(uint16_t), (uint8_t*)faces);

    std::map<mesh_vertex_indices_t, uint16_t> indices;

    for (uint32_t i = 0; i < num_faces * 3 * 3; i += 3) {
      uint16_t position_index = faces[i];
      uint16_t normal_index = faces[i + 1];
      uint16_t uv_index = faces[i + 2];

      mesh_vertex_indices_t index = {
        position_index,
        normal_index,
        uv_index
      };

      try {
        mesh->indices.push_back(indices.at(index));
      } catch (...) {
        mesh_vertex_t vertex = {
          position_data[position_index],
          normal_data[normal_index],
          uv_data[uv_index],
        };

        mesh->vertices.push_back(vertex);

        mesh->indices.push_back(mesh->vertices.size() - 1);
        indices[index] = mesh->vertices.size() - 1;

      }

    }
    model->meshes.push_back(mesh);
    mesh->initialise();
  }

}
*/
}
