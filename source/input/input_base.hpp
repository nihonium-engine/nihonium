#ifndef NH_INPUT_BASE_H
#define NH_INPUT_BASE_H

#include <string>

namespace nh {

class input_base_t {

  public:

  virtual bool is_down(std::string key) = 0;

};

extern input_base_t* global_input;

}

#endif
