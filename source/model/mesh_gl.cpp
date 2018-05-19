#include "mesh_gl.hpp"

namespace nh {

GLuint shader_program;

const char* vertex_source = 
"#version 330 core\n"
"layout (location = 0) in vec3 nh_position;\n"
"layout (location = 1) in vec3 nh_normal;\n"
"layout (location = 2) in vec2 nh_uv;\n"
"out vec3 normal;\n"
"void main() {\n"
"   gl_Position = vec4(nh_position.x, nh_position.y, nh_position.z, 1.0);\n"
"   normal = nh_normal;"
"}";

const char* fragment_source =
"#version 330 core\n"
"layout (location = 0) out vec4 nh_colour_out;\n"
"in vec3 normal\n;"
"void main() {\n"
"    nh_colour_out.rgb = normal; nh_colour_out.a = 1.0f;  //vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}";

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

  // TEMPORARY: Compile the temp shaders.
  GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, &vertex_source, NULL);
  glCompileShader(vert_shader);

  GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &fragment_source, NULL);
  glCompileShader(frag_shader);

  shader_program = glCreateProgram();
  glAttachShader(shader_program, vert_shader);
  glAttachShader(shader_program, frag_shader);
  glLinkProgram(shader_program);

  int success;
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if(!success) {
    //glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("Something bad happened.\n");
  }

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

}

void mesh_gl_t::temp_draw() {

  glUseProgram(shader_program);

  glBindVertexArray(this->vao);

  glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);

}

}
