#include "shader_gl.hpp"

namespace nh {

void shader_gl_t::initialise() {

  // TODO: Give more precise errors (i.e. check log).
  // I've deferred this task to when a proper error logging system is added.

  GLint success;

  GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, &this->vert_source, (GLint*)&this->vert_source_length);
  glCompileShader(vert_shader);

  glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    printf("Something bad happened with the vertex shader.\n");
  }

  GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &this->frag_source, (GLint*)&this->frag_source_length);
  glCompileShader(frag_shader);

  glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    printf("Something bad happened with the fragment shader.\n");
  }

  this->program = glCreateProgram();
  glAttachShader(this->program, vert_shader);
  glAttachShader(this->program, frag_shader);
  glLinkProgram(this->program);

  glGetProgramiv(this->program, GL_LINK_STATUS, &success);
  if(!success) {
    printf("Something bad happened with the program.\n");
  }

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

}

}
