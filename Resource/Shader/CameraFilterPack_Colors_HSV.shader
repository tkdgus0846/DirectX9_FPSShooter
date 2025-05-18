//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "CameraFilterPack/Colors_HSV" {
Properties {
_MainTex ("Base (RGB)", 2D) = "white" { }
_HueShift ("HueShift", Range(0, 360)) = 0
_Sat ("Saturation", Float) = 1
_Val ("Value", Float) = 1
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 54416
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