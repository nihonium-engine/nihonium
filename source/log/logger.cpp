#include "logger.hpp"

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

namespace nh {

void logger_t::log_info(std::string format, ...) {

  va_list list;

  va_start(list, format);
  vfprintf(this->log_file, (log_file_prefixes[0] + format + "\n").c_str(), list);
  va_end(list);

  fflush(this->log_file);

  va_start(list, format);
  vprintf((stdio_prefixes[0] + format + "\e[0m\n").c_str(), list);
  va_end(list);
    
}

void logger_t::log_warning(std::string format, ...) {

  va_list list;
  
  va_start(list, format);
  vfprintf(this->log_file, (log_file_prefixes[1] + format + "\n").c_str(), list);
  va_end(list);

  fflush(this->log_file);

  va_start(list, format);
  vprintf((stdio_prefixes[1] + format + "\e[0m\n").c_str(), list);
  va_end(list);

}

void logger_t::log_error(std::string format, ...) {

  va_list list;
  
  va_start(list, format);
  vfprintf(this->log_file, (log_file_prefixes[2] + format).c_str(), list);
  va_end(list);

  fflush(this->log_file);

  va_start(list, format);
  vprintf((stdio_prefixes[2] + format + "\e[0;97m\n").c_str(), list);
  va_end(list);

}

logger_t::logger_t(std::string path) {
  this->log_file = fopen(path.c_str(), "w");
}

logger_t* global_logger;

}
