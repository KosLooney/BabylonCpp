#ifndef BABYLON_MATERIALS_PBR_PBR_BASE_MATERIAL_H
#define BABYLON_MATERIALS_PBR_PBR_BASE_MATERIAL_H

#include <babylon/babylon_global.h>
#include <babylon/materials/push_material.h>

namespace BABYLON {

/**
 * The Physically based material base class of BJS.
 *
 * This offers the main features of a standard PBR material.
 * For more information, please refer to the documentation :
 * http://doc.babylonjs.com/extensions/Physically_Based_Rendering
 */
class BABYLON_SHARED_EXPORT PBRBaseMaterial : public PushMaterial {

public:
  /**
   * @brief Instantiates a new PBRMaterial instance.
   *
   * @param name The material name
   * @param scene The scene the material will be use in.
   */
  PBRBaseMaterial(const std::string& name, Scene* scene);
  ~PBRBaseMaterial();

  virtual const char* getClassName() const = 0;

  bool useLogarithmicDepth() const;
  void setUseLogarithmicDepth(bool value);
  bool needAlphaBlending() const;
  bool needAlphaTesting() const;
  BaseTexture* getAlphaTestTexture() const;
  bool isReadyForSubMesh(AbstractMesh* mesh, SubMesh* subMesh,
                         bool useInstances = false) const;
  void buildUniformLayout();
  void unbind();
  void bindOnlyWorldMatrix(const Matrix& world);
  void bindForSubMesh(const Matrix& world, Mesh* mesh, SubMesh* subMesh);
  std::vector<IAnimatable*> getAnimatables() const;
  void dispose(bool forceDisposeEffect = false, bool forceDisposeTextures);

protected:
  /**
   * @brief Attaches a new image processing configuration to the PBR Material.
   * @param configuration
   */
  void _attachImageProcessingConfiguration(
    const ImageProcessingConfiguration& configuration);

  bool _shouldUseAlphaFromAlbedoTexture() const;

private:
  BaseTexture* _getReflectionTexture() const;
  BaseTexture* _getRefractionTexture() const;

protected:
  /**
   * Intensity of the direct lights e.g. the four lights available in your
   * scene.
   * This impacts both the direct diffuse and specular highlights.
   */
  float _directIntensity;

  /**
   * Intensity of the emissive part of the material.
   * This helps controlling the emissive effect without modifying the emissive
   * color.
   */
  float _emissiveIntensity;

  /**
   * Intensity of the environment e.g. how much the environment will light the
   * object either through harmonics for rough material or through the
   * refelction for shiny ones.
   */
  float _environmentIntensity;

  /**
   * This is a special control allowing the reduction of the specular highlights
   * coming from the four lights of the scene. Those highlights may not be
   * needed in full environment lighting.
   */
  float _specularIntensity;

  /**
   * Debug Control allowing disabling the bump map on this material.
   */
  float _disableBumpMap;

  /**
   * AKA Diffuse Texture in standard nomenclature.
   */
  BaseTexture* _albedoTexture;

  /**
   * AKA Occlusion Texture in other nomenclature.
   */
  BaseTexture* _ambientTexture;

  /**
   * AKA Occlusion Texture Intensity in other nomenclature.
   */
  float _ambientTextureStrength;

  BaseTexture* _opacityTexture;

  BaseTexture* _reflectionTexture;

  BaseTexture* _refractionTexture;

  BaseTexture* _emissiveTexture;

  /**
   * AKA Specular texture in other nomenclature.
   */
  BaseTexture* _reflectivityTexture;

  /**
   * Used to switch from specular/glossiness to metallic/roughness workflow.
   */
  BaseTexture* _metallicTexture;

  /**
   * Specifies the metallic scalar of the metallic/roughness workflow.
   * Can also be used to scale the metalness values of the metallic texture.
   */
  float _metallic;

  /**
   * Specifies the roughness scalar of the metallic/roughness workflow.
   * Can also be used to scale the roughness values of the metallic texture.
   */
  float _roughness;

  /**
   * Used to enable roughness/glossiness fetch from a separate chanel depending
   * on the current mode.
   * Gray Scale represents roughness in metallic mode and glossiness in specular
   * mode.
   */
  BaseTexture* _microSurfaceTexture;

  BaseTexture* _bumpTexture;

  BaseTexture* _lightmapTexture;

  Color3 _ambientColor;

  /**
   * AKA Diffuse Color in other nomenclature.
   */
  Color3 _albedoColor;

  /**
   * AKA Specular Color in other nomenclature.
   */
  Color3 _reflectivityColor;

  Color3 _reflectionColor;

  Color3 _emissiveColor;

  /**
   * AKA Glossiness in other nomenclature.
   */
  float _microSurface;

  /**
   * source material index of refraction (IOR)' / 'destination material IOR.
   */
  float _indexOfRefraction;

  /**
   * Controls if refraction needs to be inverted on Y. This could be usefull for
   * procedural texture.
   */
  bool _invertRefractionY;

  /**
   * This parameters will make the material used its opacity to control how much
   * it is refracting aginst not.
   * Materials half opaque for instance using refraction could benefit from this
   * control.
   */
  bool _linkRefractionWithTransparency;

  bool _useLightmapAsShadowmap;

  /**
   * Specifies that the alpha is coming form the albedo channel alpha channel.
   */
  bool _useAlphaFromAlbedoTexture;

  /**
   * Specifies that the material will keeps the specular highlights over a
   * transparent surface (only the most limunous ones).
   * A car glass is a good exemple of that. When sun reflects on it you can not
   * see what is behind.
   */
  bool _useSpecularOverAlpha;

  /**
   * Specifies if the reflectivity texture contains the glossiness information
   * in its alpha channel.
   */
  bool _useMicroSurfaceFromReflectivityMapAlpha;

  /**
   * Specifies if the metallic texture contains the roughness information in its
   * alpha channel.
   */
  bool _useRoughnessFromMetallicTextureAlpha;

  /**
   * Specifies if the metallic texture contains the roughness information in its
   * green channel.
   */
  bool _useRoughnessFromMetallicTextureGreen;

  /**
   * Specifies if the metallic texture contains the metallness information in
   * its blue channel.
   */
  bool _useMetallnessFromMetallicTextureBlue;

  /**
   * Specifies if the metallic texture contains the ambient occlusion
   * information in its red channel.
   */
  bool _useAmbientOcclusionFromMetallicTextureRed;

  /**
   * Specifies if the ambient texture contains the ambient occlusion information
   * in its red channel only.
   */
  bool _useAmbientInGrayScale;

  /**
   * In case the reflectivity map does not contain the microsurface information
   * in its alpha channel,
   * The material will try to infer what glossiness each pixel should be.
   */
  bool _useAutoMicroSurfaceFromReflectivityMap;

  /**
   * BJS is using an harcoded light falloff based on a manually sets up range.
   * In PBR, one way to represents the fallof is to use the inverse squared root
   * algorythm.
   * This parameter can help you switch back to the BJS mode in order to create
   * scenes using both materials.
   */
  bool _usePhysicalLightFalloff;

  /**
   * Specifies that the material will keeps the reflection highlights over a
   * transparent surface (only the most limunous ones).
   * A car glass is a good exemple of that. When the street lights reflects on
   * it you can not see what is behind.
   */
  bool _useRadianceOverAlpha;

  /**
   * Allows using the bump map in parallax mode.
   */
  bool _useParallax;

  /**
   * Allows using the bump map in parallax occlusion mode.
   */
  bool _useParallaxOcclusion;

  /**
   * Controls the scale bias of the parallax mode.
   */
  float _parallaxScaleBias;

  /**
   * If sets to true, disables all the lights affecting the material.
   */
  bool _disableLighting;

  /**
   * Number of Simultaneous lights allowed on the material.
   */
  unsigned int _maxSimultaneousLights;

  /**
   * If sets to true, x component of normal map value will invert (x = 1.0 - x).
   */
  bool _invertNormalMapX;

  /**
   * If sets to true, y component of normal map value will invert (y = 1.0 - y).
   */
  bool _invertNormalMapY;

  /**
   * If sets to true and backfaceCulling is false, normals will be flipped on
   * the backside.
   */
  bool _twoSidedLighting;

  /**
   * Defines the alpha limits in alpha test mode.
   */
  float _alphaCutOff;

  /**
   * Enforces alpha test in opaque or blend mode in order to improve the
   * performances of some situations.
   */
  bool _forceAlphaTest;

  /**
   * Specifies that the alpha is premultiplied before output (this enables alpha
   * premultiplied blending).
   * in your scene composition.
   */
  bool _premultiplyAlpha;

  /**
   * A fresnel is applied to the alpha of the model to ensure grazing angles
   * edges are not alpha tested.
   * And/Or occlude the blended part.
   */
  bool _useAlphaFresnel;

  /**
   * Specifies the environment BRDF texture used to comput the scale and offset
   * roughness values
   * from cos thetav and roughness:
   * http://blog.selfshadow.com/publications/s2013-shading-course/karis/s2013_pbs_epic_notes_v2.pdf
   */
  BaseTexture* _environmentBRDFTexture;

  /**
   * Default configuration related to image processing available in the PBR
   * Material.
   */
  ImageProcessingConfiguration _imageProcessingConfiguration;

private:
  static Color3 _scaledReflectivity;
  Vector4 _lightingInfos;
  /**
   * Keep track of the image processing observer to allow dispose and replace.
   */
  Observer<ImageProcessingConfiguration> _imageProcessingObserver;
  std::vector<RenderTargetTexture*> _renderTargets;
  Matrix _worldViewProjectionMatrix;
  Color3 _globalAmbientColor;
  Color3 _tempColor;
  int _renderId;
  bool _useLogarithmicDepth;

}; // end of class PBRBaseMaterial

} // end of namespace BABYLON

#endif // end of BABYLON_MATERIALS_PBR_PBR_BASE_MATERIAL_H