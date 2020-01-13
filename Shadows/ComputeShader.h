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
//   float4x4 viewProj;                 // Offset:  128 Size:    64
//   float4x4 meshWorld;                // Offset:  192 Size:    64 [unused]
//   float4x4 characterWorld;           // Offset:  256 Size:    64 [unused]
//   float4 texData;                    // Offset:  320 Size:    16
//   uint4 texSize;                     // Offset:  336 Size:    16
//   uint4 headSize;                    // Offset:  352 Size:    16
//   uint4 vertexCount;                 // Offset:  368 Size:    16 [unused]
//   float3 lightDir;                   // Offset:  384 Size:    12 [unused]
//
// }
//
// Resource bind info for TailBuffer
// {
//
//   struct TailSample
//   {
//       
//       float3 ws_pos;                 // Offset:    0
//       int next;                      // Offset:   12
//
//   } $Element;                        // Offset:    0 Size:    16
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
// HEAD                                  UAV    sint          2d             u1      1 
// TAIL                                  UAV    sint          2d             u2      1 
// TailBuffer                            UAV  struct         r/w             u3      1 
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
dcl_constantbuffer CB1[23], immediateIndexed
dcl_resource_texture2dms(0) (float,float,float,float) t0
dcl_uav_typed_texture2d (float,float,float,float) u0
dcl_uav_typed_texture2d (sint,sint,sint,sint) u1
dcl_uav_typed_texture2d (sint,sint,sint,sint) u2
dcl_uav_structured u3, 16
dcl_input vThreadID.xy
dcl_temps 2
dcl_thread_group 16, 16, 1
uge r0.xy, vThreadID.xyxx, cb1[21].xyxx
or r0.x, r0.y, r0.x
if_nz r0.x
  ret 
endif 
store_uav_typed u0.xyzw, vThreadID.xyyy, l(0,0,0,1.000000)
mov r0.xy, vThreadID.xyxx
mov r0.zw, l(0,0,0,0)
ldms_indexable(texture2dms)(float,float,float,float) r0.x, r0.xyzw, t0.xyzw, l(0)
lt r0.y, l(0.999900), r0.x
if_nz r0.y
  ret 
endif 
utof r0.yz, vThreadID.xxyx
div r0.yz, r0.yyzy, cb1[20].xxyx
mad r0.y, r0.y, l(2.000000), l(-1.000000)
add r0.z, -r0.z, l(1.000000)
mad r0.z, r0.z, l(2.000000), l(-1.000000)
mul r1.xyzw, r0.zzzz, cb1[5].xyzw
mad r1.xyzw, cb1[4].xyzw, r0.yyyy, r1.xyzw
mad r0.xyzw, cb1[6].xyzw, r0.xxxx, r1.xyzw
add r0.xyzw, r0.xyzw, cb1[7].xyzw
div r0.xyzw, r0.xyzw, r0.wwww
mul r1.xyzw, r0.yyyy, cb1[1].xyzw
mad r1.xyzw, cb1[0].xyzw, r0.xxxx, r1.xyzw
mad r1.xyzw, cb1[2].xyzw, r0.zzzz, r1.xyzw
mad r0.xyzw, cb1[3].xyzw, r0.wwww, r1.xyzw
mov r1.yzw, r0.xxyz
mov r1.x, l(1.000000)
store_uav_typed u0.xyzw, vThreadID.xyyy, r1.yzwx
mul r0.xy, r1.zzzz, cb1[9].xyxx
mad r0.xy, cb1[8].xyxx, r1.yyyy, r0.xyxx
mad r0.xy, cb1[10].xyxx, r1.wwww, r0.xyxx
mad r0.xy, cb1[11].xyxx, r0.wwww, r0.xyxx
utof r0.zw, cb1[22].xxxy
mul r0.xy, r0.zwzz, r0.xyxx
round_ni r0.xy, r0.xyxx
ftoi r0.xy, r0.xyxx
imad r0.z, vThreadID.y, cb1[21].x, vThreadID.x
imm_atomic_exch r1.x, u1, r0.xyxx, r0.z
store_uav_typed u2.xyzw, vThreadID.xyyy, r1.xxxx
store_structured u3.xyzw, r0.z, l(0), r1.yzwx
ret 
// Approximately 43 instruction slots used
#endif

const BYTE ComputeShaderByteCode[] =
{
     68,  88,  66,  67,  81, 153, 
     31,  85,  22,  98, 248,  31, 
    109,  76,  81, 231, 127, 124, 
    232, 159,   1,   0,   0,   0, 
     28,  11,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
     60,   5,   0,   0,  76,   5, 
      0,   0,  92,   5,   0,   0, 
    128,  10,   0,   0,  82,  68, 
     69,  70,   0,   5,   0,   0, 
      2,   0,   0,   0,  44,   1, 
      0,   0,   6,   0,   0,   0, 
     60,   0,   0,   0,   0,   5, 
     83,  67,   0,   1,   0,   0, 
    216,   4,   0,   0,  82,  68, 
     49,  49,  60,   0,   0,   0, 
     24,   0,   0,   0,  32,   0, 
      0,   0,  40,   0,   0,   0, 
     36,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
    252,   0,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      6,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0,   2,   1,   0,   0, 
      4,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0,   9,   1, 
      0,   0,   4,   0,   0,   0, 
      3,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     14,   1,   0,   0,   4,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   2,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  19,   1,   0,   0, 
      6,   0,   0,   0,   6,   0, 
      0,   0,   1,   0,   0,   0, 
     16,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  30,   1, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     73, 110, 112, 117, 116,   0, 
     79, 117, 116, 112, 117, 116, 
      0,  72,  69,  65,  68,   0, 
     84,  65,  73,  76,   0,  84, 
     97, 105, 108,  66, 117, 102, 
    102, 101, 114,   0,  67,  83, 
     67, 111, 110, 115, 116,  97, 
    110, 116, 115,   0, 171, 171, 
     30,   1,   0,   0,  10,   0, 
      0,   0,  92,   1,   0,   0, 
    144,   1,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     19,   1,   0,   0,   1,   0, 
      0,   0,   4,   4,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
    236,   2,   0,   0,   0,   0, 
      0,   0,  64,   0,   0,   0, 
      2,   0,   0,   0,   0,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,  36,   3, 
      0,   0,  64,   0,   0,   0, 
     64,   0,   0,   0,   2,   0, 
      0,   0,   0,   3,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  44,   3,   0,   0, 
    128,   0,   0,   0,  64,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   3,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
     53,   3,   0,   0, 192,   0, 
      0,   0,  64,   0,   0,   0, 
      0,   0,   0,   0,   0,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,  63,   3, 
      0,   0,   0,   1,   0,   0, 
     64,   0,   0,   0,   0,   0, 
      0,   0,   0,   3,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  78,   3,   0,   0, 
     64,   1,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     96,   3,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    132,   3,   0,   0,  80,   1, 
      0,   0,  16,   0,   0,   0, 
      2,   0,   0,   0, 148,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 184,   3, 
      0,   0,  96,   1,   0,   0, 
     16,   0,   0,   0,   2,   0, 
      0,   0, 148,   3,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 193,   3,   0,   0, 
    112,   1,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    148,   3,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    205,   3,   0,   0, 128,   1, 
      0,   0,  12,   0,   0,   0, 
      0,   0,   0,   0, 224,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 118, 105, 
    101, 119,  73, 110, 118,   0, 
    102, 108, 111,  97, 116,  52, 
    120,  52,   0, 171, 171, 171, 
      3,   0,   3,   0,   4,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 244,   2,   0,   0, 
    112, 114, 111, 106,  73, 110, 
    118,   0, 118, 105, 101, 119, 
     80, 114, 111, 106,   0, 109, 
    101, 115, 104,  87, 111, 114, 
    108, 100,   0,  99, 104,  97, 
    114,  97,  99, 116, 101, 114, 
     87, 111, 114, 108, 100,   0, 
    116, 101, 120,  68,  97, 116, 
     97,   0, 102, 108, 111,  97, 
    116,  52,   0, 171, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  86,   3,   0,   0, 
    116, 101, 120,  83, 105, 122, 
    101,   0, 117, 105, 110, 116, 
     52,   0, 171, 171,   1,   0, 
     19,   0,   1,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    140,   3,   0,   0, 104, 101, 
     97, 100,  83, 105, 122, 101, 
      0, 118, 101, 114, 116, 101, 
    120,  67, 111, 117, 110, 116, 
      0, 108, 105, 103, 104, 116, 
     68, 105, 114,   0, 102, 108, 
    111,  97, 116,  51,   0, 171, 
    171, 171,   1,   0,   3,   0, 
      1,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 214,   3, 
      0,   0,  44,   4,   0,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    180,   4,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
     36,  69, 108, 101, 109, 101, 
    110, 116,   0,  84,  97, 105, 
    108,  83,  97, 109, 112, 108, 
    101,   0, 119, 115,  95, 112, 
    111, 115,   0, 171,   1,   0, 
      3,   0,   1,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    214,   3,   0,   0, 110, 101, 
    120, 116,   0, 105, 110, 116, 
      0, 171, 171, 171,   0,   0, 
      2,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    113,   4,   0,   0,  64,   4, 
      0,   0,  72,   4,   0,   0, 
      0,   0,   0,   0, 108,   4, 
      0,   0, 120,   4,   0,   0, 
     12,   0,   0,   0,   5,   0, 
      0,   0,   1,   0,   4,   0, 
      0,   0,   2,   0, 156,   4, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     53,   4,   0,   0,  77, 105, 
     99, 114, 111, 115, 111, 102, 
    116,  32,  40,  82,  41,  32, 
     72,  76,  83,  76,  32,  83, 
    104,  97, 100, 101, 114,  32, 
     67, 111, 109, 112, 105, 108, 
    101, 114,  32,  49,  48,  46, 
     49,   0,  73,  83,  71,  78, 
      8,   0,   0,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     79,  83,  71,  78,   8,   0, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  83,  72, 
     69,  88,  28,   5,   0,   0, 
     80,   0,   5,   0,  71,   1, 
      0,   0, 106,   8,   0,   1, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   1,   0,   0,   0, 
     23,   0,   0,   0,  88,  32, 
      0,   4,   0, 112,  16,   0, 
      0,   0,   0,   0,  85,  85, 
      0,   0, 156,  24,   0,   4, 
      0, 224,  17,   0,   0,   0, 
      0,   0,  85,  85,   0,   0, 
    156,  24,   0,   4,   0, 224, 
     17,   0,   1,   0,   0,   0, 
     51,  51,   0,   0, 156,  24, 
      0,   4,   0, 224,  17,   0, 
      2,   0,   0,   0,  51,  51, 
      0,   0, 158,   0,   0,   4, 
      0, 224,  17,   0,   3,   0, 
      0,   0,  16,   0,   0,   0, 
     95,   0,   0,   2,  50,   0, 
      2,   0, 104,   0,   0,   2, 
      2,   0,   0,   0, 155,   0, 
      0,   4,  16,   0,   0,   0, 
     16,   0,   0,   0,   1,   0, 
      0,   0,  80,   0,   0,   7, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,   0,   2,   0, 
     70, 128,  32,   0,   1,   0, 
      0,   0,  21,   0,   0,   0, 
     60,   0,   0,   7,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  31,   0, 
      4,   3,  10,   0,  16,   0, 
      0,   0,   0,   0,  62,   0, 
      0,   1,  21,   0,   0,   1, 
    164,   0,   0,   9, 242, 224, 
     17,   0,   0,   0,   0,   0, 
     70,   5,   2,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 128,  63, 
     54,   0,   0,   4,  50,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   0,   2,   0,  54,   0, 
      0,   8, 194,   0,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     46,   0,   0, 139,   2,   1, 
      0, 128,  67,  85,  21,   0, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 126, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  49,   0,   0,   7, 
     34,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
    114, 249, 127,  63,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     31,   0,   4,   3,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     62,   0,   0,   1,  21,   0, 
      0,   1,  86,   0,   0,   4, 
     98,   0,  16,   0,   0,   0, 
      0,   0,   6,   1,   2,   0, 
     14,   0,   0,   8,  98,   0, 
     16,   0,   0,   0,   0,   0, 
     86,   6,  16,   0,   0,   0, 
      0,   0,   6, 129,  32,   0, 
      1,   0,   0,   0,  20,   0, 
      0,   0,  50,   0,   0,   9, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,  64, 
      1,  64,   0,   0,   0,   0, 
    128, 191,   0,   0,   0,   8, 
     66,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16, 128, 
     65,   0,   0,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63,  50,   0, 
      0,   9,  66,   0,  16,   0, 
      0,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,  64,   1,  64,   0,   0, 
      0,   0, 128, 191,  56,   0, 
      0,   8, 242,   0,  16,   0, 
      1,   0,   0,   0, 166,  10, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   5,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   4,   0,   0,   0, 
     86,   5,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   1,   0,   0,   0, 
      6,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,   0,   0,   0,   8, 
    242,   0,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   1,   0,   0,   0, 
      7,   0,   0,   0,  14,   0, 
      0,   7, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   8, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  86,   5,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0,  70, 142, 
     32,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70, 142,  32,   0, 
      1,   0,   0,   0,   2,   0, 
      0,   0, 166,  10,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  54,   0, 
      0,   5, 226,   0,  16,   0, 
      1,   0,   0,   0,   6,   9, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   5,  18,   0, 
     16,   0,   1,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
    128,  63, 164,   0,   0,   6, 
    242, 224,  17,   0,   0,   0, 
      0,   0,  70,   5,   2,   0, 
    150,   3,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   8, 
     50,   0,  16,   0,   0,   0, 
      0,   0, 166,  10,  16,   0, 
      1,   0,   0,   0,  70, 128, 
     32,   0,   1,   0,   0,   0, 
      9,   0,   0,   0,  50,   0, 
      0,  10,  50,   0,  16,   0, 
      0,   0,   0,   0,  70, 128, 
     32,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  86,   5, 
     16,   0,   1,   0,   0,   0, 
     70,   0,  16,   0,   0,   0, 
      0,   0,  50,   0,   0,  10, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70, 128,  32,   0, 
      1,   0,   0,   0,  10,   0, 
      0,   0, 246,  15,  16,   0, 
      1,   0,   0,   0,  70,   0, 
     16,   0,   0,   0,   0,   0, 
     50,   0,   0,  10,  50,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 128,  32,   0,   1,   0, 
      0,   0,  11,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  70,   0,  16,   0, 
      0,   0,   0,   0,  86,   0, 
      0,   6, 194,   0,  16,   0, 
      0,   0,   0,   0,   6, 132, 
     32,   0,   1,   0,   0,   0, 
     22,   0,   0,   0,  56,   0, 
      0,   7,  50,   0,  16,   0, 
      0,   0,   0,   0, 230,  10, 
     16,   0,   0,   0,   0,   0, 
     70,   0,  16,   0,   0,   0, 
      0,   0,  65,   0,   0,   5, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,   0,  16,   0, 
      0,   0,   0,   0,  27,   0, 
      0,   5,  50,   0,  16,   0, 
      0,   0,   0,   0,  70,   0, 
     16,   0,   0,   0,   0,   0, 
     35,   0,   0,   8,  66,   0, 
     16,   0,   0,   0,   0,   0, 
     26,   0,   2,   0,  10, 128, 
     32,   0,   1,   0,   0,   0, 
     21,   0,   0,   0,  10,   0, 
      2,   0, 184,   0,   0,   9, 
     18,   0,  16,   0,   1,   0, 
      0,   0,   0, 224,  17,   0, 
      1,   0,   0,   0,  70,   0, 
     16,   0,   0,   0,   0,   0, 
     42,   0,  16,   0,   0,   0, 
      0,   0, 164,   0,   0,   6, 
    242, 224,  17,   0,   2,   0, 
      0,   0,  70,   5,   2,   0, 
      6,   0,  16,   0,   1,   0, 
      0,   0, 168,   0,   0,   9, 
    242, 224,  17,   0,   3,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
    150,   3,  16,   0,   1,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 148,   0, 
      0,   0,  43,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     20,   0,   0,   0,   1,   0, 
      0,   0,   2,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   4,   0,   0,   0
};
