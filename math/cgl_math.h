#ifndef CGL_MATH_H_
#define CGL_MATH_H_

#include <cmath>
#include <algorithm>

namespace cgl
{

  static const float PI          = 3.1415926536f;
  static const float PI2         = 2.0f * PI;
  static const float DEG_TO_RAD  = 0.0174532925f;
  static const float RAD_TO_DEG  = 57.295779513f;
  
  /// Returns the value clamped to be in [min, max].
  template <typename T> T clamp(T value, T min, T max)
  {
    return std::min(std::max(value, min), max);
  }
  
  /// Returns the linear interpolation of a and b given a weight w. Returns a
  /// when w == 0, and b when w == 1; if w is not in [0,1] it extrapolates.
  template <typename T> T lerp(const T& a, const T& b, float w)
  {
    return a + (b - a) * w;
  }
  
  template <typename T> class Vector2;
  template <typename T> class Vector3;
  template <typename T> class Vector4;
  template <typename T> class Matrix2;
  template <typename T> class Matrix3;
  template <typename T> class Matrix4;
  
  typedef Vector2<float> Vec2;
  typedef Vector2<double> Vec2d;
  typedef Vector3<float> Vec3;
  typedef Vector3<double> Vec3d;
  typedef Vector4<float> Vec4;
  typedef Vector4<double> Vec4d;
  
  typedef Matrix2<float> Mat2;
  typedef Matrix2<double> Mat2d;
  typedef Matrix3<float> Mat3;
  typedef Matrix3<double> Mat3d;
  typedef Matrix4<float> Mat4;
  typedef Matrix4<double> Mat4d;
  
} // namespace cgl

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix2.h"
#include "matrix3.h"
#include "matrix4.h"
#include "transform.h"

#endif
