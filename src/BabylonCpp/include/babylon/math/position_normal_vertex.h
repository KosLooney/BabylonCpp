#ifndef BABYLON_MATH_POSITION_NORMAL_VERTEX_H
#define BABYLON_MATH_POSITION_NORMAL_VERTEX_H

#include <babylon/babylon_global.h>

#include <babylon/math/vector3.h>

namespace BABYLON {

/**
 * @brief Represents a PositionNormalVertex.
 */
class BABYLON_SHARED_EXPORT PositionNormalVertex {

public:
  PositionNormalVertex();
  PositionNormalVertex(const Vector3& position, const Vector3& normal);
  PositionNormalVertex(const PositionNormalVertex& other);
  PositionNormalVertex(PositionNormalVertex&& other);
  PositionNormalVertex& operator=(const PositionNormalVertex& other);
  PositionNormalVertex& operator=(PositionNormalVertex&& other);
  ~PositionNormalVertex();
  PositionNormalVertex copy() const;
  unique_ptr_t<PositionNormalVertex> clone() const;
  friend std::ostream&
  operator<<(std::ostream& os,
             const PositionNormalVertex& positionNormalVertex);

public:
  Vector3 position;
  Vector3 normal;

}; // end of class PositionNormalVertex

std::ostream& operator<<(std::ostream& os,
                         const PositionNormalVertex& positionNormalVertex);

} // end of namespace BABYLON

#endif // end of BABYLON_MATH_POSITION_NORMAL_VERTEX_H
