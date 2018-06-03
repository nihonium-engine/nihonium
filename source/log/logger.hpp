#ifndef NH_LOGGER_H
#define NH_LOGGER_H

#include <cstdarg>
#include <cstdio>
#include <string>
#include <vector>

namespace nh {

const char* log_file_prefixes[] = {
  "[INFO]    ",
  "[WARNING] ",
  "[ERROR]   "
};

const char* stdio_prefixes[] = {
  "\e[1;97m[INFO]   \e[0;97m ",
  "\e[1;93m[WARNING]\e[0;93m ",
  "\e[1;91m[ERROR]  \e[0;91m "
};

class logger_t {
  FILE* log_file;

  void log_info(std::string format, ...);
  void log_warning(std::string format, ...);
  void log_error(std::string format, ...);

  logger_t(std::string log_file_path);
};

}

#endif
