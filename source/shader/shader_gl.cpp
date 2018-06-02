#include "shader_gl.hpp"

namespace nh {

void shader_gl_t::initialise() {

  // TODO: Modify this to use a proper logging system.
  // Of course, a proper logging system needs to exist first.

  GLint success;

  GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, &this->vert_source, (GLint*)&this->vert_source_length);
  glCompileShader(vert_shader);

  glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLint length;
    glGetShaderiv(vert_shader, GL_INFO_LOG_LENGTH, &length);
    char* message = new char[length];
    glGetShaderInfoLog(vert_shader, length, nullptr, message);
    printf("Vertex shader error: %s\n", message);
    delete[] message;
  }

  GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &this->frag_source, (GLint*)&this->frag_source_length);
  glCompileShader(frag_shader);

  glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLint length;
    glGetShaderiv(frag_shader, GL_INFO_LOG_LENGTH, &length);
    char* message = new char[length];
    glGetShaderInfoLog(frag_shader, length, nullptr, message);
    printf("Fragment shader error: %s\n", message);
    delete[] message;
  }

  this->program = glCreateProgram();
  glAttachShader(this->program, vert_shader);
  glAttachShader(this->program, frag_shader);
  glLinkProgram(this->program);

  glGetProgramiv(this->program, GL_LINK_STATUS, &success);
  if (!success) {
    GLint length;
    glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &length);
    char* message = new char[length];
    glGetProgramInfoLog(this->program, length, nullptr, message);
    printf("Program link error: %s\n", message);
    delete[] message;
  }

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

}

}
