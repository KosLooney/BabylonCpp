#ifndef BABYLON_TOOLS_PACKED_RECT_H
#define BABYLON_TOOLS_PACKED_RECT_H

#include <babylon/babylon_global.h>
#include <babylon/math/size.h>
#include <babylon/math/vector2.h>

namespace BABYLON {

/**
 * @brief This class describe a rectangle that were added to the map. You have
 * access to its coordinates either in pixel or normalized (UV).
 */
class BABYLON_SHARED_EXPORT PackedRect {

public:
  PackedRect(PackedRect* root, PackedRect* parent, const Vector2& pos,
             const Size& size);
  ~PackedRect();

  /**
   * @brief Returns the position of this node into the map.
   */
  const Vector2& pos() const;

  /**
   * @brief Returns the size of the rectangle this node handles.
   */
  Size* contentSize() const;

  /**
   * @brief Retrieve the inner position (considering the margin) and stores it
   * into the res object.
   * @param res must be a valid Vector2 that will contain the inner position
   * after this call.
   */
  void getInnerPosToRef(Vector2& res);

  /**
   * @brief Retrieve the inner size (considering the margin) and stores it into
   * the res object.
   * @param res must be a valid Size that will contain the inner size after this
   * call.
   */
  void getInnerSizeToRef(Size& res);

  /**
   * @brief Compute the UV of the top/left, top/right, bottom/right, bottom/left
   * points of the rectangle this node handles into the map
   * @returns And array of 4 Vector2, containing UV coordinates for the four
   * corners of the Rectangle into the map
   */
  vector_t<Vector2> UVs();

  /**
   * @brief You may have allocated the PackedRect using over-provisioning (you
   * allocated more than you need in order to prevent frequent
   * deallocations/reallocations)
   * and then using only a part of the PackRect.
   * This method will return the UVs for this part by given the custom size of
   * what you really use
   * @param customSize must be less/equal to the allocated size, UV will be
   * compute from this
   */
  vector_t<Vector2> getUVsForCustomSize(const Size& customSize);

  /**
   * @brief Free this rectangle from the map.
   * Call this method when you no longer need the rectangle to be in the map.
   */
  void freeContent();

  bool isUsed() const;

  PackedRect* findAndSplitNode(const Size& contentSize);
  size_t evalFreeSize(const size_t& size);

private:
  PackedRect* findNode(const Size& size);
  PackedRect* splitNode(const Size& contentSize);
  void attemptDefrag();
  void clearNode();
  bool isRecursiveFree() const;

protected:
  PackedRect* _root;
  PackedRect* _parent;
  Size _size;

private:
  static Size TpsSize;

private:
  std::unique_ptr<Size> _contentSize;
  std::unique_ptr<Size> _initialSize;
  std::unique_ptr<PackedRect> _leftNode;
  std::unique_ptr<PackedRect> _rightNode;
  std::unique_ptr<PackedRect> _bottomNode;
  Vector2 _pos;

}; // end of class PackedRect

} // end of namespace BABYLON

#endif // end of BABYLON_TOOLS_PACKED_RECT_H
