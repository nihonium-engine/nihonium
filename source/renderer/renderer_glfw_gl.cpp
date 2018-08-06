#include "renderer_glfw_gl.hpp"

namespace nh {

renderer_glfw_gl_t::renderer_glfw_gl_t() {

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->window = glfwCreateWindow(800, 600, "Nihonium Engine", NULL, NULL);

  if (!window) {
    // TODO: Error.
  }

  glfwMakeContextCurrent(this->window);

  glfwSwapInterval(1);

  gladLoadGL();

  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_BLEND);
  //glEnable(GL_MULTISAMPLE);
  //glEnable(GL_CULL_FACE);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void renderer_glfw_gl_t::frame_start() {
  glfwSwapBuffers(this->window);
  glfwPollEvents();

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer_glfw_gl_t::render() {

  for (auto camera_iter = global_cameras.begin(); camera_iter != global_cameras.end(); camera_iter++) {

    if (!camera_iter->second.enabled) {
      continue;
    }

    for (auto i = this->render_queue.begin(); i != this->render_queue.end(); i++) {

      shader_base_t* base_shader = i->material->shader;

      shader_gl_t* shader = dynamic_cast<shader_gl_t*>(base_shader);
      if (!shader) {
        global_logger->log_error("Shader wasn't an OpenGL shader.");
        continue;
      }

      glUseProgram(shader->program);

      hmm_mat4 model_matrix = HMM_MultiplyMat4(HMM_MultiplyMat4(HMM_Translate(i->position), HMM_QuaternionToMat4(i->rotation)), HMM_Scale(i->scale));

      hmm_mat4 view_matrix = HMM_MultiplyMat4(HMM_QuaternionToMat4(camera_iter->second.rotation), HMM_Translate(HMM_MultiplyVec3f(camera_iter->second.position, -1)));
      int width; int height;
      glfwGetWindowSize(this->window, &width, &height);
      hmm_mat4 projection_matrix = HMM_Perspective(45.0f, (float)width / (float)height, 0.01f, 1000.0f);

      GLint model_location = glGetUniformLocation(shader->program, "nh_model");
      glUniformMatrix4fv(model_location, 1, GL_FALSE, (const GLfloat*)&model_matrix);

      GLint projection_location = glGetUniformLocation(shader->program, "nh_projection");
      glUniformMatrix4fv(projection_location, 1, GL_FALSE, (const GLfloat*)&projection_matrix);

      GLint view_location = glGetUniformLocation(shader->program, "nh_view");
      glUniformMatrix4fv(view_location, 1, GL_FALSE, (const GLfloat*)&view_matrix);

      int current_texture_unit = 0;
      std::vector<GLuint> temp_textures;

      for (auto j = i->material->values.begin(); j != i->material->values.end(); j++) {

        GLuint texture;

        if (j->second.is_map) {

          texture_gl_t* gl_texture = dynamic_cast<texture_gl_t*>(j->second.map);
          if (!gl_texture) {
            global_logger->log_error("Texture wasn't an OpenGL texture.");
            continue;
          }

          texture = gl_texture->texture;

        } else {

          uint8_t values[4];
          for (size_t k = 0; k < 4; k++) {
            values[k] = k < j->second.num_single_values ? j->second.single[k] : 0;
          }

          glGenTextures(1, &texture);
          glBindTexture(GL_TEXTURE_2D, texture);

          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, values);
          glGenerateMipmap(GL_TEXTURE_2D);

          temp_textures.push_back(texture);
        }

        glActiveTexture(GL_TEXTURE0 + current_texture_unit);
        glBindTexture(GL_TEXTURE_2D, texture);

        GLint location = glGetUniformLocation(shader->program, ("nh_param_" + j->first).c_str());
        glUniform1i(location, current_texture_unit);

        current_texture_unit++;
      }

      for (auto j = i->model->meshes.begin(); j != i->model->meshes.end(); j++) {

        mesh_gl_t* mesh = dynamic_cast<mesh_gl_t*>(j->second);
        if (!mesh) {
          global_logger->log_error("Mesh wasn't an OpenGL mesh.");
          continue;
        }

        // Set viewport size.
        int width; int height;
        glfwGetWindowSize(this->window, &width, &height);
        float pos_x = camera_iter->second.screen_x * width;
        float pos_y = camera_iter->second.screen_y * height;
        float size_x = camera_iter->second.screen_width * width;
        float size_y = camera_iter->second.screen_height * height;
        glViewport(pos_x, pos_y, size_x, size_y);

        glBindVertexArray(mesh->vao);
        glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
      }

      glDeleteTextures(temp_textures.size(), temp_textures.data());

    }

  }

  this->render_queue.clear();
}

renderer_glfw_gl_t::~renderer_glfw_gl_t() {

  glfwDestroyWindow(window);

  glfwTerminate();

}

}
