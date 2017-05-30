﻿#ifndef BABYLON_SHADERS_SHADOW_MAP_FRAGMENT_FX_H
#define BABYLON_SHADERS_SHADOW_MAP_FRAGMENT_FX_H

namespace BABYLON {

extern const char* shadowMapPixelShader;

const char* shadowMapPixelShader
  = "#ifndef FULLFLOAT\n"
    "vec4 pack(float depth)\n"
    "{\n"
    "  const vec4 bit_shift = vec4(255.0 * 255.0 * 255.0, 255.0 * 255.0, 255.0, 1.0);\n"
    "  const vec4 bit_mask = vec4(0.0, 1.0 / 255.0, 1.0 / 255.0, 1.0 / 255.0);\n"
    "\n"
    "  vec4 res = fract(depth * bit_shift);\n"
    "  res -= res.xxyz * bit_mask;\n"
    "\n"
    "  return res;\n"
    "}\n"
    "#endif\n"
    "\n"
    "varying vec4 vPosition;\n"
    "\n"
    "#ifdef ALPHATEST\n"
    "varying vec2 vUV;\n"
    "uniform sampler2D diffuseSampler;\n"
    "#endif\n"
    "\n"
    "#ifdef CUBEMAP\n"
    "uniform vec3 lightPosition;\n"
    "uniform vec2 depthValues;\n"
    "#endif\n"
    "\n"
    "uniform vec2 biasAndScale;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "#ifdef ALPHATEST\n"
    "  if (texture2D(diffuseSampler, vUV).a < 0.4)\n"
    "  discard;\n"
    "#endif\n"
    "\n"
    "#ifdef CUBEMAP\n"
    "  vec3 directionToLight = vPosition.xyz - lightPosition;\n"
    "  \n"
    "  float depth = length(directionToLight);\n"
    "  depth = (depth - depthValues.x) / (depthValues.y - depthValues.x);\n"
    "  depth = clamp(depth, 0., 1.0);\n"
    "#else\n"
    "  float depth = vPosition.z / vPosition.w;\n"
    "  depth = depth * 0.5 + 0.5;  \n"
    "#endif\n"
    "\n"
    "  depth += biasAndScale.x;\n"
    "\n"
    "#ifdef ESM\n"
    "  depth = exp(-min(87., biasAndScale.y * depth));\n"
    "#endif\n"
    "\n"
    "#ifndef FULLFLOAT\n"
    "  gl_FragColor = pack(depth);\n"
    "#else\n"
    "  gl_FragColor = vec4(depth, 1.0, 1.0, 1.0);\n"
    "#endif\n"
    "}\n";

} // end of namespace BABYLON

#endif // end of BABYLON_SHADERS_SHADOW_MAP_FRAGMENT_FX_H
