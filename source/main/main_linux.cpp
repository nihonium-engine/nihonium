
#include <stdio.h>

#include "../filesystem/filesystem.hpp"
#include "../filesystem/mount_directory.hpp"
#include "../filesystem/mount_nar.hpp"
#include "../log/logger.hpp"
#include "../model/mesh_gl.hpp"
#include "../object/world_single.hpp"
#include "../renderer/renderer_glfw_gl.hpp"
#include "../shader/shader_gl.hpp"
#include "../texture/texture_gl.hpp"

int main(int argc, char** argv) {

  (void)argc; (void)argv;

  nh::global_logger = new nh::logger_t("log.txt");
  nh::world_base_t* world = new nh::world_single_t();
  nh::global_filesystem = new nh::filesystem_t();
  nh::global_renderer = new nh::renderer_glfw_gl_t();
  nh::global_model_factory = new nh::model_factory_t<nh::mesh_gl_t>();
  nh::global_shader_factory = new nh::shader_factory_t<nh::shader_gl_t>();
  nh::global_texture_factory = new nh::texture_factory_t<nh::texture_gl_t>();

  nh::mount_directory_t* mount_main = new nh::mount_directory_t("./");
  nh::global_filesystem->add_mount("main", mount_main);

  nh::global_logger->log_info("Mounted main mount.");

  nh::object_t* object = new nh::object_t();
  object->add_script("main:test.js");

  dynamic_cast<nh::world_single_t*>(world)->objects.push_back(object);

  while (true) {
    world->update(1.5);
    world->draw();
    nh::global_renderer->frame_start();

    nh::global_renderer->render();
  }

  return 0;

}
