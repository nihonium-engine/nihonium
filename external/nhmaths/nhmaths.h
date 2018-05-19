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
typedef long double nhm_float_t;
#define NHM_PI 3.14159265358979323846
#elif defined(NHM_USE_DOUBLE)
typedef double nhm_float_t;
#define NHM_PI 3.14159265358979323846
#else
typedef float nhm_float_t;
#define NHM_PI 3.14159265358979f
#endif

typedef struct {
  nhm_float_t x;
  nhm_float_t y;
} nhm_vec2_t;

typedef struct {
  nhm_float_t x;
  nhm_float_t y;
  nhm_float_t z;
} nhm_vec3_t;

typedef struct {
  nhm_float_t x;
  nhm_float_t y;
  nhm_float_t z;
  nhm_float_t w;
} nhm_vec4_t;

typedef struct {
  nhm_float_t x;
  nhm_float_t y;
  nhm_float_t z;
  nhm_float_t w; 
} nhm_quaternion_t;

/*
Note: matrices are laid out like so:
 0   4   8  12
 1   5   9  13
 2   6  10  14
 3   7  11  15
*/
typedef struct {
  nhm_float_t elements[16];
} nhm_mat4_t;

nhm_vec4_t nhm_new_vec4(nhm_float_t x, nhm_float_t y, nhm_float_t z, nhm_float_t w);

nhm_quaternion_t nhm_new_quaternion(nhm_float_t x, nhm_float_t y, nhm_float_t z, nhm_float_t w);
nhm_quaternion_t nhm_new_quaternion_from_axis_angle(nhm_vec4_t axis, nhm_float_t angle);

nhm_mat4_t nhm_new_mat4_zero(void);
nhm_mat4_t nhm_new_mat4_identity(void);
nhm_mat4_t nhm_new_mat4_translate(nhm_vec4_t translation);
nhm_mat4_t nhm_new_mat4_scale(nhm_vec4_t scale);
nhm_mat4_t nhm_new_mat4_perspective(nhm_float_t fov, nhm_float_t aspect_ratio, nhm_float_t near, nhm_float_t far);
nhm_mat4_t nhm_new_mat4_orthographic(nhm_float_t left, nhm_float_t right, nhm_float_t bottom, nhm_float_t top, nhm_float_t near, nhm_float_t far);
nhm_mat4_t nhm_new_mat4_from_quaternion(nhm_quaternion_t quaternion);

nhm_vec4_t nhm_vec4_add(nhm_vec4_t left, nhm_vec4_t right);
nhm_vec4_t nhm_vec4_subtract(nhm_vec4_t left, nhm_vec4_t right);
nhm_vec4_t nhm_vec4_multiply(nhm_vec4_t left, nhm_vec4_t right);
nhm_vec4_t nhm_vec4_multiply_scalar(nhm_vec4_t left, nhm_float_t right);
nhm_vec4_t nhm_vec4_divide(nhm_vec4_t left, nhm_vec4_t right);
nhm_vec4_t nhm_vec4_divide_scalar(nhm_vec4_t left, nhm_float_t right);
nhm_vec4_t nhm_vec4_cross_product(nhm_vec4_t left, nhm_vec4_t right);
nhm_float_t nhm_vec4_dot_product(nhm_vec4_t left, nhm_vec4_t right);
nhm_vec4_t nhm_vec4_normalise(nhm_vec4_t vec4);
nhm_float_t nhm_vec4_length(nhm_vec4_t vec4);
nhm_float_t nhm_vec4_length_squared(nhm_vec4_t vec4);

nhm_quaternion_t nhm_quaternion_add(nhm_quaternion_t left, nhm_quaternion_t right);
nhm_quaternion_t nhm_quaternion_subtract(nhm_quaternion_t left, nhm_quaternion_t right);
nhm_quaternion_t nhm_quaternion_multiply(nhm_quaternion_t left, nhm_quaternion_t right);
nhm_quaternion_t nhm_quaternion_multiply_scalar(nhm_quaternion_t left, nhm_float_t right);
nhm_quaternion_t nhm_quaternion_divide_scalar(nhm_quaternion_t left, nhm_float_t right);
nhm_quaternion_t nhm_quaternion_inverse(nhm_quaternion_t quaternion);
nhm_quaternion_t nhm_quaternion_normalise(nhm_quaternion_t quaternion);

nhm_mat4_t nhm_mat4_add(nhm_mat4_t left, nhm_mat4_t right);
nhm_mat4_t nhm_mat4_subtract(nhm_mat4_t left, nhm_mat4_t right);
nhm_mat4_t nhm_mat4_multiply(nhm_mat4_t left, nhm_mat4_t right);
nhm_mat4_t nhm_mat4_multiply_scalar(nhm_float_t left, nhm_mat4_t right);
nhm_vec4_t nhm_mat4_multiply_vec4(nhm_vec4_t left, nhm_mat4_t right);
nhm_mat4_t nhm_mat4_inverse(nhm_mat4_t mat4);
nhm_mat4_t nhm_mat4_transpose(nhm_mat4_t mat4);

#endif

#ifdef NHMATHS_IMPLEMENTATION

nhm_vec4_t nhm_new_vec4(nhm_float_t x, nhm_float_t y, nhm_float_t z, nhm_float_t w) {

  nhm_vec4_t vec4;

  vec4.x = x;
  vec4.y = y;
  vec4.z = z;
  vec4.w = w;

  return vec4;

}

nhm_quaternion_t nhm_new_quaternion(nhm_float_t x, nhm_float_t y, nhm_float_t z, nhm_float_t w) {

  nhm_quaternion_t quaternion;

  quaternion.x = x;
  quaternion.y = y;
  quaternion.z = z;
  quaternion.w = w;

  return quaternion;
  
}

nhm_quaternion_t nhm_new_quaternion_from_axis_angle(nhm_vec4_t axis, nhm_float_t angle) {

  nhm_quaternion_t quaternion;

  nhm_float_t sin_angle_over_2 = NHM_SIN(angle / 2.0f);

  quaternion.x = axis.x * sin_angle_over_2;
  quaternion.y = axis.y * sin_angle_over_2;
  quaternion.z = axis.z * sin_angle_over_2;
  quaternion.w = NHM_COS(angle / 2.0f);

  return quaternion;
  
}

nhm_mat4_t nhm_new_mat4_zero() {

  nhm_mat4_t mat4;

  for (int i = 0; i < 16; i++) {
    mat4.elements[i] = 0;
  }

  return mat4;

}

nhm_mat4_t nhm_new_mat4_identity() {

  nhm_mat4_t mat4 = nhm_new_mat4_zero();
  
  for (int i = 0; i < 16; i += 5) {
    mat4.elements[i] = 1;
  }

  return mat4;
 
}

nhm_mat4_t nhm_new_mat4_translate(nhm_vec4_t translation) {

  nhm_mat4_t mat4 = nhm_new_mat4_identity();

  mat4.elements[12] = translation.x;
  mat4.elements[13] = translation.y;
  mat4.elements[14] = translation.z;

  return mat4;
  
}

nhm_mat4_t nhm_new_mat4_scale(nhm_vec4_t scale) {

  nhm_mat4_t mat4 = nhm_new_mat4_identity();

  mat4.elements[0] = scale.x;
  mat4.elements[5] = scale.y;
  mat4.elements[10] = scale.z;

  return mat4;
  
}

nhm_mat4_t nhm_new_mat4_perspective(nhm_float_t fov, nhm_float_t aspect_ratio, nhm_float_t near, nhm_float_t far) {

  nhm_mat4_t mat4 = nhm_new_mat4_zero();

  nhm_float_t tan_theta_over_2 = NHM_TAN(fov);

  mat4.elements[0] = 1.0 / tan_theta_over_2;
  mat4.elements[5] = aspect_ratio / tan_theta_over_2;
  mat4.elements[11] = -1.0;
  mat4.elements[10] = (near + far) / (near - far);
  mat4.elements[14] = (2.0 * near * far) / (near - far);
  mat4.elements[15] = 0.0;

  return mat4;

}

nhm_mat4_t nhm_new_mat4_orthographic(nhm_float_t left, nhm_float_t right, nhm_float_t bottom, nhm_float_t top, nhm_float_t near, nhm_float_t far) {

  nhm_mat4_t mat4 = nhm_new_mat4_zero();

  mat4.elements[0] = 2.0 / (right - left);
  mat4.elements[5] = 2.0 / (top - bottom);
  mat4.elements[10] = 2.0 / (near - far);
  mat4.elements[15] = 1.0;

  mat4.elements[12] = (left + right) / (left - right);
  mat4.elements[13] = (bottom + top) / (bottom - top);
  mat4.elements[14] = (far + near) / (near - far);

  return mat4;

}

nhm_mat4_t nhm_new_mat4_from_quaternion(nhm_quaternion_t quaternion) {

  nhm_mat4_t out = nhm_new_mat4_identity();

  nhm_float_t xx = quaternion.x * quaternion.x;
  nhm_float_t yy = quaternion.y * quaternion.y;
  nhm_float_t zz = quaternion.z * quaternion.z;
  nhm_float_t xy = quaternion.x * quaternion.y;
  nhm_float_t xz = quaternion.x * quaternion.z;
  nhm_float_t yz = quaternion.y * quaternion.z;
  nhm_float_t wx = quaternion.w * quaternion.x;
  nhm_float_t wy = quaternion.w * quaternion.y;
  nhm_float_t wz = quaternion.w * quaternion.z;

  out.elements[0][0] = 1.0 - 2.0 * (yy + zz);
  out.elements[0][1] = 2.0 * (xy + wz);
  out.elements[0][2] = 2.0 * (xz - yz);

  out.elements[1][0] = 2.0 * (xy - wz);
  out.elements[1][1] = 1.0 - 2.0 * (xx + zz);
  out.elements[1][2] = 2.0 * (yz + wx);
  
  out.elements[2][0] = 2.0 * (xz + wy);
  out.elements[2][1] = 2.0 * (yz - wx);
  out.elements[2][2] = 1.0 - 2.0 * (xx + yy);

  return out;

}

nhm_vec4_t nhm_vec4_add(nhm_vec4_t left, nhm_vec4_t right) {

  nhm_vec4_t vec4;

  vec4.x = left.x + right.x;
  vec4.y = left.y + right.y;
  vec4.z = left.z + right.z;
  vec4.w = left.w + right.w;

  return vec4;

}

nhm_vec4_t nhm_vec4_subtract(nhm_vec4_t left, nhm_vec4_t right) {

  nhm_vec4_t vec4;

  vec4.x = left.x - right.x;
  vec4.y = left.y - right.y;
  vec4.z = left.z - right.z;
  vec4.w = left.w - right.w;

  return vec4;

}

nhm_vec4_t nhm_vec4_multiply(nhm_vec4_t left, nhm_vec4_t right) {

  nhm_vec4_t vec4;

  vec4.x = left.x * right.x;
  vec4.y = left.y * right.y;
  vec4.z = left.z * right.z;
  vec4.w = left.w * right.w;

  return vec4;  

}

nhm_vec4_t nhm_vec4_multiply_scalar(nhm_vec4_t left, nhm_float_t right) {

  nhm_vec4_t vec4;

  vec4.x = left.x * right;
  vec4.y = left.y * right;
  vec4.z = left.z * right;
  vec4.w = left.w * right;

  return vec4;

}

nhm_vec4_t nhm_vec4_divide(nhm_vec4_t left, nhm_vec4_t right) {

  nhm_vec4_t vec4;

  vec4.x = left.x / right.x;
  vec4.y = left.y / right.y;
  vec4.z = left.z / right.z;
  vec4.w = left.w / right.w;

  return vec4;

}

nhm_vec4_t nhm_vec4_divide_scalar(nhm_vec4_t left, nhm_float_t right) {

  nhm_vec4_t vec4;

  vec4.x = left.x / right;
  vec4.y = left.y / right;
  vec4.z = left.z / right;
  vec4.w = left.w / right;

  return vec4;
  
}

nhm_vec4_t nhm_vec4_cross_product(nhm_vec4_t left, nhm_vec4_t right) {

  nhm_vec4_t vec4;

  vec4.x = (left.x * right.z) - (left.z * right.y);
  vec4.y = (left.z * right.x) - (left.x * right.z);
  vec4.z = (left.x * right.y) - (left.y * right.x);

  vec4.w = 0;

  return vec4;

}

nhm_float_t nhm_vec4_dot_product(nhm_vec4_t left, nhm_vec4_t right) {

  return (left.x * right.x) + (left.y * right.y) + (left.z * right.z) + (left.w * right.w);

}

nhm_vec4_t nhm_vec4_normalise(nhm_vec4_t vec4) {
  return nhm_vec4_divide_scalar(vec4, NHM_SQRT(nhm_vec4_dot_product(vec4, vec4)));
}

nhm_float_t nhm_vec4_length(nhm_vec4_t vec4) {
  return NHM_SQRT(nhm_vec4_dot_product(vec4, vec4));
}

nhm_float_t nhm_vec4_length_squared(nhm_vec4_t vec4) {
  return nhm_vec4_dot_product(vec4, vec4);
}

nhm_quaternion_t nhm_quaternion_add(nhm_quaternion_t left, nhm_quaternion_t right) {

  nhm_quaternion_t quaternion;

  quaternion.x = left.x + right.x;
  quaternion.y = left.y + right.y;
  quaternion.z = left.z + right.z;
  quaternion.w = left.w + right.w;

  return quaternion;
   
}

nhm_quaternion_t nhm_quaternion_subtract(nhm_quaternion_t left, nhm_quaternion_t right) {

  nhm_quaternion_t quaternion;

  quaternion.x = left.x - right.x;
  quaternion.y = left.y - right.y;
  quaternion.z = left.z - right.z;
  quaternion.w = left.w - right.w;

  return quaternion;

}

nhm_quaternion_t nhm_quaternion_multiply(nhm_quaternion_t left, nhm_quaternion_t right) {

  nhm_quaternion_t quaternion;

  quaternion.x = (left.x * right.w) + (left.y * right.z) - (left.z * right.y) + (left.w * right.x);
  quaternion.y = (-left.x * right.z) + (left.y * right.w) + (left.z * right.x) + (left.w * right.y);
  quaternion.z = (left.x * right.y) - (left.y * right.x) + (left.z * right.w) + (left.w * right.z);
  quaternion.w = (-left.x * right.x) - (left.y * right.y) - (left.z * right.z) + (left.w * right.w);

  return quaternion;

}

nhm_quaternion_t nhm_quaternion_multiply_scalar(nhm_quaternion_t left, nhm_float_t right) {

  nhm_quaternion_t quaternion;

  quaternion.x = left.x * right;
  quaternion.y = left.y * right;
  quaternion.z = left.z * right;
  quaternion.w = left.w * right;

  return quaternion;
 
}

nhm_quaternion_t nhm_quaternion_divide_scalar(nhm_quaternion_t left, nhm_float_t right) {

  nhm_quaternion_t quaternion;

  quaternion.x = left.x / right;
  quaternion.y = left.y / right;
  quaternion.z = left.z / right;
  quaternion.w = left.w / right;

  return quaternion;

}

nhm_quaternion_t nhm_quaternion_inverse(nhm_quaternion_t quaternion_in) {

  nhm_quaternion_t quaternion;

  nhm_float_t length_squared = (quaternion_in.x * quaternion_in.x) + (quaternion_in.y * quaternion_in.y) + (quaternion_in.z * quaternion_in.z);

  quaternion.x = -quaternion_in.x / length_squared;
  quaternion.y = -quaternion_in.y / length_squared;
  quaternion.z = -quaternion_in.z / length_squared;
  quaternion.w = quaternion_in.w / length_squared;

  return quaternion;

}

nhm_quaternion_t nhm_quaternion_normalise(nhm_quaternion_t quaternion) {

  nhm_float_t length = NHM_SQRT(quaternion.x * quaternion.x + quaternion.y * quaternion.y + quaternion.z * quaternion.z + quaternion.w * quaternion.w);

  return nhm_quaternion_divide_scalar(quaternion, length);
  
}

nhm_mat4_t nhm_mat4_add(nhm_mat4_t left, nhm_mat4_t right) {
  nhm_mat4_t out;
  for (int i = 0; i < 16; i++) {
    out[i] = left[i] + right[i];
  }
  return out;
}

nhm_mat4_t nhm_mat4_subtract(nhm_mat4_t left, nhm_mat4_t right) {
  nhm_mat4_t out;
  for (int i = 0; i < 16; i++) {
    out[i] = left[i] - right[i];
  }
  return out;
}

nhm_mat4_t nhm_mat4_multiply(nhm_mat4_t left, nhm_mat4_t right) {

  nhm_mat4_t out;

  for (int col = 0; col < 4; col++) {
    for (int row = 0; row < 4; row++) {

      nhm_float_t sum = 0;
      for (int i = 0; i < 4; i++) {
        sum += left.elements[i * 4 + row] * right.elements[col * 4 + i];
      }
      out.elements[col * 4 + row] = sum;

    }
  }

  return out;
}

nhm_mat4_t nhm_mat4_multiply_scalar(nhm_float_t left, nhm_mat4_t right) {
  nhm_mat4_t out;
  for (int i = 0; i < 16; i++) {
    out[i] = left * right[i]
  }
  return out;
}

nhm_vec4_t nhm_mat4_multiply_vec4(nhm_vec4_t left, nhm_mat4_t right) {

  nhm_vec4_t out;
  nhm_float_t* out_elements = (nhm_float_t*)&out;

  nhm_float_t* left_elements = (nhm_float_t*)&left;

  for (int row = 0; row < 4; row++) {
    nhm_float_t sum = 0;
    for (int col = 0; col < 4; col++) {
      sum += left_elements[col] * right.elements[col * 4 + row];
    }
    out_elements[row] = sum;
  }

  return out;

}

// TODO: Implement this.
nhm_mat4_t nhm_mat4_inverse(nhm_mat4_t mat4) {
  
}

nhm_mat4_t nhm_mat4_transpose(nhm_mat4_t mat4) {
  nhm_mat4_t out;
  
  for(int col = 0; col < 4; col++) {
    for(int row = 0; row < 4; row++) {
      out.elements[col * 4 + row] = mat4.elements[row * 4 + col];
    }
  }
  
  return out;
}

#endif
