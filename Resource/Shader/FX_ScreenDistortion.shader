//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "FX/ScreenDistortion" {
Properties {
_MainTex ("Tint Color (RGB)", 2D) = "white" { }
_MainColor ("MainColor", Color) = (0,0,0,1)
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
 GrabPass {
}
 Pass {
  Name "BASE"
  Tags { "LIGHTMODE" = "ALWAYS" "QUEUE" = "Transparent+1" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
  ZWrite Off
  GpuProgramID 33505
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FOG_LINEAR" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "FOG_LINEAR" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}