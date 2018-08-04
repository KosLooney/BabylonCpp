#ifndef BABYLON_POSTPROCESS_BLOOM_MERGE_POST_PROCESS_H
#define BABYLON_POSTPROCESS_BLOOM_MERGE_POST_PROCESS_H

#include <babylon/babylon_global.h>
#include <babylon/postprocess/post_process.h>

namespace BABYLON {

/**
 * @brief The BloomMergePostProcess merges blurred images with the original
 * based on the values of the circle of confusion.
 */
class BABYLON_SHARED_EXPORT BloomMergePostProcess : public PostProcess {

public:
  /**
   * @brief Creates a new instance of @see BloomMergePostProcess.
   * @param name The name of the effect.
   * @param originalFromInput Post process which's input will be used for the
   * merge.
   * @param blurred Blurred highlights post process which's output will be used.
   * @param weight Weight of the bloom to be added to the original input.
   * @param options The required width/height ratio to downsize to before
   * computing the render pass.
   * @param camera The camera to apply the render pass to.
   * @param samplingMode The sampling mode to be used when computing the pass.
   * (default: 0)
   * @param engine The engine which the post process will be applied. (default:
   * current engine)
   * @param reusable If the post process can be reused on the same frame.
   * (default: false)
   * @param textureType Type of textures used when performing the post process.
   * (default: 0)
   * @param blockCompilation If compilation of the shader should not be done in
   * the constructor. The updateEffect method can be used to compile the shader
   * at a later time. (default: false)
   */
  BloomMergePostProcess(const string_t& name, PostProcess* originalFromInput,
                        PostProcess* blurred, float weight,
                        const Variant<float, PostProcessOptions>& options,
                        Camera* camera, unsigned int samplingMode,
                        Engine* engine, bool reusable = false,
                        unsigned int textureType
                        = EngineConstants::TEXTURETYPE_UNSIGNED_INT,
                        bool blockCompilation = false);
  virtual ~BloomMergePostProcess() override;

public:
  PostProcess* originalFromInput;
  PostProcess* blurred;

  /**
   * Weight of the bloom to be added to the original input
   */
  float weight;

}; // end of class BloomMergePostProcess

} // end of namespace BABYLON

#endif // end of BABYLON_POSTPROCESS_BLOOM_MERGE_POST_PROCESS_H
