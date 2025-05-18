//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "AlpacaSound/RetroPixelPro" {
Properties {
_MainTex ("Texture", 2D) = "" { }
_Colormap ("Colormap", 3D) = "" { }
_Palette ("Palette", 2D) = "" { }
_BlueNoise ("BlueNoise", 2D) = "" { }
_Opacity ("Opacity", Range(0, 1)) = 1
_Dither ("Dither", Range(0, 1)) = 1
}
SubShader {
 Pass {
  ZWrite Off
  Cull Off
  GpuProgramID 15699
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