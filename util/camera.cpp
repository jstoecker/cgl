#include "camera.h"

using namespace cgl;

Camera::Camera()
{}

const Vec3& Camera::eye() const
{
  return eye_;
}

const Vec3& Camera::up() const
{
  return up_;
}

const Vec3& Camera::right() const
{
  return right_;
}

const Vec3& Camera::forward() const
{
  return forward_;
}

const Mat4& Camera::view() const
{
  return view_;
}

const Mat4& Camera::projection() const
{
  return projection_;
}

void Camera::rotateX(float radians)
{
  view_ = view_ * rotationX(radians);
  viewInverse_ = rotationX(-radians) * viewInverse_;
  update();
}

void Camera::rotateY(float radians)
{
  view_ = view_ * rotationY(radians);
  viewInverse_ = rotationY(-radians) * viewInverse_;
  update();
}

void Camera::rotateZ(float radians)
{
  view_ = view_ * rotationZ(radians);
  viewInverse_ = rotationZ(-radians) * viewInverse_;
  update();
}

void Camera::rotate(float radians, Vec3 axis)
{
  view_ = view_ * rotation(radians, axis);
  viewInverse_ = rotation(-radians, axis) * viewInverse_;
  update();
}

void Camera::translate(float x, float y, float z)
{
  view_ = view_ * translation(x, y, z);
  viewInverse_ = translation(-x, -y, -z) * viewInverse_;
  update();
}

void Camera::pitch(float radians)
{
  rotate(radians, right_);
}

void Camera::roll(float radians)
{
  rotate(radians, forward_); 
}

void Camera::yaw(float radians)
{
  rotate(radians, up_);
}

void Camera::translate(const Vec3& t)
{
  translate(t.x, t.y, t.z);
}

void Camera::translateForward(float units)
{
  translate(forward_ * units);
}

void Camera::translateBackward(float units)
{
  translate(forward_ * -units);
}

void Camera::translateRight(float units)
{
  translate(right_ * units);
}

void Camera::translateLeft(float units)
{
  translate(right_ * -units);
}

void Camera::translateUp(float units)
{
  translate(up_ * units);
}

void Camera::translateDown(float units)
{
  translate(up_ * -units);
}

void Camera::update()
{
  right_ = viewInverse_.col(0);
  up_ = viewInverse_.col(1);
  forward_ = viewInverse_.col(2) * -1.0f;
  eye_ = viewInverse_.col(3);
}

void Camera::setView(const Mat4& view)
{
  view_ = view;
  viewInverse_ = view.inverse();
  update();
}

void Camera::setProjection(const Mat4& projection)
{
  projection_ = projection;
}
