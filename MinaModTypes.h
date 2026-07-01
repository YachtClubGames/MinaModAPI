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
