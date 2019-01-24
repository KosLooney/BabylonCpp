#ifndef BABYLON_COLLISIONS_UPDATE_PAYLOAD_H
#define BABYLON_COLLISIONS_UPDATE_PAYLOAD_H

#include <unordered_map>

#include <babylon/babylon_api.h>
#include <babylon/collisions/serialized_geometry.h>
#include <babylon/collisions/serialized_mesh.h>

namespace BABYLON {

/**
 * @brief Hidden
 */
struct BABYLON_SHARED_EXPORT UpdatePayload {
  std::unordered_map<unsigned int, SerializedMesh> updatedMeshes;
  std::unordered_map<std::string, SerializedGeometry> updatedGeometries;
  Uint32Array removedMeshes;
  std::vector<std::string> removedGeometries;
}; // end of struct UpdatePayload

} // end of namespace BABYLON

#endif // end of BABYLON_COLLISIONS_UPDATE_PAYLOAD_H
