//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Retro/RetroDiffuse" {
Properties {
_Color ("Color", Color) = (1,1,1,1)
_AmbientColor ("Ambient", Color) = (1,1,1,1)
_MainTex ("Texture", 2D) = "white" { }
_ResolutionX ("Resolution X", Float) = 320
_ResolutionY ("Resolution Y", Float) = 240
}
SubShader {
 LOD 100
 Tags { "RenderType" = "Opaque" }
 Pass {
  LOD 100
  Tags { "RenderType" = "Opaque" }
  GpuProgramID 56824
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