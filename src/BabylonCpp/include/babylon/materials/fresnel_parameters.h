#ifndef BABYLON_MATERIALS_FRESNEL_PARAMETERS_H
#define BABYLON_MATERIALS_FRESNEL_PARAMETERS_H

#include <babylon/babylon_global.h>
#include <babylon/math/color3.h>

namespace BABYLON {

class BABYLON_SHARED_EXPORT FresnelParameters {

public:
  FresnelParameters();
  FresnelParameters(const FresnelParameters& other);
  FresnelParameters(FresnelParameters&& other);
  FresnelParameters& operator=(const FresnelParameters& other);
  FresnelParameters& operator=(FresnelParameters&& other);
  ~FresnelParameters();

  bool isEnabled() const;
  void setIsEnabled(bool value);

  unique_ptr_t<FresnelParameters> clone() const;
  Json::object serialize() const;

  static unique_ptr_t<FresnelParameters>
  Parse(const Json::value& parsedFresnelParameters);

public:
  Color3 leftColor;
  Color3 rightColor;
  float bias;
  float power;

private:
  bool _isEnabled;

}; // end of class FresnelParameters

} // end of namespace BABYLON

#endif // end of BABYLON_MATERIALS_FRESNEL_PARAMETERS_H
