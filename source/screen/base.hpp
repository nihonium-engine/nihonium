#ifndef NH_SCREEN_BASE_H
#define NH_SCREEN_BASE_H

namespace nh {

enum class ScreenErrorCode {
  OK,
  ERROR_CONNECTING_TO_DISPLAY
};

class BaseScreen {

    public:

    virtual void initialise() = 0;
    virtual void uninitialise() = 0;

    virtual void update() = 0;
  
};
  
}

#endif