#ifndef BABYLON_MESH_CSG_NODE_H
#define BABYLON_MESH_CSG_NODE_H

#include <babylon/babylon_api.h>
#include <babylon/mesh/csg/csg.h>
#include <babylon/mesh/csg/polygon.h>

namespace BABYLON {
namespace CSG {

/**
 * @brief class Node
 *
 * Holds a node in a BSP tree. A BSP tree is built from a collection of
 * polygons by picking a polygon to split along. That polygon (and all other
 * coplanar polygons) are added directly to that node and the other polygons are
 * added to the front and/or back subtrees. This is not a leafy BSP tree since
 * there is no distinction between internal and leaf nodes.
 */
class BABYLON_SHARED_EXPORT Node {

public:
  Node();
  Node(const std::vector<Polygon>& polygons);
  ~Node();

  std::unique_ptr<Node> clone();

  // Convert solid space to empty space and empty space to solid space.
  void invert();

  // Recursively remove all polygons in `polygons` that are inside this BSP
  // tree.
  std::vector<Polygon> clipPolygons(const std::vector<Polygon>& polygons);

  // Remove all polygons in this BSP tree that are inside the other BSP tree
  // `bsp`.
  void clipTo(Node& bsp);

  // Return a list of all polygons in this BSP tree.
  std::vector<Polygon> allPolygons();

  // Build a BSP tree out of `polygons`. When called on an existing tree, the
  // new polygons are filtered down to the bottom of the tree and become new
  // nodes there. Each set of polygons is partitioned using the first polygon
  // (no heuristic is used to pick a good split).
  void build(const std::vector<Polygon>& polygons);

private:
  std::unique_ptr<Plane> _plane;
  std::unique_ptr<Node> _front;
  std::unique_ptr<Node> _back;
  std::vector<Polygon> _polygons;

}; // end of class Node

} // end of namespace CSG
} // end of namespace BABYLON

#endif // end of BABYLON_MESH_CSG_NODE_H
