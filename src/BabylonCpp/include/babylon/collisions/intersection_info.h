#ifndef BABYLON_COLLISIONS_INTERSECTIONINFO_H
#define BABYLON_COLLISIONS_INTERSECTIONINFO_H

#include <babylon/babylon_api.h>
#include <babylon/babylon_common.h>

namespace BABYLON {

/**
 * @brief Hidden
 */
class BABYLON_SHARED_EXPORT IntersectionInfo {

public:
  IntersectionInfo(float distance);
  IntersectionInfo(float bu, float bv, float distance);
  ~IntersectionInfo();

public:
  float bu;
  float bv;
  float distance;
  size_t faceId;
  int subMeshId;

}; // end of class IntersectionInfo

} // end of namespace BABYLON

#endif // end of BABYLON_COLLISIONS_INTERSECTIONINFO_H
