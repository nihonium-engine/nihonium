#include "mesh_gl.hpp"

namespace nh {

void mesh_gl_t::initialise() {

  glGenVertexArrays(1, &this->vao);

  glGenBuffers(1, &this->vbo);
  glGenBuffers(1, &this->ebo);

  glBindVertexArray(this->vao);

  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(mesh_vertex_t), this->vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(uint32_t), this->indices.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(nhm_float_t) * 8, (GLvoid*)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(nhm_float_t) * 8, (GLvoid*)(sizeof(nhm_float_t) * 3));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(nhm_float_t) * 8, (GLvoid*)(sizeof(nhm_float_t) * 5));

  glBindVertexArray(0);

}

}
