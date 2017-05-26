#ifndef BABYLON_POSTPROCESS_BLUR_POST_PROCESS_H
#define BABYLON_POSTPROCESS_BLUR_POST_PROCESS_H

#include <babylon/babylon_global.h>
#include <babylon/materials/textures/texture_constants.h>
#include <babylon/math/vector2.h>
#include <babylon/postprocess/post_process.h>

namespace BABYLON {

/**
 * @brief
 */
class BABYLON_SHARED_EXPORT BlurPostProcess : public PostProcess {

public:
  BlurPostProcess(const std::string& name, const Vector2& direction,
                  float blurWidth, float ratio, Camera* camera,
                  unsigned int samplingMode
                  = TextureConstants::BILINEAR_SAMPLINGMODE,
                  Engine* engine = nullptr, bool reusable = false);
  ~BlurPostProcess();

public:
  Vector2 direction;
  float blurWidth;

}; // end of class BlurPostProcess

} // end of namespace BABYLON

#endif // end of BABYLON_POSTPROCESS_BLUR_POST_PROCESS_H
