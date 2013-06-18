#include "obj_loader.h"
#include <fstream>
#include <sstream>
#include <map>
#include <limits>

using namespace cgl;

void ObjLoader::load(const char* fileName, ObjModel* model)
{
  model_ = model;
  model_->min = Vec3(std::numeric_limits<float>::infinity());
  model_->max = Vec3(-std::numeric_limits<float>::infinity());
  smoothGroup = 1;
  vertexMap = &vertexMaps[smoothGroup];
  
  // parse file line by line
  std::ifstream infile(fileName);
  std::string line;
  while (std::getline(infile, line)) {
    parseLine(line);
  }
  
  // make sure normals are all unit length
  for (std::vector<ObjVertex>::iterator it = model_->vertices.begin();
       it != model_->vertices.end();
       ++it)
  {
    it->normal.normalize();
  }
  
  // clear temporary storage
  v_.clear();
  vt_.clear();
  vn_.clear();
  model_ = NULL;
}

void ObjLoader::parseLine(std::string& line)
{
  std::istringstream iss(line);
  std::string prefix;
  iss >> prefix;
  
  if (prefix == "v") {
    Vec3 position;
    iss >> position.x >> position.y >> position.z;
    if (position.x < model_->min.x) model_->min.x = position.x;
    if (position.x > model_->max.x) model_->max.x = position.x;
    if (position.y < model_->min.y) model_->min.y = position.y;
    if (position.y > model_->max.y) model_->max.y = position.y;
    if (position.z < model_->min.z) model_->min.z = position.z;
    if (position.z > model_->max.z) model_->max.z = position.z;
    v_.push_back(position);
    
  } else if (prefix == "vt") {
    Vec2 texCoord;
    iss >> texCoord.x >> texCoord.y;
    vt_.push_back(texCoord);
    
  } else if (prefix == "vn") {
    Vec3 normal;
    iss >> normal.x >> normal.y >> normal.z;
    vn_.push_back(normal);
    
  } else if (prefix == "s") {
    iss >> smoothGroup;
    vertexMap = &vertexMaps[smoothGroup];
    
  } else if (prefix == "f") {
    parseFace(iss);
  }
}

inline void parseTriplet(std::string& triplet, int& v, int& vt, int& vn)
{
  size_t i = triplet.find("/");
  if (i == -1) {
    // format: v
    v = atoi(triplet.c_str()) - 1;
    vt = -1;
    vn = -1;
  } else {
    size_t j = triplet.rfind("/");
    if (i == j) {
      // format: v/vt
      v = atoi(triplet.substr(0, i).c_str()) - 1;
      vt = atoi(triplet.substr(j+1).c_str()) - 1;
      vn = -1;
    } else if (i == j - 1) {
      // format: v//vn
      v = atoi(triplet.substr(0, i).c_str()) - 1;
      vt = -1;
      vn = atoi(triplet.substr(j+1).c_str()) - 1;
    } else {
      // format: v/vt/vn
      v = atoi(triplet.substr(0, i).c_str()) - 1;
      vt = atoi(triplet.substr(i+1, j-i).c_str()) - 1;
      vn = atoi(triplet.substr(j+1).c_str()) - 1;
    }
  }
}

void ObjLoader::parseFace(std::istringstream& iss)
{
  int numVerts = 0;
  std::string triplet;
  bool useFaceNormal = false;
  while (iss >> triplet) {
    numVerts++;
    int v, vt, vn;
    parseTriplet(triplet, v, vt, vn);
    useFaceNormal = useFaceNormal || vn < 0;
    
    // split polygons into triangles using a triangle fan
    if (numVerts > 3) {
      model_->indices.push_back(model_->indices[model_->indices.size() - numVerts + 1]);
      model_->indices.push_back(model_->indices[model_->indices.size() - 2]);
    }
    
    // if no smoothing group or the vertex hasn't been seen, create a new one
    if (!smoothGroup || vertexMap->find(triplet) == vertexMap->end()) {
      ObjVertex vert = {
        v_[v],
        (vt < 0) ? Vec2() : vt_[vt],
        (vn < 0) ? Vec3() : vn_[vn] };
      int index = static_cast<int>(model_->vertices.size());
      model_->indices.push_back(index);
      model_->vertices.push_back(vert);
      (*vertexMap)[triplet] = index;
    } else {
      model_->indices.push_back((*vertexMap)[triplet]);
    }
  }
  
  if (useFaceNormal) {
    int indicesAdded = 3 + 3 * (numVerts - 3);
    int n = static_cast<int>(model_->indices.size());
    Vec3 a = model_->vertices[model_->indices[n - indicesAdded]].position;
    Vec3 b = model_->vertices[model_->indices[n - indicesAdded + 1]].position;
    Vec3 c = model_->vertices[model_->indices[n - indicesAdded + 2]].position;
    Vec3 normal = (b-a).cross(c-a).normalize();
    for (int i = n - indicesAdded; i < n; ++i) {
      model_->vertices[ model_->indices[i]].normal += normal;
    }
  }
}