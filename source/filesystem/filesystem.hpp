#ifndef NH_FILESYSTEM_H
#define NH_FILESYSTEM_H

#include <vector>

#include "mount_base.hpp"

namespace nh {

class filesystem_t {

  public:
  void add_mount(std::string name, mount_base_t* mount);
  void remove_mount(std::string name);

  file_base_t* open_file(std::string path);

  private:
  std::map<std::string, mount_base_t*> mounts;

};

extern filesystem_t* filesystem;

}

#endif
