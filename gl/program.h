#ifndef CGL_PROGRAM_H_
#define CGL_PROGRAM_H_

#include <vector>
#include "cgl.h"

namespace cgl
{
  class Shader;
  struct GLProgramObject;

  /// GLSL program reference.
  class Program
  {
  public:
    /// Creates a new empty program reference.
    Program();

    /// Creates a new program reference.
    Program(GLuint id);

    /// Returns the handle to the referenced program. Returns 0 if no valid
    /// program is referenced.
    GLuint id() const;

    /// Returns the info log from failed linking or validating.
    std::string log() const;

    /// Returns a named uniform variable's location or -1 if it is not active.
    GLint getUniformLocation(const GLchar* name) const;

    /// Returns a vector of references to all attached shaders.
    std::vector<Shader> shaders() const;

    /// Attaches a GLSL shader to the program. If this object does not yet
    /// reference a program, a new one will be created.
    void attach(const Shader& shader);

    /// Detaches a GLSL shader from the program.
    void detach(const Shader& shader);

    /// Removes all shaders from the program.
    void detachAll();

    /// Links the attached shaders.
    bool link();

    /// Checks to see whether the executables contained in this program can
    /// execute given the current OpenGL state.
    bool validate() const;

    /// Sets the active program to this.
    void bind() const;

    /// Sets the active program to 0.
    void unbind() const;

    /// Deletes the referenced program from the OpenGL context. If 
    /// deleteAttached is true, all attached shaders will also be deleted.
    void release(bool deleteAttached);

    /// Sets a uniform variable's using a float.
    void set(const GLchar*, GLfloat);

    /// Sets a uniform variable's value using two floats.
    void set(const GLchar*, GLfloat, GLfloat);

    /// Sets a uniform variable's value using two floats.
    void set(const GLchar*, const Vec2&);

    /// Sets a uniform variable's value using three floats.
    void set(const GLchar*, GLfloat, GLfloat, GLfloat);

    /// Sets a uniform variable's value using four floats.
    void set(const GLchar*, const Vec3&);

    /// Sets a uniform variable's value using four floats.
    void set(const GLchar*, GLfloat, GLfloat, GLfloat, GLfloat);

    /// Sets a uniform variable's value using three floats.
    void set(const GLchar*, const Vec4&);

    /// Sets a uniform variable array using count 2-tuples of type float.
    void set2(const GLchar*, GLsizei count, const GLfloat*);

    /// Sets a uniform variable array using count 3-tuples of type float.
    void set3(const GLchar*, GLsizei count, const GLfloat*);

    /// Sets a uniform variable array using count 4-tuples of type float.
    void set4(const GLchar*, GLsizei count, const GLfloat*);

    /// Sets a uniform variable's using an integer.
    void set(const GLchar*, GLint);

    /// Sets a uniform variable's using two integers.
    void set(const GLchar*, GLint, GLint);

    /// Sets a uniform variable's using three integers.
    void set(const GLchar*, GLint, GLint, GLint);

    /// Sets a uniform variable's using four integers.
    void set(const GLchar*, GLint, GLint, GLint, GLint);

    /// Sets a uniform variable array using count 2-tuples of type int.
    void set2(const GLchar*, GLsizei count, const GLint*);

    /// Sets a uniform variable array using count 2-tuples of type int.
    void set3(const GLchar*, GLsizei count, const GLint*);

    /// Sets a uniform variable array using count 2-tuples of type int.
    void set4(const GLchar*, GLsizei count, const GLint*);
    
    /// Sets a uniform 4x4 matrix.
    void set(const GLchar*, const Mat4&);

  private:
    GLProgramObject* obj_;
  };

} // namespace cgl

#endif // CGL_PROGRAM_H_
