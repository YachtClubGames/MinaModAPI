#pragma once

#ifdef __cplusplus
	#define MM_CLASS class
#else
	#define MM_CLASS struct
#endif

struct MM_Color
{
	uint8_t r, g, b, a;
};

struct MM_Vec2
{
	float x, y;
};

struct MM_Vec3
{
	float x, y, z;
};

struct MM_Vec4
{
	float x, y, z, w;
};

union MM_Mtx
{
	//struct { struct MM_Vec4 x, y, z, t; };
	float a[ 16 ];
	float m[ 4 ][ 4 ];
};

struct MM_Quat
{
	float x, y, z, w;
};

struct MM_Transform
{
	struct MM_Quat r; // rotation
	struct MM_Vec3 s; // scale
	struct MM_Vec3 t; // translation
};

struct MM_AABB
{
	struct MM_Vec3 center;
	struct MM_Vec3 extents;
};

struct MM_Sphere
{
	struct MM_Vec3 center;
	float radius;
};

struct MM_LineSeg
{
	struct MM_Vec3 p1, p2;
};

struct MM_StringRef // this is not gauranteed to be NUL terminated (but often is)
{
	const char* str;
	size_t len;
};

typedef uint64_t MM_Rtti;

struct MinaModRenderObject;

MM_CLASS ycRenderObject;
MM_CLASS ycRenderPass;
MM_CLASS ycGpuBuffer;
MM_CLASS ycTexture;
MM_CLASS ycRenderCmdList;
struct ycRenderDrawCall;

struct MM_RenderCtx
{
	struct MinaModRenderObject* renderObject;
	const union MM_Mtx* proj;
	const union MM_Mtx* view;
	MM_CLASS ycRenderCmdList* cmdList;
	struct ycRenderDrawCall* drawCall;
};

struct MM_Vertex_PTC
{
	struct MM_Vec3  pos;
	float           u, v;
	struct MM_Color color;
};

MM_CLASS ycComponent;
MM_CLASS ycDrawUtil;
MM_CLASS ycEntity;

MM_CLASS World;
MM_CLASS CombatShape;
MM_CLASS GameAnim;
