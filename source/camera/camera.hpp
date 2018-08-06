#ifndef NH_CAMERA_H
#define NH_CAMERA_H

#include <map>
#include <string>

#include "../../external/hmm/HandmadeMath.h"

namespace nh {

class camera_t {

  public:
  float screen_x;
  float screen_y;
  float screen_width;
  float screen_height;

  hmm_vec3 position;
  hmm_quaternion rotation;

  bool enabled;

};

extern std::map<std::string, camera_t> global_cameras;

}

#endif
