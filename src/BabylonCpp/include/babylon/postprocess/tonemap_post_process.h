#ifndef BABYLON_POSTPROCESS_TONEMAP_POST_PROCESS_H
#define BABYLON_POSTPROCESS_TONEMAP_POST_PROCESS_H

#include <babylon/babylon_global.h>
#include <babylon/postprocess/post_process.h>

namespace BABYLON {

/**
 * @brief
 */
class BABYLON_SHARED_EXPORT TonemapPostProcess : public PostProcess {

public:
  TonemapPostProcess(const string_t& name, const TonemappingOperator& operator_,
                     float exposureAdjustment, Camera* camera,
                     unsigned int samplingMode
                     = TextureConstants::BILINEAR_SAMPLINGMODE,
                     Engine* engine = nullptr,
                     unsigned int textureFormat
                     = EngineConstants::TEXTURETYPE_UNSIGNED_INT);
  virtual ~TonemapPostProcess();

private:
  TonemappingOperator _operator;

}; // end of class TonemapPostProcess

} // end of namespace BABYLON

#endif // end of BABYLON_POSTPROCESS_TONEMAP_POST_PROCESS_H
