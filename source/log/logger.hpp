#ifndef NH_LOGGER_H
#define NH_LOGGER_H

#include <cstdarg>
#include <cstdio>
#include <string>
#include <vector>

namespace nh {

class logger_t {

  public:
  void log_info(std::string format, ...);
  void log_warning(std::string format, ...);
  void log_error(std::string format, ...);

  logger_t(std::string log_file_path);

  private:
  FILE* log_file;
};

}

#endif
