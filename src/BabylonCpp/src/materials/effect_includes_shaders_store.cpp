﻿#include <babylon/materials/effect_includes_shaders_store.h>

#include <babylon/shaders/shadersinclude/background_fragment_declaration_fx.h>
#include <babylon/shaders/shadersinclude/background_ubo_declaration_fx.h>
#include <babylon/shaders/shadersinclude/background_vertex_declaration_fx.h>
#include <babylon/shaders/shadersinclude/bayer_dither_functions_fx.h>
#include <babylon/shaders/shadersinclude/bones_declaration_fx.h>
#include <babylon/shaders/shadersinclude/bones_vertex_fx.h>
#include <babylon/shaders/shadersinclude/bump_fragment_fx.h>
#include <babylon/shaders/shadersinclude/bump_fragment_functions_fx.h>
#include <babylon/shaders/shadersinclude/bump_fragment_main_functions_fx.h>
#include <babylon/shaders/shadersinclude/bump_vertex_fx.h>
#include <babylon/shaders/shadersinclude/bump_vertex_declaration_fx.h>
#include <babylon/shaders/shadersinclude/clip_plane_fragment_fx.h>
#include <babylon/shaders/shadersinclude/clip_plane_fragment_declaration_fx.h>
#include <babylon/shaders/shadersinclude/clip_plane_fragment_declaration2_fx.h>
#include <babylon/shaders/shadersinclude/clip_plane_vertex_fx.h>
#include <babylon/shaders/shadersinclude/clip_plane_vertex_declaration_fx.h>
#include <babylon/shaders/shadersinclude/clip_plane_vertex_declaration2_fx.h>
#include <babylon/shaders/shadersinclude/default_fragment_declaration_fx.h>
#include <babylon/shaders/shadersinclude/default_ubo_declaration_fx.h>
#include <babylon/shaders/shadersinclude/default_vertex_declaration_fx.h>
#include <babylon/shaders/shadersinclude/depth_pre_pass_fx.h>
#include <babylon/shaders/shadersinclude/fog_fragment_fx.h>
#include <babylon/shaders/shadersinclude/fog_fragment_declaration_fx.h>
#include <babylon/shaders/shadersinclude/fog_vertex_fx.h>
#include <babylon/shaders/shadersinclude/fog_vertex_declaration_fx.h>
#include <babylon/shaders/shadersinclude/fresnel_function_fx.h>
#include <babylon/shaders/shadersinclude/harmonics_functions_fx.h>
#include <babylon/shaders/shadersinclude/hdr_filtering_functions_fx.h>
#include <babylon/shaders/shadersinclude/helper_functions_fx.h>
#include <babylon/shaders/shadersinclude/image_processing_declaration_fx.h>
#include <babylon/shaders/shadersinclude/image_processing_functions_fx.h>
#include <babylon/shaders/shadersinclude/importance_sampling_fx.h>
#include <babylon/shaders/shadersinclude/instances_declaration_fx.h>
#include <babylon/shaders/shadersinclude/instances_vertex_fx.h>
#include <babylon/shaders/shadersinclude/kernel_blur_fragment_fx.h>
#include <babylon/shaders/shadersinclude/kernel_blur_fragment2_fx.h>
#include <babylon/shaders/shadersinclude/kernel_blur_varying_declaration_fx.h>
#include <babylon/shaders/shadersinclude/kernel_blur_vertex_fx.h>
#include <babylon/shaders/shadersinclude/light_fragment_fx.h>
#include <babylon/shaders/shadersinclude/light_fragment_declaration_fx.h>
#include <babylon/shaders/shadersinclude/light_ubo_declaration_fx.h>
#include <babylon/shaders/shadersinclude/lights_fragment_functions_fx.h>
#include <babylon/shaders/shadersinclude/log_depth_declaration_fx.h>
#include <babylon/shaders/shadersinclude/log_depth_fragment_fx.h>
#include <babylon/shaders/shadersinclude/log_depth_vertex_fx.h>
#include <babylon/shaders/shadersinclude/morph_targets_vertex_fx.h>
#include <babylon/shaders/shadersinclude/morph_targets_vertex_declaration_fx.h>
#include <babylon/shaders/shadersinclude/morph_targets_vertex_global_declaration_fx.h>
#include <babylon/shaders/shadersinclude/mrt_fragment_declaration_fx.h>
#include <babylon/shaders/shadersinclude/packing_functions_fx.h>
#include <babylon/shaders/shadersinclude/pbr_brdf_functions_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_albedo_opacity_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_alpha_fresnel_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_ambient_occlusion_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_anisotropic_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_clearcoat_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_direct_lighting_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_final_color_composition_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_final_lit_components_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_final_unlit_components_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_geometry_info_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_image_processing_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_normal_final_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_normal_geometric_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_reflectance_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_reflectance0_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_reflection_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_reflectivity_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_sheen_fx.h>
#include <babylon/shaders/shadersinclude/pbr_block_sub_surface_fx.h>
#include <babylon/shaders/shadersinclude/pbr_debug_fx.h>
#include <babylon/shaders/shadersinclude/pbr_direct_lighting_falloff_functions_fx.h>
#include <babylon/shaders/shadersinclude/pbr_direct_lighting_functions_fx.h>
#include <babylon/shaders/shadersinclude/pbr_direct_lighting_setup_functions_fx.h>
#include <babylon/shaders/shadersinclude/pbr_fragment_declaration_fx.h>
#include <babylon/shaders/shadersinclude/pbr_fragment_extra_declaration_fx.h>
#include <babylon/shaders/shadersinclude/pbr_fragment_samplers_declaration_fx.h>
#include <babylon/shaders/shadersinclude/pbr_helper_functions_fx.h>
#include <babylon/shaders/shadersinclude/pbr_ibl_functions_fx.h>
#include <babylon/shaders/shadersinclude/pbr_ubo_declaration_fx.h>
#include <babylon/shaders/shadersinclude/pbr_vertex_declaration_fx.h>
#include <babylon/shaders/shadersinclude/point_cloud_vertex_fx.h>
#include <babylon/shaders/shadersinclude/point_cloud_vertex_declaration_fx.h>
#include <babylon/shaders/shadersinclude/reflection_function_fx.h>
#include <babylon/shaders/shadersinclude/shadow_map_fragment_fx.h>
#include <babylon/shaders/shadersinclude/shadow_map_fragment_declaration_fx.h>
#include <babylon/shaders/shadersinclude/shadow_map_fragment_soft_transparent_shadow_fx.h>
#include <babylon/shaders/shadersinclude/shadow_map_vertex_declaration_fx.h>
#include <babylon/shaders/shadersinclude/shadow_map_vertex_metric_fx.h>
#include <babylon/shaders/shadersinclude/shadow_map_vertex_normal_bias_fx.h>
#include <babylon/shaders/shadersinclude/shadows_fragment_functions_fx.h>
#include <babylon/shaders/shadersinclude/shadows_vertex_fx.h>

namespace BABYLON {

EffectIncludesShadersStore::EffectIncludesShadersStore() = default;

EffectIncludesShadersStore::~EffectIncludesShadersStore() = default;

std::unordered_map<std::string, std::string>&
EffectIncludesShadersStore::shaders()
{
  return _shaders;
}

const std::unordered_map<std::string, std::string>&
EffectIncludesShadersStore::shaders() const
{
  return _shaders;
}

std::unordered_map<std::string, std::string>
  EffectIncludesShadersStore::_shaders
  = {{"backgroundFragmentDeclaration", backgroundFragmentDeclaration},
     {"backgroundUboDeclaration", backgroundUboDeclaration},
     {"backgroundVertexDeclaration", backgroundVertexDeclaration},
     {"bayerDitherFunctions", bayerDitherFunctions},
     {"bonesDeclaration", bonesDeclaration},
     {"bonesVertex", bonesVertex},
     {"bumpFragment", bumpFragment},
     {"bumpFragmentFunctions", bumpFragmentFunctions},
     {"bumpFragmentMainFunctions", bumpFragmentMainFunctions},
     {"bumpVertex", bumpVertex},
     {"bumpVertexDeclaration", bumpVertexDeclaration},
     {"clipPlaneFragment", clipPlaneFragment},
     {"clipPlaneFragmentDeclaration", clipPlaneFragmentDeclaration},
     {"clipPlaneFragmentDeclaration2", clipPlaneFragmentDeclaration2},
     {"clipPlaneVertex", clipPlaneVertex},
     {"clipPlaneVertexDeclaration", clipPlaneVertexDeclaration},
     {"clipPlaneVertexDeclaration2", clipPlaneVertexDeclaration2},
     {"defaultFragmentDeclaration", defaultFragmentDeclaration},
     {"defaultUboDeclaration", defaultUboDeclaration},
     {"defaultVertexDeclaration", defaultVertexDeclaration},
     {"depthPrePass", depthPrePass},
     {"fogFragment", fogFragment},
     {"fogFragmentDeclaration", fogFragmentDeclaration},
     {"fogVertex", fogVertex},
     {"fogVertexDeclaration", fogVertexDeclaration},
     {"fresnelFunction", fresnelFunction},
     {"harmonicsFunctions", harmonicsFunctions},
     {"hdrFilteringFunctions", hdrFilteringFunctions},
     {"helperFunctions", helperFunctions},
     {"imageProcessingDeclaration", imageProcessingDeclaration},
     {"imageProcessingFunctions", imageProcessingFunctions},
     {"importanceSampling", importanceSampling},
     {"instancesDeclaration", instancesDeclaration},
     {"instancesVertex", instancesVertex},
     {"kernelBlurFragment", kernelBlurFragment},
     {"kernelBlurFragment2", kernelBlurFragment2},
     {"kernelBlurVaryingDeclaration", kernelBlurVaryingDeclaration},
     {"kernelBlurVertex", kernelBlurVertex},
     {"lightFragment", lightFragment},
     {"lightFragmentDeclaration", lightFragmentDeclaration},
     {"lightUboDeclaration", lightUboDeclaration},
     {"lightsFragmentFunctions", lightsFragmentFunctions},
     {"logDepthDeclaration", logDepthDeclaration},
     {"logDepthFragment", logDepthFragment},
     {"logDepthVertex", logDepthVertex},
     {"morphTargetsVertex", morphTargetsVertex},
     {"morphTargetsVertexDeclaration", morphTargetsVertexDeclaration},
     {"morphTargetsVertexGlobalDeclaration", morphTargetsVertexGlobalDeclaration},
     {"mrtFragmentDeclaration", mrtFragmentDeclaration},
     {"packingFunctions", packingFunctions},
     {"pbrBRDFFunctions", pbrBRDFFunctions},
     {"pbrBlockAlbedoOpacity", pbrBlockAlbedoOpacity},
     {"pbrBlockAlphaFresnel", pbrBlockAlphaFresnel},
     {"pbrBlockAmbientOcclusion", pbrBlockAmbientOcclusion},
     {"pbrBlockAnisotropic", pbrBlockAnisotropic},
     {"pbrBlockClearcoat", pbrBlockClearcoat},
     {"pbrBlockDirectLighting", pbrBlockDirectLighting},
     {"pbrBlockFinalColorComposition", pbrBlockFinalColorComposition},
     {"pbrBlockFinalLitComponents", pbrBlockFinalLitComponents},
     {"pbrBlockFinalUnlitComponents", pbrBlockFinalUnlitComponents},
     {"pbrBlockGeometryInfo", pbrBlockGeometryInfo},
     {"pbrBlockImageProcessing", pbrBlockImageProcessing},
     {"pbrBlockNormalFinal", pbrBlockNormalFinal},
     {"pbrBlockNormalGeometric", pbrBlockNormalGeometric},
     {"pbrBlockReflectance", pbrBlockReflectance},
     {"pbrBlockReflectance0", pbrBlockReflectance0},
     {"pbrBlockReflection", pbrBlockReflection},
     {"pbrBlockReflectivity", pbrBlockReflectivity},
     {"pbrBlockSheen", pbrBlockSheen},
     {"pbrBlockSubSurface", pbrBlockSubSurface},
     {"pbrDebug", pbrDebug},
     {"pbrDirectLightingFalloffFunctions", pbrDirectLightingFalloffFunctions},
     {"pbrDirectLightingFunctions", pbrDirectLightingFunctions},
     {"pbrDirectLightingSetupFunctions", pbrDirectLightingSetupFunctions},
     {"pbrFragmentDeclaration", pbrFragmentDeclaration},
     {"pbrFragmentExtraDeclaration", pbrFragmentExtraDeclaration},
     {"pbrFragmentSamplersDeclaration", pbrFragmentSamplersDeclaration},
     {"pbrHelperFunctions", pbrHelperFunctions},
     {"pbrIBLFunctions", pbrIBLFunctions},
     {"pbrUboDeclaration", pbrUboDeclaration},
     {"pbrVertexDeclaration", pbrVertexDeclaration},
     {"pointCloudVertex", pointCloudVertex},
     {"pointCloudVertexDeclaration", pointCloudVertexDeclaration},
     {"reflectionFunction", reflectionFunction},
     {"shadowMapFragment", shadowMapFragment},
     {"shadowMapFragmentDeclaration", shadowMapFragmentDeclaration},
     {"shadowMapFragmentSoftTransparentShadow", shadowMapFragmentSoftTransparentShadow},
     {"shadowMapVertexDeclaration", shadowMapVertexDeclaration},
     {"shadowMapVertexMetric", shadowMapVertexMetric},
     {"shadowMapVertexNormalBias", shadowMapVertexNormalBias},
     {"shadowsFragmentFunctions", shadowsFragmentFunctions},
     {"shadowsVertex", shadowsVertex}};

} // end of namespace BABYLON
