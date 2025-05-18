//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Unlit/DitherShader" {
Properties {
_Color ("Color", Color) = (1,1,1,1)
_MainTex ("Texture", 2D) = "white" { }
_ResolutionX ("Resolution X", Float) = 320
_ResolutionY ("Resolution Y", Float) = 240
}
SubShader {
 LOD 100
 Tags { "QUEUE" = "AlphaTest" "RenderType" = "TransparentCutout" }
 Pass {
  LOD 100
  Tags { "QUEUE" = "AlphaTest" "RenderType" = "TransparentCutout" }
  GpuProgramID 44745
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