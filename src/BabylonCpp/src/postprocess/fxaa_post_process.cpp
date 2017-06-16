#include <babylon/postprocess/fxaa_post_process.h>

#include <babylon/materials/effect.h>

namespace BABYLON {

FxaaPostProcess::FxaaPostProcess(const std::string& iName, float ratio,
                                 Camera* camera, unsigned int samplingMode,
                                 Engine* engine, bool reusable,
                                 unsigned int textureType)
    : PostProcess{iName,        "fxaa", {"texelSize"}, {}, ratio,      camera,
                  samplingMode, engine, reusable,      "", textureType}
{

  onSizeChangedObservable.add([this]() {
    texelWidth  = 1.f / static_cast<float>(width);
    texelHeight = 1.f / static_cast<float>(height);
  });

  onApplyObservable.add([this](Effect* effect) {
    effect->setFloat2("texelSize", texelWidth, texelHeight);
  });
}

FxaaPostProcess::~FxaaPostProcess()
{
}

} // end of namespace BABYLON
