#ifndef CGL_CAMERA_H_
#define CGL_CAMERA_H_

#include "math/cgl_math.h"

namespace cgl
{

class Camera
{
public:
  /// Creates a camera. Initially, the view and projection are identity matrices.
  Camera();

  /// Returns the view matrix.
  const Mat4& view() const;

  /// Returns the projection matrix.
  const Mat4& projection() const;

  /// Returns the eye position in world coordinates; origin in eye coordinates.
  const Vec3& eye() const;

  /// Returns the up axis in world coordinates; (0, 1, 0) in eye coordinates.
  const Vec3& up() const;

  /// Returns the right axis in world coordinates; (1, 0, 0) in eye coordinates.
  const Vec3& right() const;

  /// Returns the forward axis in world coordinates; (0, 0, -1) in eye coordinates.
  const Vec3& forward() const;

  /// Assigns a new view matrix.
  void setView(const Mat4& view);

  /// Assigns a projection matrix.
  void setProjection(const Mat4& projection);

  /// Adds a rotation of radians around axis.
  void rotate(float radians, Vec3 axis);

  /// Adds a rotation of radians around the X axis.
  void rotateX(float radians);

  /// Adds a rotation of radians around the Y axis.
  void rotateY(float radians);

  /// Adds a rotation of radians around the Z axis.
  void rotateZ(float radians);

  /// Adds a rotation of radians around the right axis.
  void pitch(float radians);

  /// Adds a rotation of radians around the forward axis.
  void roll(float radians);

  /// Adds a rotation of radians around the up axis.
  void yaw(float radians);

  /// Adds a translation of (x, y, z) in world coordinates.
  void translate(float x, float y, float z);

  /// Adds a translation of t in world coordinates.
  void translate(const Vec3& t);

  /// Adds a translation along the right axis.
  void translateRight(float units);

  /// Adds a translation along the left axis.
  void translateLeft(float units);

  /// Adds a translation along the up axis.
  void translateUp(float units);

  /// Adds a translation along the down axis.
  void translateDown(float units);

  /// Adds a translation along the forward axis.
  void translateForward(float units);

  /// Adds a translation along the backward axis.
  void translateBackward(float units);

private:
  Mat4 view_;
  Mat4 viewInverse_;
  Mat4 projection_;
  Vec3 eye_;
  Vec3 up_;
  Vec3 right_;
  Vec3 forward_;

  void update();
};

} // namespace cgl

#endif // CGL_CAMERA_H_
