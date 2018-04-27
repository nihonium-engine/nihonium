#include "mesh_gl.hpp"

namespace nh {

BaseMesh* GLMeshFactory::create_mesh(BaseFileReader* reader) {

  GLMesh* mesh = new GLMesh();

  uint8_t header[4];
  reader->read_bytes(4, header);

  if (memcmp(header, "NMDL", 4) != 0) {
    throw std::exception();
  }

  uint32_t version = reader->read_uint32();

  if (version != 1) {
    throw std::exception();
  }

  uint32_t num_meshes = reader->read_uint32();

  for (uint32_t i = 0; i < num_meshes; i++) {

    uint32_t mesh_name_length = reader->read_uint32();

    uint32_t num_positions = reader->read_uint32();
    uint32_t num_normals = reader->read_uint32();
    uint32_t num_albedo_uvs = reader->read_uint32();
    uint32_t num_normal_uvs = reader->read_uint32();
    uint32_t num_metallic_uvs = reader->read_uint32();
    uint32_t num_roughness_uvs = reader->read_uint32();
    uint32_t num_ao_uvs = reader->read_uint32();
    uint32_t num_faces = reader->read_uint32();

    char* mesh_name_c_str = new char[mesh_name_length];
    reader->read_bytes(mesh_name_length, (uint8_t*)mesh_name_c_str);
    mesh->name = std::string(mesh_name_c_str);

    std::map<GLMeshIndex, GLuint> indices;

    NHMVec3* position_data = new NHMVec3[num_positions];
    reader->read_bytes(num_positions * 3 * sizeof(NHMFloat), (uint8_t*)position_data);

    NHMVec3* normal_data = new NHMVec3[num_normals];
    reader->read_bytes(num_normals * 3 * sizeof(NHMFloat), (uint8_t*)normal_data);

    NHMVec2* albedo_uv_data = new NHMVec2[num_albedo_uvs];
    reader->read_bytes(num_albedo_uvs * 2 * sizeof(NHMFloat), (uint8_t*)albedo_uv_data);

    NHMVec2* normal_uv_data = new NHMVec2[num_normal_uvs];
    reader->read_bytes(num_normal_uvs * 2 * sizeof(NHMFloat), (uint8_t*)normal_uv_data);

    NHMVec2* metallic_uv_data = new NHMVec2[num_metallic_uvs];
    reader->read_bytes(num_metallic_uvs * 2 * sizeof(NHMFloat), (uint8_t*)metallic_uv_data);

    NHMVec2* roughness_uv_data = new NHMVec2[num_roughness_uvs];
    reader->read_bytes(num_roughness_uvs * 2 * sizeof(NHMFloat), (uint8_t*)roughness_uv_data);

    NHMVec2* ao_uv_data = new NHMVec2[num_ao_uvs];
    reader->read_bytes(num_ao_uvs * 2 * sizeof(NHMFloat), (uint8_t*)ao_uv_data);

    uint32_t* faces = new uint32_t[num_faces * 7 * 3];
    reader->read_bytes(num_faces * 7 * 3 * sizeof(uint32_t), (uint8_t*)faces);

    for (uint32_t i = 0; i < num_faces * 7 * 3; i += 7 * 3) {
      uint32_t position_index = faces[i];
      uint32_t normal_index = faces[i + 1];
      uint32_t albedo_uv_index = faces[i + 2];
      uint32_t normal_uv_index = faces[i + 3];
      uint32_t metallic_uv_index = faces[i + 4];
      uint32_t roughness_uv_index = faces[i + 5];
      uint32_t ao_uv_index = faces[i + 6];

      GLMeshIndex index = {
        position_index,
        normal_index,
        albedo_uv_index,
        normal_uv_index,
        metallic_uv_index,
        roughness_uv_index,
        ao_uv_index
      };

      try {
        mesh->indices.push_back(indices.at(index));
      } catch (...) {
        GLMeshVertex vertex = {
          position_data[position_index],
          normal_data[normal_index],
          albedo_uv_data[albedo_uv_index],
          normal_uv_data[normal_uv_index],
          metallic_uv_data[metallic_uv_index],
          roughness_uv_data[roughness_uv_index],
          ao_uv_data[ao_uv_index]
        };

        mesh->vertices.push_back(vertex);

        mesh->indices.push_back(mesh->vertices.size() - 1);
        indices[index] = mesh->vertices.size() - 1;

      }
    }
  }

  return static_cast<BaseMesh*>(mesh);

}

}