//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/NTSCEffect" {
Properties {
_MainTex ("Texture", 2D) = "white" { }
_OverlayImg ("Overlay Image", 2D) = "white" { }
_PixelMask ("Pixel Mask", 2D) = "white" { }
_RGB2YIQ ("RGB to YIQ LUT", 3D) = "" { }
_YIQ2RGB ("YIQ to RGB LUT", 3D) = "" { }
}
SubShader {
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 37436
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 67874
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 146176
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "RF_SIGNAL" "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 261665
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_TV_CURVATURE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" "USE_TV_CURVATURE" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_TV_CURVATURE" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" "USE_TV_CURVATURE" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 279917
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 351099
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 449585
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "QUANTIZE_RGB" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  ZTest Always
  ZWrite Off
  Cull Off
  GpuProgramID 501038
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "USE_YIQ_MATRIX" "ANTI_FLICKER" "ROLLING_FLICKER" "PIXEL_MASK" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}