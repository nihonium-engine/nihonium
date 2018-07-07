#version 330 core

layout (location = 0) in vec3 nh_position;
layout (location = 1) in vec3 nh_normal;
layout (location = 2) in vec2 nh_uv;

uniform mat4 nh_model;
uniform mat4 nh_projection;

out vec3 normal;
out vec2 uv;

void main() {

  gl_Position = nh_projection * nh_model * vec4(nh_position.x, nh_position.y, nh_position.z, 1.0);
  normal = nh_normal;
  uv = nh_uv;

}
