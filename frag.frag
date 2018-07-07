#version 330 core

layout (location = 0) out vec4 nh_colour_out;

in vec3 normal;
in vec2 uv;

uniform sampler2D nh_param_albedo;
uniform sampler2D nh_param_normal;
uniform sampler2D nh_param_metallic;
uniform sampler2D nh_param_roughness;
uniform sampler2D nh_param_ao;


void main() {

  nh_colour_out = texture(nh_param_albedo, uv);

}
