#ifndef NH_COMMON_ROLE_H
#define NH_COMMON_ROLE_H

namespace nh {

class BaseRole {

  public:

  virtual void initialise() = 0;
  virtual void uninitialise() = 0;

  virtual void main_loop() = 0;

  virtual ~BaseRole() {};
  
};

}

#endif