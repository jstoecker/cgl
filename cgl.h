#ifndef CGL_H_
#define CGL_H_

// TODO: check for GL3 define and include the GL3 headers
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "math/cgl_math.h"

#include "gl/program.h"
#include "gl/shader.h"
#include "gl/uniform.h"
#include "gl/texture.h"
#include "gl/viewport.h"

#include "util/camera.h"

#endif
