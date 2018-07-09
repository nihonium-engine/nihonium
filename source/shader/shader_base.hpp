#ifndef NH_SHADER_BASE_H
#define NH_SHADER_BASE_H

#include "../filesystem/mount_base.hpp"
#include "../log/logger.hpp"

namespace nh {

class shader_base_t {

  public:
  shader_base_t(file_base_t* vert_reader, file_base_t* frag_reader);
  virtual ~shader_base_t();

  virtual void initialise() = 0;

  protected:
  char* vert_source;
  char* frag_source;
  size_t vert_source_length;
  size_t frag_source_length;

};

class shader_factory_base_t {
  public:
  virtual shader_base_t* load_shader(file_base_t* vert_reader, file_base_t* frag_reader) = 0;
};

template <typename T> class shader_factory_t : public shader_factory_base_t {

  public:

  shader_base_t* load_shader(file_base_t* vert_reader, file_base_t* frag_reader) {
    shader_base_t* shader = new T(vert_reader, frag_reader);
    shader->initialise();
    return shader;
  }

  logger_t* logger;

};

extern shader_factory_base_t* global_shader_factory;

}

#endif
