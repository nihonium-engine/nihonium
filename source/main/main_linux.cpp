
#include "../roles/single.hpp"
#include "../screen/glfw.hpp"

nh::BaseRole* role;

int main(int argc, char** argv) {

  (void)argc; (void)argv;

  nh::BaseScreen* screen = new nh::GLFWScreen();

  screen->initialise();

  while (true) {
    screen->update();
  }

  screen->uninitialise();

  /*
  role = new nh::SingleRole();

  role->initialise();

  role->main_loop();

  role->uninitialise();

  delete role;
  */
  return 0;

}