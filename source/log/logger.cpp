#include "logger.hpp"

namespace nh {

void logger_t::log_info(std::string format, ...) {

  va_list list;
  va_start(list, format);

  vfprintf(this->log_file, (log_file_prefixes[0] + format).c_str(), list);
  vprintf((stdio_prefixes[0] + format).c_str(), list);

  va_end(list);
    
}

void logger_t::log_warning(std::string format, ...) {

  va_list list;
  va_start(list, format);

  vfprintf(this->log_file, (log_file_prefixes[1] + format).c_str(), list);
  vprintf((stdio_prefixes[1] + format).c_str(), list);

  va_end(list);

}

void logger_t::log_error(std::string format, ...) {

  va_list list;
  va_start(list, format);

  vfprintf(this->log_file, (log_file_prefixes[2] + format).c_str(), list);
  vprintf((stdio_prefixes[2] + format).c_str(), list);

  va_end(list);

}

logger_t::logger_t(std::string path) {
  this->log_file = fopen(path.c_str(), "w");
}

}
