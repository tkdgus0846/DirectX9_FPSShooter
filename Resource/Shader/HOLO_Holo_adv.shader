//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "HOLO/Holo_adv" {
Properties {
_originalDiffuse ("Original Diffuse Map", 2D) = "white" { }
_Diffuse ("Diffuse Map", 2D) = "white" { }
_diff_Color ("Diffuse Color Mult", Color) = (1,1,1,1)
_N_map ("Noise", 2D) = "white" { }
_M_map ("Mask", 2D) = "white" { }
[Toggle] _mask_type ("Use Map as Mask", Float) = 1
_intensity ("Intensity", Range(0, 10)) = 0
_deform ("Deformation intensity", Float) = 1
_Color ("Outline Color Mult", Color) = (1,1,1,1)
_Opacity ("Base Opacity", Range(0, 1)) = 0
_Bias ("Bias", Range(0, 1)) = 0
_Scale ("Scale ", Range(0, 10)) = 0
_Power ("Power", Range(0, 3)) = 0
_Speed ("Speed", Range(0, 1)) = 0
_t ("Extra Option", Range(0, 1)) = 0
[Toggle] _X ("Active X Axe", Float) = 1
[Toggle] _Y ("Active Y Axe", Float) = 1
[Toggle] _glitchColor ("Glitch/Diffuse Color", Float) = 1
_glitchColor_c ("G/H Color", Color) = (1,1,1,1)
[Toggle] _dist_chrom ("Chromatic ", Float) = 1
_noise_details ("G/H Noise Details Amount", Range(1, 16)) = 0
_cut_level ("Cut Level", Range(0, 6)) = 0
_OrigineX ("OrigineX", Range(0, 1)) = 0
_OrigineY ("OrigineY", Range(0, 1)) = 0
_Circle_wave ("Wave Circles", Range(0, 100)) = 5
_Speed_wave ("Wave Speed", Float) = 0
_Zoom ("Zoom", Range(0.5, 200)) = 1
_Speed_face ("_Speed_face", Range(0.01, 10)) = 1
_Rotation ("Rotation", Range(0, 1)) = 0
[Toggle] _monochrom ("Monochromatic", Float) = 1
[Toggle] _OriginalUVSwitch ("Switch to Orginal UVs on/off", Float) = 0
}
SubShader {
 Tags { "IGNOREPROJECTOR" = "true" "QUEUE" = "Transparent" "RenderType" = "Transparent" }
 Pass {
  Tags { "IGNOREPROJECTOR" = "true" "QUEUE" = "Transparent" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
  GpuProgramID 53149
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
CustomEditor "Glitch_Editor"
}