#include "shader_gl.hpp"

namespace nh {

void shader_gl_t::initialise(logger_t* logger) {

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
    logger->log_error("Error compiling OpenGL vertex shader: %s", message);
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
    logger->log_error("Error compiling OpenGL fragment shader: %s", message);
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
    logger->log_error("Error linking OpenGL shader program: %s", message);
    delete[] message;
  }

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

}

}
