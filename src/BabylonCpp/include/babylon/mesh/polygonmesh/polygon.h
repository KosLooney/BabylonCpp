#ifndef BABYLON_MESH_POLYGONMESH_POLYGON_H
#define BABYLON_MESH_POLYGONMESH_POLYGON_H

#include <babylon/babylon_api.h>
#include <babylon/babylon_common.h>

namespace BABYLON {

class Path2;
class Vector2;

/**
 * @brief
 */
struct BABYLON_SHARED_EXPORT Polygon {

  static std::vector<Vector2> Rectangle(float xmin, float ymin, float xmax,
                                        float ymax);
  static std::vector<Vector2> Circle(float radius, float cx = 0.f,
                                     float cy = 0.f, size_t numberOfSides = 32);
  static std::vector<Vector2> Parse(const std::string& input);
  static Path2 StartingAt(float x, float y);

}; // end of class Polygon

} // end of namespace BABYLON

#endif // end of BABYLON_MESH_POLYGONMESH_POLYGON_H
