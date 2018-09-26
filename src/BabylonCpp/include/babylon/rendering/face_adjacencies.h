#ifndef BABYLON_RENDERING_FACE_ADJACENCIES_H
#define BABYLON_RENDERING_FACE_ADJACENCIES_H

#include <babylon/babylon_api.h>
#include <babylon/math/vector3.h>

namespace BABYLON {

/**
 * @brief FaceAdjacencies Helper class to generate edges.
 */
class BABYLON_SHARED_EXPORT FaceAdjacencies {

public:
  Int32Array edges;
  Vector3 p0;
  Vector3 p1;
  Vector3 p2;
  int edgesConnectedCount = 0;

}; // end of class FaceAdjacencies

} // end of namespace BABYLON

#endif // end of BABYLON_RENDERING_FACE_ADJACENCIES_H
