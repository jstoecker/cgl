#ifndef CGL_UNIFORM_H_
#define CGL_UNIFORM_H_

#include <iostream>
#include "cgl.h"

namespace cgl
{
  
  /// Reference to a GLSL uniform variable.
  class Uniform
  {
  public:
    Uniform();
    Uniform(GLuint program, GLint location, GLint size, GLenum type,
            std::string name);
    
    GLint size() const;
    
    std::string name() const;
    
    GLint location() const;
    
    GLenum type() const;
    
    /// Retrieves the current uniform value and stores it in the buffer.
    void get(float* buffer) const;
    
    /// Retrieves the current uniform value and stores it in the buffer.
    void get(int* buffer) const;
    
    void set(GLfloat);
    void set(GLfloat, GLfloat);
    void set(GLfloat, GLfloat, GLfloat);
    void set(GLfloat, GLfloat, GLfloat, GLfloat);
    void set2(GLsizei count, const GLfloat*);
    void set3(GLsizei count, const GLfloat*);
    void set4(GLsizei count, const GLfloat*);
    void set(const Vec2&);
    void set(const Vec3&);
    void set(const Vec4&);
    void set(GLint);
    void set(GLint, GLint);
    void set(GLint, GLint, GLint);
    void set(GLint, GLint, GLint, GLint);
    void set2(GLsizei count, const GLint*);
    void set3(GLsizei count, const GLint*);
    void set4(GLsizei count, const GLint*);
    void set4x4(GLsizei count, const GLfloat*);
    void set(const Mat4&);
    
    friend std::ostream& operator<<(std::ostream&, const Uniform&);
    
  private:
    GLuint program_;
    GLint location_;
    std::string name_;
    GLint size_;
    GLenum type_;
  };
  
} // namespace cgl

#endif
