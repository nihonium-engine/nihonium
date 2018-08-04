#include "input_glfw.hpp"

namespace nh {

// TODO: Support all keys.
std::map<std::string, int> string_to_key_map = {
  {"a", GLFW_KEY_A},
  {"b", GLFW_KEY_B},
  {"c", GLFW_KEY_C},
  {"d", GLFW_KEY_D},
  {"e", GLFW_KEY_E},
  {"f", GLFW_KEY_F},
  {"g", GLFW_KEY_G},
  {"h", GLFW_KEY_H},
  {"i", GLFW_KEY_I},
  {"j", GLFW_KEY_J},
  {"k", GLFW_KEY_K},
  {"l", GLFW_KEY_L},
  {"m", GLFW_KEY_M},
  {"n", GLFW_KEY_N},
  {"o", GLFW_KEY_O},
  {"p", GLFW_KEY_P},
  {"q", GLFW_KEY_Q},
  {"r", GLFW_KEY_R},
  {"s", GLFW_KEY_S},
  {"t", GLFW_KEY_T},
  {"u", GLFW_KEY_U},
  {"v", GLFW_KEY_V},
  {"w", GLFW_KEY_W},
  {"x", GLFW_KEY_X},
  {"y", GLFW_KEY_Y},
  {"z", GLFW_KEY_Z},

  {" ", GLFW_KEY_SPACE},

  {"up", GLFW_KEY_UP},
  {"down", GLFW_KEY_DOWN},
  {"left", GLFW_KEY_LEFT},
  {"right", GLFW_KEY_RIGHT},

  {"escape", GLFW_KEY_ESCAPE}

};

bool input_glfw_t::is_down(std::string key) {

  // TODO: Handle invalid keys.
  return glfwGetKey(this->renderer->window, string_to_key_map[key]) == GLFW_PRESS;

}

}
