//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "DistortionShaderPack/Legacy/RTDistortionMaster" {
Properties {
_MainColor ("MainColor", Color) = (0,0,0,1)
_RenderTexture ("RenderTexture", 2D) = "black" { }
_NormalTexture ("Normal", 2D) = "blue" { }
_DistortionStrength ("DistortionStrength", Range(-2, 2)) = 0.1
_DistortionCircle ("DistortionCircle", Range(0, 1)) = 0
_NormalTexStrength ("_NormalTexStrength", Range(0, 1)) = 0.5
_NormalTexFrameless ("_NormalTexFrameless", Range(0, 1)) = 0.5
_StrengthAlpha ("AlphaStrength", Range(0, 1)) = 0.5
_UVOffset ("UVOffset XY, generated ZW", Vector) = (0,0,0,0)
}
SubShader {
 Tags { "QUEUE" = "Transparent+1" "RenderType" = "Transparent" }
 Pass {
  Tags { "QUEUE" = "Transparent+1" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
  ZWrite Off
  GpuProgramID 8021
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
}
}
}