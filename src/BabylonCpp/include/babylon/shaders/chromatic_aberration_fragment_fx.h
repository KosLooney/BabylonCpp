﻿#ifndef BABYLON_SHADERS_CHROMATIC_ABERRATION_FRAGMENT_FX_H
#define BABYLON_SHADERS_CHROMATIC_ABERRATION_FRAGMENT_FX_H

namespace BABYLON {

extern const char* chromaticAberrationPixelShader;

const char* chromaticAberrationPixelShader
  = "// samplers\n"
    "uniform sampler2D textureSampler;  // original color\n"
    "\n"
    "// uniforms\n"
    "uniform float chromatic_aberration;\n"
    "uniform float radialIntensity;\n"
    "uniform vec2 direction;\n"
    "uniform vec2 centerPosition;\n"
    "uniform float screen_width;\n"
    "uniform float screen_height;\n"
    "\n"
    "// varyings\n"
    "varying vec2 vUV;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "  vec2 centered_screen_pos = vec2(vUV.x - centerPosition.x, vUV.y - centerPosition.y);\n"
    "  vec2 directionOfEffect = direction;\n"
    "  if(directionOfEffect.x == 0. && directionOfEffect.y == 0.){\n"
    "  directionOfEffect = normalize(centered_screen_pos);\n"
    "  }\n"
    "\n"
    "  float radius2 = centered_screen_pos.x*centered_screen_pos.x\n"
    "  + centered_screen_pos.y*centered_screen_pos.y;\n"
    "  float radius = sqrt(radius2);\n"
    "\n"
    "  vec4 original = texture2D(textureSampler, vUV);\n"
    "\n"
    "  //index of refraction of each color channel, causing chromatic dispersion\n"
    "  vec3 ref_indices = vec3(-0.3, 0.0, 0.3);\n"
    "  float ref_shiftX = chromatic_aberration * pow(radius, radialIntensity) * directionOfEffect.x / screen_width;\n"
    "  float ref_shiftY = chromatic_aberration * pow(radius, radialIntensity) * directionOfEffect.y / screen_height;\n"
    "\n"
    "  // shifts for red, green & blue\n"
    "  vec2 ref_coords_r = vec2(vUV.x + ref_indices.r*ref_shiftX, vUV.y + ref_indices.r*ref_shiftY*0.5);\n"
    "  vec2 ref_coords_g = vec2(vUV.x + ref_indices.g*ref_shiftX, vUV.y + ref_indices.g*ref_shiftY*0.5);\n"
    "  vec2 ref_coords_b = vec2(vUV.x + ref_indices.b*ref_shiftX, vUV.y + ref_indices.b*ref_shiftY*0.5);\n"
    "\n"
    "  original.r = texture2D(textureSampler, ref_coords_r).r;\n"
    "  original.g = texture2D(textureSampler, ref_coords_g).g;\n"
    "  original.b = texture2D(textureSampler, ref_coords_b).b;\n"
    "  original.a = clamp(texture2D(textureSampler, ref_coords_r).a + texture2D(textureSampler, ref_coords_g).a + texture2D(textureSampler, ref_coords_b).a, 0., 1.);\n"
    "  gl_FragColor = original;\n"
    "}\n";

} // end of namespace BABYLON

#endif // end of BABYLON_SHADERS_CHROMATIC_ABERRATION_FRAGMENT_FX_H
