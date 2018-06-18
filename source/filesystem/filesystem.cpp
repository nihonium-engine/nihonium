#include "filesystem.hpp"

namespace nh {

void filesystem_t::add_mount(std::string name, mount_base_t* mount) {
  this->mounts[name] = mount;
}

void filesystem_t::remove_mount(std::string name) {
  this->mounts.erase(name);
}

file_base_t* filesystem_t::open_file(std::string path) {

  size_t mount_delimiter_pos = path.find_first_of(':');

  // TODO: Consider using a default mount (e.g. main).
  if (mount_delimiter_pos == std::string::npos) {
    // TODO: Use a more specific exception.
    throw std::exception();
  }

  std::string mount = path.substr(0, mount_delimiter_pos);
  std::string mount_path = path.substr(mount_delimiter_pos + 1, std::string::npos);

  if (this->mounts[mount]) {
    return this->mounts[mount]->open_file(mount_path);
  } else {
    throw std::exception();
  }

}

filesystem_t* filesystem;

}
