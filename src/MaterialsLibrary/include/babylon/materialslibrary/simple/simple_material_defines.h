#ifndef BABYLON_MATERIALS_LIBRARY_SIMPLE_SIMPLE_MATERIAL_DEFINES_H
#define BABYLON_MATERIALS_LIBRARY_SIMPLE_SIMPLE_MATERIAL_DEFINES_H

#include <babylon/babylon_global.h>
#include <babylon/materials/material_defines.h>

namespace BABYLON {
namespace MaterialsLibrary {

struct BABYLON_SHARED_EXPORT SimpleMaterialDefines : public MaterialDefines {

  static constexpr unsigned int DIFFUSE          = 0;
  static constexpr unsigned int CLIPPLANE        = 1;
  static constexpr unsigned int ALPHATEST        = 2;
  static constexpr unsigned int POINTSIZE        = 3;
  static constexpr unsigned int FOG              = 4;
  static constexpr unsigned int NORMAL           = 5;
  static constexpr unsigned int UV1              = 6;
  static constexpr unsigned int UV2              = 7;
  static constexpr unsigned int VERTEXCOLOR      = 8;
  static constexpr unsigned int VERTEXALPHA      = 9;
  static constexpr unsigned int INSTANCES        = 10;
  static constexpr unsigned int LOGARITHMICDEPTH = 11;
  static constexpr unsigned int SPECULARTERM     = 12;
  static constexpr unsigned int SHADOWFULLFLOAT  = 13;

  SimpleMaterialDefines();
  ~SimpleMaterialDefines();

}; // end of struct SimpleMaterialDefines

} // end of namespace MaterialsLibrary
} // end of namespace BABYLON

#endif // end of BABYLON_MATERIALS_LIBRARY_SIMPLE_SIMPLE_MATERIAL_DEFINES_H
