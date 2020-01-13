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
//   float4x4 viewInv;                  // Offset:    0 Size:    64 [unused]
//   float4x4 projInv;                  // Offset:   64 Size:    64 [unused]
//   float4x4 viewProj;                 // Offset:  128 Size:    64 [unused]
//   float4x4 meshWorld;                // Offset:  192 Size:    64
//   float4x4 characterWorld;           // Offset:  256 Size:    64 [unused]
//   float4 texData;                    // Offset:  320 Size:    16 [unused]
//   uint4 texSize;                     // Offset:  336 Size:    16
//   uint4 headSize;                    // Offset:  352 Size:    16 [unused]
//   uint4 vertexCount;                 // Offset:  368 Size:    16
//   float3 lightDir;                   // Offset:  384 Size:    12
//
// }
//
// Resource bind info for Indices
// {
//
//   uint $Element;                     // Offset:    0 Size:     4
//
// }
//
// Resource bind info for TailBuffer
// {
//
//   struct TailSample
//   {
//       
//       int next;                      // Offset:    0
//       float3 ws_pos;                 // Offset:    4
//
//   } $Element;                        // Offset:    0 Size:    16
//
// }
//
// Resource bind info for IntersectValues
// {
//
//   struct IntersectSample
//   {
//       
//       float4 edge1A;                 // Offset:    0
//       float4 edge2F;                 // Offset:   16
//       float4 h;                      // Offset:   32
//
//   } $Element;                        // Offset:    0 Size:    48
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// Indices                           texture  struct         r/o             t0      1 
// Vertices                          texture  float3         buf             t1      1 
// HEAD                              texture    sint          2d             t2      1 
// BBoxData                          texture    uint         buf             t3      1 
// InputHist                         texture    uint         buf             t4      1 
// TailBuffer                        texture  struct         r/o             t5      1 
// IntersectValues                   texture  struct         r/o             t6      1 
// VISMASK                               UAV    sint          2d             u0      1 
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
dcl_constantbuffer CB1[25], immediateIndexed
dcl_resource_structured t0, 4
dcl_resource_buffer (float,float,float,float) t1
dcl_resource_texture2d (sint,sint,sint,sint) t2
dcl_resource_buffer (uint,uint,uint,uint) t3
dcl_resource_buffer (uint,uint,uint,uint) t4
dcl_resource_structured t5, 16
dcl_resource_structured t6, 48
dcl_uav_typed_texture2d (sint,sint,sint,sint) u0
dcl_input vThreadID.xy
dcl_temps 7
dcl_thread_group 4, 64, 1
ld_indexable(buffer)(uint,uint,uint,uint) r0.x, cb1[23].yyyy, t4.xyzw
uge r0.x, vThreadID.x, r0.x
if_nz r0.x
  ret 
endif 
imul null, r0.x, cb1[23].y, cb1[23].x
imul null, r0.y, vThreadID.x, l(5)
imad r0.x, l(5), r0.x, r0.y
iadd r0.y, r0.x, l(4)
ld_indexable(buffer)(uint,uint,uint,uint) r0.y, r0.yyyy, t3.yxzw
ld_structured_indexable(structured_buffer, stride=48)(mixed,mixed,mixed,mixed) r1.xyzw, r0.y, l(0), t6.xyzw
lt r0.z, l(-0.000000), r1.w
lt r0.w, r1.w, l(0.000000)
and r0.z, r0.w, r0.z
if_nz r0.z
  ret 
endif 
ld_indexable(buffer)(uint,uint,uint,uint) r0.z, r0.xxxx, t3.yzxw
iadd r2.xyz, r0.xxxx, l(1, 2, 3, 0)
ld_indexable(buffer)(uint,uint,uint,uint) r0.x, r2.xxxx, t3.xyzw
ld_indexable(buffer)(uint,uint,uint,uint) r2.x, r2.yyyy, t3.xyzw
ld_indexable(buffer)(uint,uint,uint,uint) r2.y, r2.zzzz, t3.yxzw
iadd r0.w, -r0.z, r2.x
iadd r0.w, r0.w, l(1)
udiv r3.x, r4.x, vThreadID.y, r0.w
iadd r4.x, r0.z, r4.x
iadd r4.y, r0.x, r3.x
ult r0.xz, r2.xxyx, r4.xxyx
or r0.x, r0.z, r0.x
if_nz r0.x
  ret 
endif 
imul null, r0.x, r0.y, l(3)
ld_structured_indexable(structured_buffer, stride=4)(mixed,mixed,mixed,mixed) r0.x, r0.x, l(0), t0.xxxx
ld_indexable(buffer)(float,float,float,float) r2.xyz, r0.xxxx, t1.xyzw
mov r2.w, l(1.000000)
dp4 r3.y, r2.xyzw, cb1[12].xyzw
dp4 r3.z, r2.xyzw, cb1[13].xyzw
dp4 r3.x, r2.xyzw, cb1[14].xyzw
ld_structured_indexable(structured_buffer, stride=48)(mixed,mixed,mixed,mixed) r2.xyzw, r0.y, l(16), t6.xyzw
ld_structured_indexable(structured_buffer, stride=48)(mixed,mixed,mixed,mixed) r0.xyz, r0.y, l(32), t6.xyzx
mov r4.zw, l(0,0,0,0)
ld_indexable(texture2d)(sint,sint,sint,sint) r0.w, r4.xyzw, t2.yzwx
mov r1.w, r0.w
loop 
  ieq r3.w, r1.w, l(-1)
  breakc_nz r3.w
  ld_structured_indexable(structured_buffer, stride=16)(mixed,mixed,mixed,mixed) r4.xyzw, r1.w, l(0), t5.xyzw
  mad r4.yzw, cb1[24].zzxy, l(0.000000, 0.025000, 0.025000, 0.025000), r4.wwyz
  add r4.yzw, -r3.xxyz, r4.yyzw
  dp3 r3.w, r4.zwyz, r0.xyzx
  mul r5.x, r2.w, r3.w
  lt r5.y, r5.x, l(0.000000)
  lt r5.x, l(1.000000), r5.x
  or r5.x, r5.x, r5.y
  mul r5.yzw, r1.yyzx, r4.yyzw
  mad r4.yzw, r4.wwyz, r1.zzxy, -r5.yyzw
  dp3 r5.y, cb1[24].xyzx, r4.yzwy
  mul r5.y, r2.w, r5.y
  lt r5.z, r5.y, l(0.000000)
  mad r3.w, r2.w, r3.w, r5.y
  lt r3.w, l(1.000000), r3.w
  or r3.w, r3.w, r5.z
  dp3 r4.y, r2.xyzx, r4.yzwy
  mul r4.y, r2.w, r4.y
  lt r4.z, l(0.000000), r4.y
  lt r4.y, r4.y, l(10000000.000000)
  and r4.y, r4.y, r4.z
  or r3.w, r5.x, r3.w
  movc r3.w, r3.w, l(0), r4.y
  if_nz r3.w
    udiv r5.x, r6.x, r1.w, cb1[21].x
    utof r3.w, r5.x
    ftoi r6.yzw, r3.wwww
    store_uav_typed u0.xyzw, r6.xyzw, l(0,0,0,0)
  endif 
  mov r1.w, r4.x
endloop 
ret 
// Approximately 79 instruction slots used
#endif

const BYTE IZBRenderingBigByteCode[] =
{
     68,  88,  66,  67, 132, 226, 
    180, 148, 160,  24,  81, 128, 
    216,   5,  73,   6, 250,  51, 
    255, 139,   1,   0,   0,   0, 
    216,  16,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    252,   6,   0,   0,  12,   7, 
      0,   0,  28,   7,   0,   0, 
     60,  16,   0,   0,  82,  68, 
     69,  70, 192,   6,   0,   0, 
      4,   0,   0,   0, 180,   1, 
      0,   0,   9,   0,   0,   0, 
     60,   0,   0,   0,   0,   5, 
     83,  67,   0,   1,   0,   0, 
    152,   6,   0,   0,  82,  68, 
     49,  49,  60,   0,   0,   0, 
     24,   0,   0,   0,  32,   0, 
      0,   0,  40,   0,   0,   0, 
     36,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
     92,   1,   0,   0,   5,   0, 
      0,   0,   6,   0,   0,   0, 
      1,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 100,   1,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   1,   0,   0,   0, 
    255, 255, 255, 255,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      9,   0,   0,   0, 109,   1, 
      0,   0,   2,   0,   0,   0, 
      3,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      2,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    114,   1,   0,   0,   2,   0, 
      0,   0,   4,   0,   0,   0, 
      1,   0,   0,   0, 255, 255, 
    255, 255,   3,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 123,   1,   0,   0, 
      2,   0,   0,   0,   4,   0, 
      0,   0,   1,   0,   0,   0, 
    255, 255, 255, 255,   4,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0, 133,   1, 
      0,   0,   5,   0,   0,   0, 
      6,   0,   0,   0,   1,   0, 
      0,   0,  16,   0,   0,   0, 
      5,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    144,   1,   0,   0,   5,   0, 
      0,   0,   6,   0,   0,   0, 
      1,   0,   0,   0,  48,   0, 
      0,   0,   6,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 160,   1,   0,   0, 
      4,   0,   0,   0,   3,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0, 168,   1, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     73, 110, 100, 105,  99, 101, 
    115,   0,  86, 101, 114, 116, 
    105,  99, 101, 115,   0,  72, 
     69,  65,  68,   0,  66,  66, 
    111, 120,  68,  97, 116,  97, 
      0,  73, 110, 112, 117, 116, 
     72, 105, 115, 116,   0,  84, 
     97, 105, 108,  66, 117, 102, 
    102, 101, 114,   0,  73, 110, 
    116, 101, 114, 115, 101,  99, 
    116,  86,  97, 108, 117, 101, 
    115,   0,  86,  73,  83,  77, 
     65,  83,  75,   0,  67,  83, 
     67, 111, 110, 115, 116,  97, 
    110, 116, 115,   0, 168,   1, 
      0,   0,  10,   0,   0,   0, 
     20,   2,   0,   0, 144,   1, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  92,   1, 
      0,   0,   1,   0,   0,   0, 
    188,   4,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0, 133,   1, 
      0,   0,   1,   0,   0,   0, 
     24,   5,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0, 144,   1, 
      0,   0,   1,   0,   0,   0, 
    224,   5,   0,   0,  48,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0, 164,   3, 
      0,   0,   0,   0,   0,   0, 
     64,   0,   0,   0,   0,   0, 
      0,   0, 184,   3,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 220,   3,   0,   0, 
     64,   0,   0,   0,  64,   0, 
      0,   0,   0,   0,   0,   0, 
    184,   3,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    228,   3,   0,   0, 128,   0, 
      0,   0,  64,   0,   0,   0, 
      0,   0,   0,   0, 184,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 237,   3, 
      0,   0, 192,   0,   0,   0, 
     64,   0,   0,   0,   2,   0, 
      0,   0, 184,   3,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 247,   3,   0,   0, 
      0,   1,   0,   0,  64,   0, 
      0,   0,   0,   0,   0,   0, 
    184,   3,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      6,   4,   0,   0,  64,   1, 
      0,   0,  16,   0,   0,   0, 
      0,   0,   0,   0,  24,   4, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,  60,   4, 
      0,   0,  80,   1,   0,   0, 
     16,   0,   0,   0,   2,   0, 
      0,   0,  76,   4,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 112,   4,   0,   0, 
     96,   1,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
     76,   4,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    121,   4,   0,   0, 112,   1, 
      0,   0,  16,   0,   0,   0, 
      2,   0,   0,   0,  76,   4, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 133,   4, 
      0,   0, 128,   1,   0,   0, 
     12,   0,   0,   0,   2,   0, 
      0,   0, 152,   4,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 118, 105, 101, 119, 
     73, 110, 118,   0, 102, 108, 
    111,  97, 116,  52, 120,  52, 
      0, 171, 171, 171,   3,   0, 
      3,   0,   4,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    172,   3,   0,   0, 112, 114, 
    111, 106,  73, 110, 118,   0, 
    118, 105, 101, 119,  80, 114, 
    111, 106,   0, 109, 101, 115, 
    104,  87, 111, 114, 108, 100, 
      0,  99, 104,  97, 114,  97, 
     99, 116, 101, 114,  87, 111, 
    114, 108, 100,   0, 116, 101, 
    120,  68,  97, 116,  97,   0, 
    102, 108, 111,  97, 116,  52, 
      0, 171, 171, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     14,   4,   0,   0, 116, 101, 
    120,  83, 105, 122, 101,   0, 
    117, 105, 110, 116,  52,   0, 
    171, 171,   1,   0,  19,   0, 
      1,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  68,   4, 
      0,   0, 104, 101,  97, 100, 
     83, 105, 122, 101,   0, 118, 
    101, 114, 116, 101, 120,  67, 
    111, 117, 110, 116,   0, 108, 
    105, 103, 104, 116,  68, 105, 
    114,   0, 102, 108, 111,  97, 
    116,  51,   0, 171, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 142,   4,   0,   0, 
    228,   4,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      2,   0,   0,   0, 244,   4, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,  36,  69, 
    108, 101, 109, 101, 110, 116, 
      0, 100, 119, 111, 114, 100, 
      0, 171,   0,   0,  19,   0, 
      1,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 237,   4, 
      0,   0, 228,   4,   0,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    188,   5,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
     84,  97, 105, 108,  83,  97, 
    109, 112, 108, 101,   0, 110, 
    101, 120, 116,   0, 105, 110, 
    116,   0,   0,   0,   2,   0, 
      1,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  80,   5, 
      0,   0, 119, 115,  95, 112, 
    111, 115,   0, 171,   1,   0, 
      3,   0,   1,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    142,   4,   0,   0,  75,   5, 
      0,   0,  84,   5,   0,   0, 
      0,   0,   0,   0, 120,   5, 
      0,   0, 128,   5,   0,   0, 
      4,   0,   0,   0,   5,   0, 
      0,   0,   1,   0,   4,   0, 
      0,   0,   2,   0, 164,   5, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     64,   5,   0,   0, 228,   4, 
      0,   0,   0,   0,   0,   0, 
     48,   0,   0,   0,   2,   0, 
      0,   0, 116,   6,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  73, 110, 116, 101, 
    114, 115, 101,  99, 116,  83, 
     97, 109, 112, 108, 101,   0, 
    101, 100, 103, 101,  49,  65, 
      0, 171,   1,   0,   3,   0, 
      1,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  14,   4, 
      0,   0, 101, 100, 103, 101, 
     50,  70,   0, 104,   0, 171, 
    171, 171,  24,   6,   0,   0, 
     32,   6,   0,   0,   0,   0, 
      0,   0,  68,   6,   0,   0, 
     32,   6,   0,   0,  16,   0, 
      0,   0,  75,   6,   0,   0, 
     32,   6,   0,   0,  32,   0, 
      0,   0,   5,   0,   0,   0, 
      1,   0,  12,   0,   0,   0, 
      3,   0,  80,   6,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   8,   6, 
      0,   0,  77, 105,  99, 114, 
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
     24,   9,   0,   0,  80,   0, 
      5,   0,  70,   2,   0,   0, 
    106,   8,   0,   1,  89,   0, 
      0,   4,  70, 142,  32,   0, 
      1,   0,   0,   0,  25,   0, 
      0,   0, 162,   0,   0,   4, 
      0, 112,  16,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
     88,   8,   0,   4,   0, 112, 
     16,   0,   1,   0,   0,   0, 
     85,  85,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      2,   0,   0,   0,  51,  51, 
      0,   0,  88,   8,   0,   4, 
      0, 112,  16,   0,   3,   0, 
      0,   0,  68,  68,   0,   0, 
     88,   8,   0,   4,   0, 112, 
     16,   0,   4,   0,   0,   0, 
     68,  68,   0,   0, 162,   0, 
      0,   4,   0, 112,  16,   0, 
      5,   0,   0,   0,  16,   0, 
      0,   0, 162,   0,   0,   4, 
      0, 112,  16,   0,   6,   0, 
      0,   0,  48,   0,   0,   0, 
    156,  24,   0,   4,   0, 224, 
     17,   0,   0,   0,   0,   0, 
     51,  51,   0,   0,  95,   0, 
      0,   2,  50,   0,   2,   0, 
    104,   0,   0,   2,   7,   0, 
      0,   0, 155,   0,   0,   4, 
      4,   0,   0,   0,  64,   0, 
      0,   0,   1,   0,   0,   0, 
     45,   0,   0, 138,  66,   0, 
      0, 128,   3,  17,  17,   0, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  86, 133,  32,   0, 
      1,   0,   0,   0,  23,   0, 
      0,   0,  70, 126,  16,   0, 
      4,   0,   0,   0,  80,   0, 
      0,   6,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
      2,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  31,   0, 
      4,   3,  10,   0,  16,   0, 
      0,   0,   0,   0,  62,   0, 
      0,   1,  21,   0,   0,   1, 
     38,   0,   0,  10,   0, 208, 
      0,   0,  18,   0,  16,   0, 
      0,   0,   0,   0,  26, 128, 
     32,   0,   1,   0,   0,   0, 
     23,   0,   0,   0,  10, 128, 
     32,   0,   1,   0,   0,   0, 
     23,   0,   0,   0,  38,   0, 
      0,   7,   0, 208,   0,   0, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,   2,   0, 
      1,  64,   0,   0,   5,   0, 
      0,   0,  35,   0,   0,   9, 
     18,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      5,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  30,   0,   0,   7, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   4,   0,   0,   0, 
     45,   0,   0, 137,  66,   0, 
      0, 128,   3,  17,  17,   0, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  86,   5,  16,   0, 
      0,   0,   0,   0,  22, 126, 
     16,   0,   3,   0,   0,   0, 
    167,   0,   0, 139,   2, 131, 
      1, 128, 131, 153,  25,   0, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     70, 126,  16,   0,   6,   0, 
      0,   0,  49,   0,   0,   7, 
     66,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
    149, 191, 214, 179,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     49,   0,   0,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
    149, 191, 214,  51,   1,   0, 
      0,   7,  66,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     42,   0,  16,   0,   0,   0, 
      0,   0,  31,   0,   4,   3, 
     42,   0,  16,   0,   0,   0, 
      0,   0,  62,   0,   0,   1, 
     21,   0,   0,   1,  45,   0, 
      0, 137,  66,   0,   0, 128, 
      3,  17,  17,   0,  66,   0, 
     16,   0,   0,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0, 150, 124,  16,   0, 
      3,   0,   0,   0,  30,   0, 
      0,  10, 114,   0,  16,   0, 
      2,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
      2,  64,   0,   0,   1,   0, 
      0,   0,   2,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  45,   0,   0, 137, 
     66,   0,   0, 128,   3,  17, 
     17,   0,  18,   0,  16,   0, 
      0,   0,   0,   0,   6,   0, 
     16,   0,   2,   0,   0,   0, 
     70, 126,  16,   0,   3,   0, 
      0,   0,  45,   0,   0, 137, 
     66,   0,   0, 128,   3,  17, 
     17,   0,  18,   0,  16,   0, 
      2,   0,   0,   0,  86,   5, 
     16,   0,   2,   0,   0,   0, 
     70, 126,  16,   0,   3,   0, 
      0,   0,  45,   0,   0, 137, 
     66,   0,   0, 128,   3,  17, 
     17,   0,  34,   0,  16,   0, 
      2,   0,   0,   0, 166,  10, 
     16,   0,   2,   0,   0,   0, 
     22, 126,  16,   0,   3,   0, 
      0,   0,  30,   0,   0,   8, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16, 128, 
     65,   0,   0,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      2,   0,   0,   0,  30,   0, 
      0,   7, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   1,   0, 
      0,   0,  78,   0,   0,   8, 
     18,   0,  16,   0,   3,   0, 
      0,   0,  18,   0,  16,   0, 
      4,   0,   0,   0,  26,   0, 
      2,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  30,   0, 
      0,   7,  18,   0,  16,   0, 
      4,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   4,   0, 
      0,   0,  30,   0,   0,   7, 
     34,   0,  16,   0,   4,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   3,   0,   0,   0, 
     79,   0,   0,   7,  82,   0, 
     16,   0,   0,   0,   0,   0, 
      6,   1,  16,   0,   2,   0, 
      0,   0,   6,   1,  16,   0, 
      4,   0,   0,   0,  60,   0, 
      0,   7,  18,   0,  16,   0, 
      0,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  31,   0,   4,   3, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  62,   0,   0,   1, 
     21,   0,   0,   1,  38,   0, 
      0,   8,   0, 208,   0,   0, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   3,   0,   0,   0, 
    167,   0,   0, 139,   2,  35, 
      0, 128, 131, 153,  25,   0, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
      6, 112,  16,   0,   0,   0, 
      0,   0,  45,   0,   0, 137, 
     66,   0,   0, 128,  67,  85, 
     21,   0, 114,   0,  16,   0, 
      2,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 126,  16,   0,   1,   0, 
      0,   0,  54,   0,   0,   5, 
    130,   0,  16,   0,   2,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63,  17,   0, 
      0,   8,  34,   0,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,  12,   0,   0,   0, 
     17,   0,   0,   8,  66,   0, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  70, 142,  32,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0,  17,   0,   0,   8, 
     18,   0,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  70, 142, 
     32,   0,   1,   0,   0,   0, 
     14,   0,   0,   0, 167,   0, 
      0, 139,   2, 131,   1, 128, 
    131, 153,  25,   0, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
     16,   0,   0,   0,  70, 126, 
     16,   0,   6,   0,   0,   0, 
    167,   0,   0, 139,   2, 131, 
      1, 128, 131, 153,  25,   0, 
    114,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,  32,   0,   0,   0, 
     70, 114,  16,   0,   6,   0, 
      0,   0,  54,   0,   0,   8, 
    194,   0,  16,   0,   4,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  45,   0, 
      0, 137, 194,   0,   0, 128, 
    195, 204,  12,   0, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   4,   0, 
      0,   0, 150, 115,  16,   0, 
      2,   0,   0,   0,  54,   0, 
      0,   5, 130,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     48,   0,   0,   1,  32,   0, 
      0,   7, 130,   0,  16,   0, 
      3,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
      1,  64,   0,   0, 255, 255, 
    255, 255,   3,   0,   4,   3, 
     58,   0,  16,   0,   3,   0, 
      0,   0, 167,   0,   0, 139, 
      2, 131,   0, 128, 131, 153, 
     25,   0, 242,   0,  16,   0, 
      4,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  70, 126,  16,   0, 
      5,   0,   0,   0,  50,   0, 
      0,  13, 226,   0,  16,   0, 
      4,   0,   0,   0, 166, 132, 
     32,   0,   1,   0,   0,   0, 
     24,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
    205, 204, 204,  60, 205, 204, 
    204,  60, 205, 204, 204,  60, 
    246,   9,  16,   0,   4,   0, 
      0,   0,   0,   0,   0,   8, 
    226,   0,  16,   0,   4,   0, 
      0,   0,   6,   9,  16, 128, 
     65,   0,   0,   0,   3,   0, 
      0,   0,  86,  14,  16,   0, 
      4,   0,   0,   0,  16,   0, 
      0,   7, 130,   0,  16,   0, 
      3,   0,   0,   0, 230,   9, 
     16,   0,   4,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   7, 
     18,   0,  16,   0,   5,   0, 
      0,   0,  58,   0,  16,   0, 
      2,   0,   0,   0,  58,   0, 
     16,   0,   3,   0,   0,   0, 
     49,   0,   0,   7,  34,   0, 
     16,   0,   5,   0,   0,   0, 
     10,   0,  16,   0,   5,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  49,   0, 
      0,   7,  18,   0,  16,   0, 
      5,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128,  63, 
     10,   0,  16,   0,   5,   0, 
      0,   0,  60,   0,   0,   7, 
     18,   0,  16,   0,   5,   0, 
      0,   0,  10,   0,  16,   0, 
      5,   0,   0,   0,  26,   0, 
     16,   0,   5,   0,   0,   0, 
     56,   0,   0,   7, 226,   0, 
     16,   0,   5,   0,   0,   0, 
     86,   2,  16,   0,   1,   0, 
      0,   0,  86,  14,  16,   0, 
      4,   0,   0,   0,  50,   0, 
      0,  10, 226,   0,  16,   0, 
      4,   0,   0,   0, 246,   9, 
     16,   0,   4,   0,   0,   0, 
    166,   4,  16,   0,   1,   0, 
      0,   0,  86,  14,  16, 128, 
     65,   0,   0,   0,   5,   0, 
      0,   0,  16,   0,   0,   8, 
     34,   0,  16,   0,   5,   0, 
      0,   0,  70, 130,  32,   0, 
      1,   0,   0,   0,  24,   0, 
      0,   0, 150,   7,  16,   0, 
      4,   0,   0,   0,  56,   0, 
      0,   7,  34,   0,  16,   0, 
      5,   0,   0,   0,  58,   0, 
     16,   0,   2,   0,   0,   0, 
     26,   0,  16,   0,   5,   0, 
      0,   0,  49,   0,   0,   7, 
     66,   0,  16,   0,   5,   0, 
      0,   0,  26,   0,  16,   0, 
      5,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     50,   0,   0,   9, 130,   0, 
     16,   0,   3,   0,   0,   0, 
     58,   0,  16,   0,   2,   0, 
      0,   0,  58,   0,  16,   0, 
      3,   0,   0,   0,  26,   0, 
     16,   0,   5,   0,   0,   0, 
     49,   0,   0,   7, 130,   0, 
     16,   0,   3,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
    128,  63,  58,   0,  16,   0, 
      3,   0,   0,   0,  60,   0, 
      0,   7, 130,   0,  16,   0, 
      3,   0,   0,   0,  58,   0, 
     16,   0,   3,   0,   0,   0, 
     42,   0,  16,   0,   5,   0, 
      0,   0,  16,   0,   0,   7, 
     34,   0,  16,   0,   4,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0, 150,   7, 
     16,   0,   4,   0,   0,   0, 
     56,   0,   0,   7,  34,   0, 
     16,   0,   4,   0,   0,   0, 
     58,   0,  16,   0,   2,   0, 
      0,   0,  26,   0,  16,   0, 
      4,   0,   0,   0,  49,   0, 
      0,   7,  66,   0,  16,   0, 
      4,   0,   0,   0,   1,  64, 
      0,   0, 149, 191, 214,  51, 
     26,   0,  16,   0,   4,   0, 
      0,   0,  49,   0,   0,   7, 
     34,   0,  16,   0,   4,   0, 
      0,   0,  26,   0,  16,   0, 
      4,   0,   0,   0,   1,  64, 
      0,   0, 128, 150,  24,  75, 
      1,   0,   0,   7,  34,   0, 
     16,   0,   4,   0,   0,   0, 
     26,   0,  16,   0,   4,   0, 
      0,   0,  42,   0,  16,   0, 
      4,   0,   0,   0,  60,   0, 
      0,   7, 130,   0,  16,   0, 
      3,   0,   0,   0,  10,   0, 
     16,   0,   5,   0,   0,   0, 
     58,   0,  16,   0,   3,   0, 
      0,   0,  55,   0,   0,   9, 
    130,   0,  16,   0,   3,   0, 
      0,   0,  58,   0,  16,   0, 
      3,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     26,   0,  16,   0,   4,   0, 
      0,   0,  31,   0,   4,   3, 
     58,   0,  16,   0,   3,   0, 
      0,   0,  78,   0,   0,  10, 
     18,   0,  16,   0,   5,   0, 
      0,   0,  18,   0,  16,   0, 
      6,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     10, 128,  32,   0,   1,   0, 
      0,   0,  21,   0,   0,   0, 
     86,   0,   0,   5, 130,   0, 
     16,   0,   3,   0,   0,   0, 
     10,   0,  16,   0,   5,   0, 
      0,   0,  27,   0,   0,   5, 
    226,   0,  16,   0,   6,   0, 
      0,   0, 246,  15,  16,   0, 
      3,   0,   0,   0, 164,   0, 
      0,  10, 242, 224,  17,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   6,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  21,   0,   0,   1, 
     54,   0,   0,   5, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   4,   0, 
      0,   0,  22,   0,   0,   1, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 148,   0,   0,   0, 
     79,   0,   0,   0,   7,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  22,   0, 
      0,   0,  11,   0,   0,   0, 
      8,   0,   0,   0,   4,   0, 
      0,   0,   5,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     13,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,   1,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0
};
