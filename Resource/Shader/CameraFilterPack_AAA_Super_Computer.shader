//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "CameraFilterPack/AAA_Super_Computer" {
Properties {
_MainTex ("Base (RGB)", 2D) = "white" { }
_TimeX ("Time", Range(0, 1)) = 1
_Distortion ("_Distortion", Range(0, 1)) = 0.3
_ScreenResolution ("_ScreenResolution", Vector) = (0,0,0,0)
_Value ("_Value", Range(0.2, 10)) = 8.1
_BorderSize ("_BorderSize", Range(-0.5, 0.5)) = 0
_BorderColor ("_BorderColor", Color) = (0,0.5,1,1)
_SpotSize ("_SpotSize", Range(0, 1)) = 0.5
_AlphaHexa ("_AlphaHexa", Range(0.2, 10)) = 0.608
_PositionX ("_PositionX", Range(-0.5, 0.5)) = 0
_PositionY ("_PositionY", Range(-0.5, 0.5)) = 0
_Radius ("_Radius", Range(0, 1)) = 0.5
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 6429
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