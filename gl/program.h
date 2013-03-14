#ifndef CGL_PROGRAM_H_
#define CGL_PROGRAM_H_

#include <vector>
#include <iostream>
#include "cgl.h"

namespace cgl
{
  class Shader;
  class Uniform;
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

    /// Returns a vector of references to all attached shaders.
    std::vector<Shader> shaders() const;

    /// Returns a reference to a named uniform variable in this program.
    Uniform uniform(const char* name) const;

    /// Returns references to all the active uniforms in the program.
    std::vector<Uniform> uniforms() const;

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

    /// Deletes the referenced program from the OpenGL context. If deleteAttached
    /// is true, all attached shaders will also be deleted.
    void glDelete(bool deleteAttached);

    friend std::ostream& operator<<(std::ostream&, const Program&);

  private:
    GLProgramObject* obj_;
  };

} // namespace cgl

#endif // CGL_PROGRAM_H_
