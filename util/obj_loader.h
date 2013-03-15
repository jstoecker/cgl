#ifndef CGL_OBJ_LOADER_H_
#define CGL_OBJ_LOADER_H_

#include <vector>
#include <map>
#include "math/cgl_math.h"

namespace cgl
{
  
  struct ObjVertex
  {
    cgl::Vec3 position;
    cgl::Vec2 texCoord;
    cgl::Vec3 normal;
  };
  
  struct ObjModel
  {
    std::vector<ObjVertex> vertices;
    std::vector<int> indices; // change to vector<objpart>
    cgl::Vec3 min;
    cgl::Vec3 max;
    bool textured;
  };
  
  // ObjPart : name, indices, material
  // ObjMaterial : textures, color properties
  
  class ObjLoader
  {
  public:
    
    void load(const char* fileName, ObjModel* model);
    
  private:
    ObjModel* model_;
    
    // Vertex positions read from input.
    std::vector<cgl::Vec3> v_;
    
    // Vertex texture coordinates read from input.
    std::vector<cgl::Vec2> vt_;
    
    // Vertex normals read from input.
    std::vector<cgl::Vec3> vn_;
    
    // Current smoothing group number.
    int smoothGroup;
    
    // Each smoothing group owns a set of indices to obj vertices in the output
    // model. This way, input vertices will be duplicated if they are in
    // separate smoothing groups, which is necessary for unique normals.
    std::map<int, std::map<std::string, int> > vertexMaps;
    
    // Each input triplet in the obj file maps to an index for a vertex in the
    // output model. This maps stores the mapping for the current smoothGroup.
    std::map<std::string, int>* vertexMap;
    
    void parseLine(std::string& line);
    void parseFace(std::istringstream& iss);
  };
  
}

#endif
