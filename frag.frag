#version 330 core

layout (location = 0) out vec4 nh_colour_out;
in vec3 normal;

void main() {

  nh_colour_out.rgb = normal; nh_colour_out.a = 1.0f;  //vec4(1.0f, 0.5f, 0.2f, 1.0f);

}