#ifndef NHMATHS_H
#define NHMATHS_H

#ifndef NHM_DONT_USE_MATH_H
#include <math.h>
#define NHM_SIN(x) sin(x)
#define NHM_COS(x) cos(x)
#define NHM_TAN(x) tan(x)
#define NHM_SQRT(x) sqrt(x)
#endif

#if defined(NHM_USE_LONG_DOUBLE)
typedef long double NHMFloat;
#define NHM_PI 3.14159265358979323846
#elif defined(NHM_USE_DOUBLE)
typedef double NHMFloat;
#define NHM_PI 3.14159265358979323846
#else
typedef float NHMFloat;
#define NHM_PI 3.14159265358979f
#endif

typedef struct {
  NHMFloat x;
  NHMFloat y;
} NHMVec2;

typedef struct {
  NHMFloat x;
  NHMFloat y;
  NHMFloat z;
} NHMVec3;

typedef struct {
  NHMFloat x;
  NHMFloat y;
  NHMFloat z;
  NHMFloat w;
} NHMVec4;

typedef struct {
  NHMFloat x;
  NHMFloat y;
  NHMFloat z;
  NHMFloat w; 
} NHMQuaternion;

typedef struct {
  NHMFloat elements[16];
} NHMMat4;

NHMVec4 nhm_new_vec4(NHMFloat x, NHMFloat y, NHMFloat z, NHMFloat w);

NHMQuaternion nhm_new_quaternion(NHMFloat x, NHMFloat y, NHMFloat z, NHMFloat w);
NHMQuaternion nhm_new_quaternion_from_axis_angle(NHMVec4 axis, NHMFloat angle);

NHMMat4 nhm_new_mat4_zero(void);
NHMMat4 nhm_new_mat4_identity(void);
NHMMat4 nhm_new_mat4_translate(NHMVec4 translation);
NHMMat4 nhm_new_mat4_scale(NHMVec4 scale);
NHMMat4 nhm_new_mat4_perspective(NHMFloat fov, NHMFloat aspect_ratio, NHMFloat near, NHMFloat far);
NHMMat4 nhm_new_mat4_orthographic(NHMFloat left, NHMFloat right, NHMFloat bottom, NHMFloat top, NHMFloat near, NHMFloat far);

NHMVec4 nhm_vec4_add(NHMVec4 left, NHMVec4 right);
NHMVec4 nhm_vec4_subtract(NHMVec4 left, NHMVec4 right);
NHMVec4 nhm_vec4_multiply(NHMVec4 left, NHMVec4 right);
NHMVec4 nhm_vec4_multiply_scalar(NHMVec4 left, NHMFloat right);
NHMVec4 nhm_vec4_divide(NHMVec4 left, NHMVec4 right);
NHMVec4 nhm_vec4_divide_scalar(NHMVec4 left, NHMFloat right);
NHMVec4 nhm_vec4_cross_product(NHMVec4 left, NHMVec4 right);
NHMFloat nhm_vec4_dot_product(NHMVec4 left, NHMVec4 right);
NHMVec4 nhm_vec4_normalise(NHMVec4 vec4);
NHMFloat nhm_vec4_length(NHMVec4 vec4);
NHMFloat nhm_vec4_length_squared(NHMVec4 vec4);

NHMQuaternion nhm_quaternion_add(NHMQuaternion left, NHMQuaternion right);
NHMQuaternion nhm_quaternion_subtract(NHMQuaternion left, NHMQuaternion right);
NHMQuaternion nhm_quaternion_multiply(NHMQuaternion left, NHMQuaternion right);
NHMQuaternion nhm_quaternion_multiply_scalar(NHMQuaternion left, NHMFloat right);
NHMQuaternion nhm_quaternion_divide_scalar(NHMQuaternion left, NHMFloat right);
NHMQuaternion nhm_quaternion_inverse(NHMQuaternion quaternion);
NHMQuaternion nhm_quaternion_normalise(NHMQuaternion quaternion);

NHMMat4 nhm_mat4_add(NHMMat4 left, NHMMat4 right);
NHMMat4 nhm_mat4_subtract(NHMMat4 left, NHMMat4 right);
NHMMat4 nhm_mat4_multiply(NHMMat4 left, NHMMat4 right);
NHMMat4 nhm_mat4_multiply_scalar(NHMFloat left, NHMMat4 right);
NHMMat4 nhm_mat4_inverse(NHMMat4 mat4);
NHMMat4 nhm_mat4_transpose(NHMMat4 mat4);

#endif

#ifdef NHMATHS_IMPLEMENTATION

NHMVec4 nhm_new_vec4(NHMFloat x, NHMFloat y, NHMFloat z, NHMFloat w) {

  NHMVec4 vec4;

  vec4.x = x;
  vec4.y = y;
  vec4.z = z;
  vec4.w = w;

  return vec4;

}

NHMQuaternion nhm_new_quaternion(NHMFloat x, NHMFloat y, NHMFloat z, NHMFloat w) {

  NHMQuaternion quaternion;

  quaternion.x = x;
  quaternion.y = y;
  quaternion.z = z;
  quaternion.w = w;

  return quaternion;
  
}

NHMQuaternion nhm_new_quaternion_from_axis_angle(NHMVec4 axis, NHMFloat angle) {

  NHMQuaternion quaternion;

  NHMFloat sin_angle_over_2 = NHM_SIN(angle / 2.0f);

  quaternion.x = axis.x * sin_angle_over_2;
  quaternion.y = axis.y * sin_angle_over_2;
  quaternion.z = axis.z * sin_angle_over_2;
  quaternion.w = NHM_COS(angle / 2.0f);

  return quaternion;
  
}

NHMMat4 nhm_new_mat4_zero() {

  NHMMat4 mat4;

  for (int i = 0; i < 16; i++) {
    mat4.elements[i] = 0;
  }

  return mat4;

}

NHMMat4 nhm_new_mat4_identity() {

  NHMMat4 mat4 = nhm_new_mat4_zero();
  
  for (int i = 0; i < 16; i += 5) {
    mat4.elements[i] = 1;
  }

  return mat4;
 
}

NHMMat4 nhm_new_mat4_translate(NHMVec4 translation) {

  NHMMat4 mat4 = nhm_new_mat4_identity();

  mat4.elements[12] = translation.x;
  mat4.elements[13] = translation.y;
  mat4.elements[14] = translation.z;

  return mat4;
  
}

NHMMat4 nhm_new_mat4_scale(NHMVec4 scale) {

  NHMMat4 mat4 = nhm_new_mat4_identity();

  mat4.elements[0] = scale.x;
  mat4.elements[5] = scale.y;
  mat4.elements[10] = scale.z;

  return mat4;
  
}

NHMMat4 nhm_new_mat4_perspective(NHMFloat fov, NHMFloat aspect_ratio, NHMFloat near, NHMFloat far) {

  NHMMat4 mat4 = nhm_new_mat4_zero();

  NHMFloat tan_theta_over_2 = NHM_TAN(fov);

  mat4.elements[0] = 1.0 / tan_theta_over_2;
  mat4.elements[5] = aspect_ratio / tan_theta_over_2;
  mat4.elements[11] = -1.0;
  mat4.elements[10] = (near + far) / (near - far);
  mat4.elements[14] = (2.0 * near * far) / (near - far);
  mat4.elements[15] = 0.0;

  return mat4;

}

NHMMat4 nhm_new_mat4_orthographic(NHMFloat left, NHMFloat right, NHMFloat bottom, NHMFloat top, NHMFloat near, NHMFloat far) {

  NHMMat4 mat4 = nhm_new_mat4_zero();

  mat4.elements[0] = 2.0 / (right - left);
  mat4.elements[5] = 2.0 / (top - bottom);
  mat4.elements[10] = 2.0 / (near - far);
  mat4.elements[15] = 1.0;

  mat4.elements[12] = (left + right) / (left - right);
  mat4.elements[13] = (bottom + top) / (bottom - top);
  mat4.elements[14] = (far + near) / (near - far);

  return mat4;

}

NHMVec4 nhm_vec4_add(NHMVec4 left, NHMVec4 right) {

  NHMVec4 vec4;

  vec4.x = left.x + right.x;
  vec4.y = left.y + right.y;
  vec4.z = left.z + right.z;
  vec4.w = left.w + right.w;

  return vec4;

}

NHMVec4 nhm_vec4_subtract(NHMVec4 left, NHMVec4 right) {

  NHMVec4 vec4;

  vec4.x = left.x - right.x;
  vec4.y = left.y - right.y;
  vec4.z = left.z - right.z;
  vec4.w = left.w - right.w;

  return vec4;

}

NHMVec4 nhm_vec4_multiply(NHMVec4 left, NHMVec4 right) {

  NHMVec4 vec4;

  vec4.x = left.x * right.x;
  vec4.y = left.y * right.y;
  vec4.z = left.z * right.z;
  vec4.w = left.w * right.w;

  return vec4;  

}

NHMVec4 nhm_vec4_multiply_scalar(NHMVec4 left, NHMFloat right) {

  NHMVec4 vec4;

  vec4.x = left.x * right;
  vec4.y = left.y * right;
  vec4.z = left.z * right;
  vec4.w = left.w * right;

  return vec4;

}

NHMVec4 nhm_vec4_divide(NHMVec4 left, NHMVec4 right) {

  NHMVec4 vec4;

  vec4.x = left.x / right.x;
  vec4.y = left.y / right.y;
  vec4.z = left.z / right.z;
  vec4.w = left.w / right.w;

  return vec4;

}

NHMVec4 nhm_vec4_divide_scalar(NHMVec4 left, NHMFloat right) {

  NHMVec4 vec4;

  vec4.x = left.x / right;
  vec4.y = left.y / right;
  vec4.z = left.z / right;
  vec4.w = left.w / right;

  return vec4;
  
}

NHMVec4 nhm_vec4_cross_product(NHMVec4 left, NHMVec4 right) {

  NHMVec4 vec4;

  vec4.x = (left.x * right.z) - (left.z * right.y);
  vec4.y = (left.z * right.x) - (left.x * right.z);
  vec4.z = (left.x * right.y) - (left.y * right.x);

  vec4.w = 0;

  return vec4;

}

NHMFloat nhm_vec4_dot_product(NHMVec4 left, NHMVec4 right) {

  return (left.x * right.x) + (left.y * right.y) + (left.z * right.z) + (left.w * right.w);

}

NHMVec4 nhm_vec4_normalise(NHMVec4 vec4) {
  return nhm_vec4_divide_scalar(vec4, NHM_SQRT(nhm_vec4_dot_product(vec4, vec4)));
}

NHMFloat nhm_vec4_length(NHMVec4 vec4) {
  return NHM_SQRT(nhm_vec4_dot_product(vec4, vec4));
}

NHMFloat nhm_vec4_length_squared(NHMVec4 vec4) {
  return nhm_vec4_dot_product(vec4, vec4);
}

NHMQuaternion nhm_quaternion_add(NHMQuaternion left, NHMQuaternion right) {

  NHMQuaternion quaternion;

  quaternion.x = left.x + right.x;
  quaternion.y = left.y + right.y;
  quaternion.z = left.z + right.z;
  quaternion.w = left.w + right.w;

  return quaternion;
   
}

NHMQuaternion nhm_quaternion_subtract(NHMQuaternion left, NHMQuaternion right) {

  NHMQuaternion quaternion;

  quaternion.x = left.x - right.x;
  quaternion.y = left.y - right.y;
  quaternion.z = left.z - right.z;
  quaternion.w = left.w - right.w;

  return quaternion;

}

NHMQuaternion nhm_quaternion_multiply(NHMQuaternion left, NHMQuaternion right) {

  NHMQuaternion quaternion;

  quaternion.x = (left.x * right.w) + (left.y * right.z) - (left.z * right.y) + (left.w * right.x);
  quaternion.y = (-left.x * right.z) + (left.y * right.w) + (left.z * right.x) + (left.w * right.y);
  quaternion.z = (left.x * right.y) - (left.y * right.x) + (left.z * right.w) + (left.w * right.z);
  quaternion.w = (-left.x * right.x) - (left.y * right.y) - (left.z * right.z) + (left.w * right.w);

  return quaternion;

}

NHMQuaternion nhm_quaternion_multiply_scalar(NHMQuaternion left, NHMFloat right) {

  NHMQuaternion quaternion;

  quaternion.x = left.x * right;
  quaternion.y = left.y * right;
  quaternion.z = left.z * right;
  quaternion.w = left.w * right;

  return quaternion;
 
}

NHMQuaternion nhm_quaternion_divide_scalar(NHMQuaternion left, NHMFloat right) {

  NHMQuaternion quaternion;

  quaternion.x = left.x / right;
  quaternion.y = left.y / right;
  quaternion.z = left.z / right;
  quaternion.w = left.w / right;

  return quaternion;

}

NHMQuaternion nhm_quaternion_inverse(NHMQuaternion quaternion_in) {

  NHMQuaternion quaternion;

  NHMFloat length_squared = (quaternion_in.x * quaternion_in.x) + (quaternion_in.y * quaternion_in.y) + (quaternion_in.z * quaternion_in.z);

  quaternion.x = -quaternion_in.x / length_squared;
  quaternion.y = -quaternion_in.y / length_squared;
  quaternion.z = -quaternion_in.z / length_squared;
  quaternion.w = quaternion_in.w / length_squared;

  return quaternion;

}

NHMQuaternion nhm_quaternion_normalise(NHMQuaternion quaternion);

NHMMat4 nhm_mat4_add(NHMMat4 left, NHMMat4 right);
NHMMat4 nhm_mat4_subtract(NHMMat4 left, NHMMat4 right);
NHMMat4 nhm_mat4_multiply(NHMMat4 left, NHMMat4 right);
NHMMat4 nhm_mat4_multiply_scalar(NHMFloat left, NHMMat4 right);
NHMMat4 nhm_mat4_inverse(NHMMat4 mat4);
NHMMat4 nhm_mat4_transpose(NHMMat4 mat4);

#endif
