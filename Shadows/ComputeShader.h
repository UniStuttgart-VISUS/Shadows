#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer CSConstants
// {
//
//   float4x4 viewInv;                  // Offset:    0 Size:    64
//   float4x4 projInv;                  // Offset:   64 Size:    64
//   float width;                       // Offset:  128 Size:     4
//   float height;                      // Offset:  132 Size:     4
//   float4x4 viewProj;                 // Offset:  144 Size:    64
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// Input                             texture  float4        2dMS             t0      1 
// Output                                UAV  float4          2d             u0      1 
// HEAD                                  UAV   sint2          2d             u1      1 
// TAIL                                  UAV   sint2          2d             u2      1 
// CSConstants                       cbuffer      NA          NA            cb1      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// no Input
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// no Output
cs_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB1[13], immediateIndexed
dcl_resource_texture2dms(0) (float,float,float,float) t0
dcl_uav_typed_texture2d (float,float,float,float) u0
dcl_uav_typed_texture2d (sint,sint,sint,sint) u1
dcl_uav_typed_texture2d (sint,sint,sint,sint) u2
dcl_input vThreadID.xy
dcl_temps 2
dcl_thread_group 16, 16, 1
utof r0.xy, vThreadID.xyxx
div r0.xy, r0.xyxx, cb1[8].xyxx
add r0.y, -r0.y, l(1.000000)
mad r0.x, r0.x, l(2.000000), l(-1.000000)
mad r0.y, r0.y, l(2.000000), l(-1.000000)
mul r1.xyzw, r0.yyyy, cb1[5].xyzw
mad r0.xyzw, cb1[4].xyzw, r0.xxxx, r1.xyzw
mov r1.xy, vThreadID.xyxx
mov r1.zw, l(0,0,0,0)
ldms_indexable(texture2dms)(float,float,float,float) r1.x, r1.xyzw, t0.xyzw, l(0)
mad r0.xyzw, cb1[6].xyzw, r1.xxxx, r0.xyzw
add r0.xyzw, r0.xyzw, cb1[7].xyzw
mul r1.xyzw, r0.yyyy, cb1[1].xyzw
mad r1.xyzw, cb1[0].xyzw, r0.xxxx, r1.xyzw
mad r1.xyzw, cb1[2].xyzw, r0.zzzz, r1.xyzw
mad r0.xyzw, cb1[3].xyzw, r0.wwww, r1.xyzw
mul r1.xyzw, r0.yyyy, cb1[10].xyzw
mad r1.xyzw, cb1[9].xyzw, r0.xxxx, r1.xyzw
mad r1.xyzw, cb1[11].xyzw, r0.zzzz, r1.xyzw
mad r0.xyzw, cb1[12].xyzw, r0.wwww, r1.xyzw
div r0.xyz, r0.xyzx, r0.wwww
mov r0.w, l(1.000000)
store_uav_typed u0.xyzw, vThreadID.xyyy, r0.xyzw
store_uav_typed u1.xyzw, vThreadID.xyyy, l(0,1,0,0)
store_uav_typed u2.xyzw, vThreadID.xyyy, l(1,0,1,1)
ret 
// Approximately 26 instruction slots used
#endif

const BYTE ComputeShaderByteCode[] =
{
     68,  88,  66,  67, 126, 118, 
    106, 182, 205, 198, 190,  51, 
    127, 220, 255, 198, 199, 188, 
    126, 245,   1,   0,   0,   0, 
     76,   7,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    196,   2,   0,   0, 212,   2, 
      0,   0, 228,   2,   0,   0, 
    176,   6,   0,   0,  82,  68, 
     69,  70, 136,   2,   0,   0, 
      1,   0,   0,   0,   0,   1, 
      0,   0,   5,   0,   0,   0, 
     60,   0,   0,   0,   0,   5, 
     83,  67,   0,   1,   0,   0, 
     96,   2,   0,   0,  82,  68, 
     49,  49,  60,   0,   0,   0, 
     24,   0,   0,   0,  32,   0, 
      0,   0,  40,   0,   0,   0, 
     36,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
    220,   0,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      6,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0, 226,   0,   0,   0, 
      4,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0, 233,   0, 
      0,   0,   4,   0,   0,   0, 
      3,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   5,   0,   0,   0, 
    238,   0,   0,   0,   4,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   2,   0,   0,   0, 
      1,   0,   0,   0,   5,   0, 
      0,   0, 243,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  73, 110, 
    112, 117, 116,   0,  79, 117, 
    116, 112, 117, 116,   0,  72, 
     69,  65,  68,   0,  84,  65, 
     73,  76,   0,  67,  83,  67, 
    111, 110, 115, 116,  97, 110, 
    116, 115,   0, 171, 243,   0, 
      0,   0,   5,   0,   0,   0, 
     24,   1,   0,   0, 208,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 224,   1, 
      0,   0,   0,   0,   0,   0, 
     64,   0,   0,   0,   2,   0, 
      0,   0, 244,   1,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  24,   2,   0,   0, 
     64,   0,   0,   0,  64,   0, 
      0,   0,   2,   0,   0,   0, 
    244,   1,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
     32,   2,   0,   0, 128,   0, 
      0,   0,   4,   0,   0,   0, 
      2,   0,   0,   0,  44,   2, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,  80,   2, 
      0,   0, 132,   0,   0,   0, 
      4,   0,   0,   0,   2,   0, 
      0,   0,  44,   2,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  87,   2,   0,   0, 
    144,   0,   0,   0,  64,   0, 
      0,   0,   2,   0,   0,   0, 
    244,   1,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    118, 105, 101, 119,  73, 110, 
    118,   0, 102, 108, 111,  97, 
    116,  52, 120,  52,   0, 171, 
    171, 171,   3,   0,   3,   0, 
      4,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 232,   1, 
      0,   0, 112, 114, 111, 106, 
     73, 110, 118,   0, 119, 105, 
    100, 116, 104,   0, 102, 108, 
    111,  97, 116,   0,   0,   0, 
      3,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     38,   2,   0,   0, 104, 101, 
    105, 103, 104, 116,   0, 118, 
    105, 101, 119,  80, 114, 111, 
    106,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  49,  48,  46,  49,   0, 
     73,  83,  71,  78,   8,   0, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  79,  83, 
     71,  78,   8,   0,   0,   0, 
      0,   0,   0,   0,   8,   0, 
      0,   0,  83,  72,  69,  88, 
    196,   3,   0,   0,  80,   0, 
      5,   0, 241,   0,   0,   0, 
    106,   8,   0,   1,  89,   0, 
      0,   4,  70, 142,  32,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0,  88,  32,   0,   4, 
      0, 112,  16,   0,   0,   0, 
      0,   0,  85,  85,   0,   0, 
    156,  24,   0,   4,   0, 224, 
     17,   0,   0,   0,   0,   0, 
     85,  85,   0,   0, 156,  24, 
      0,   4,   0, 224,  17,   0, 
      1,   0,   0,   0,  51,  51, 
      0,   0, 156,  24,   0,   4, 
      0, 224,  17,   0,   2,   0, 
      0,   0,  51,  51,   0,   0, 
     95,   0,   0,   2,  50,   0, 
      2,   0, 104,   0,   0,   2, 
      2,   0,   0,   0, 155,   0, 
      0,   4,  16,   0,   0,   0, 
     16,   0,   0,   0,   1,   0, 
      0,   0,  86,   0,   0,   4, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,   0,   2,   0, 
     14,   0,   0,   8,  50,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   0,  16,   0,   0,   0, 
      0,   0,  70, 128,  32,   0, 
      1,   0,   0,   0,   8,   0, 
      0,   0,   0,   0,   0,   8, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16, 128, 
     65,   0,   0,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63,  50,   0, 
      0,   9,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,  64,   1,  64,   0,   0, 
      0,   0, 128, 191,  50,   0, 
      0,   9,  34,   0,  16,   0, 
      0,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,  64,   1,  64,   0,   0, 
      0,   0, 128, 191,  56,   0, 
      0,   8, 242,   0,  16,   0, 
      1,   0,   0,   0,  86,   5, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   5,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   4,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  54,   0, 
      0,   4,  50,   0,  16,   0, 
      1,   0,   0,   0,  70,   0, 
      2,   0,  54,   0,   0,   8, 
    194,   0,  16,   0,   1,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  46,   0, 
      0, 139,   2,   1,   0, 128, 
     67,  85,  21,   0,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  70, 126,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   6,   0,   0,   0, 
      6,   0,  16,   0,   1,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   8, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   7,   0,   0,   0, 
     56,   0,   0,   8, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     86,   5,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70, 142,  32,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   6,   0,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   2,   0,   0,   0, 
    166,  10,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   1,   0,   0,   0, 
      3,   0,   0,   0, 246,  15, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   8, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  86,   5,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   1,   0,   0,   0, 
     10,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0,  70, 142, 
     32,   0,   1,   0,   0,   0, 
      9,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70, 142,  32,   0, 
      1,   0,   0,   0,  11,   0, 
      0,   0, 166,  10,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,  12,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  14,   0, 
      0,   7, 114,   0,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   5, 
    130,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63, 164,   0, 
      0,   6, 242, 224,  17,   0, 
      0,   0,   0,   0,  70,   5, 
      2,   0,  70,  14,  16,   0, 
      0,   0,   0,   0, 164,   0, 
      0,   9, 242, 224,  17,   0, 
      1,   0,   0,   0,  70,   5, 
      2,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 164,   0, 
      0,   9, 242, 224,  17,   0, 
      2,   0,   0,   0,  70,   5, 
      2,   0,   2,  64,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  62,   0, 
      0,   1,  83,  84,  65,  84, 
    148,   0,   0,   0,  26,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  17,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0
};