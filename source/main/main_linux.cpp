
#include "../filesystem/filesystem.hpp"
#include "../filesystem/mount_directory.hpp"
#include "../filesystem/mount_nar.hpp"

#include "../renderer/renderer_glfw_gl.hpp"

#include "../model/mesh_gl.hpp"

#include "../shader/shader_gl.hpp"

#include "../log/logger.hpp"

#include "../object/world_single.hpp"

#include <cstdio>

int main(int argc, char** argv) {

  (void)argc; (void)argv;

  nh::global_logger = new nh::logger_t("log.txt");
  nh::world_base_t* world = new nh::world_single_t();
  nh::global_filesystem = new nh::filesystem_t();
  nh::renderer_glfw_gl_t* renderer = new nh::renderer_glfw_gl_t();
  nh::model_factory_base_t* model_factory = new nh::model_factory_t<nh::mesh_gl_t>();
  nh::shader_factory_t* shader_factory = new nh::shader_factory_t();

  nh::mount_directory_t* mount_main = new nh::mount_directory_t("./");
  nh::global_filesystem->add_mount("main", mount_main);

  nh::global_logger->log_info("Mounted main mount.");

  nh::file_base_t* reader = nh::global_filesystem->open_file("main:test.nmdl");

  nh::file_base_t* vert_reader = nh::global_filesystem->open_file("main:vert.vert");
  nh::file_base_t* frag_reader = nh::global_filesystem->open_file("main:frag.frag");

  nh::shader_base_t* shader = shader_factory->shader_create<nh::shader_gl_t>(vert_reader, frag_reader);

  nh::model_t* model = model_factory->load_model(reader);

  nh::object_t* object = new nh::object_t();
  object->add_script("main:test.js");

  dynamic_cast<nh::world_single_t*>(world)->objects.push_back(object);

  while (true) {
    world->update(1.5);
    world->draw();
    renderer->frame_start();

    nh::render_queue_item_t item;
    item.model = model;
    item.shader = shader;
    renderer->add_to_render_queue(item);

    renderer->render();
  }

  return 0;

}
