#ifndef NH_OBJECT_H
#define NH_OBJECT_H

#include <cstdio>
#include <map>
#include <string>
#include <vector>

#include "../../external/duktape/duktape.h"

#include "../filesystem/filesystem.hpp"
#include "../log/logger.hpp"

#include "binding_filesystem.hpp"
#include "binding_log.hpp"

namespace nh {

class object_t {

  public:

  object_t* parent;
  std::vector<object_t*> children;

  std::map<std::string, duk_context*> scripts;

  void update(double delta_time);
  void draw();

  void add_script(std::string file_name);

};

}

#endif
