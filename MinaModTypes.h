#pragma once

#ifdef __cplusplus
	#define MM_FWD_CLASS(x) class x;
	#define MM_FWD_STRUCT(x) struct x;
#else
	#define MM_FWD_CLASS(x) typedef struct x x;
	#define MM_FWD_STRUCT(x) typedef struct x x;
#endif

//
// engine
//

// direct access to engine level classes/structs

MM_FWD_CLASS( ycCamera )
MM_FWD_CLASS( ycComponent )
MM_FWD_CLASS( ycDrawUtil )
MM_FWD_CLASS( ycEntity )
MM_FWD_CLASS( ycUpdateQueue )
MM_FWD_CLASS( ycRenderObject )
MM_FWD_CLASS( ycRenderPass )
MM_FWD_CLASS( ycGpuBuffer )
MM_FWD_CLASS( ycTexture )
MM_FWD_CLASS( ycRenderCmdList )
MM_FWD_STRUCT( ycRenderDrawCall )
MM_FWD_CLASS( ycFileRefBase )
MM_FWD_CLASS( ycPaletteTexture )

//
// file formats
//

MM_FWD_STRUCT( ycTileLevel2Entity );

//
// game
//

// direct access to game level classes/structs

MM_FWD_CLASS( CombatShape )
MM_FWD_CLASS( GameAnim )
MM_FWD_CLASS( GameCamera )
MM_FWD_CLASS( GameComponent )
MM_FWD_CLASS( SpawnManager )
MM_FWD_CLASS( SpawnPoint )
MM_FWD_CLASS( World )
MM_FWD_CLASS( WorldRegion )

//
// mod utilities
//

// MM_ remappings from engine/game classes and structs to mod-visible versions
//   these generally have the same data layout as yc versions
// MinaMod wrappers for engine concepts
//   these convert engine features to simpler forms

typedef struct MinaModRenderCtx MinaModRenderCtx;
typedef void( *MinaModRenderFunc )( void* userData, MinaModRenderCtx* ctx );
typedef void( *MinaModUpdateQueueCallback )( void* userData );

typedef struct MinaModRenderObject MinaModRenderObject;
typedef struct MM_WeakPtr MM_WeakPtr;

#if defined MM_USE_YC_TYPES && __has_include("ycColor.h")
	#include "ycColor.h"
	typedef ycColor MM_Color;
#else
	typedef struct alignas(4) MM_Color
	{
		uint8_t r, g, b, a;
	} MM_Color;
#endif

#if defined MM_USE_YC_TYPES && __has_include("ycVec2.h")
	#include "ycVec2.h"
	typedef ycVec2 MM_Vec2;
#else
	typedef struct MM_Vec2
	{
		float x, y;
	} MM_Vec2;
#endif

#if defined MM_USE_YC_TYPES && __has_include("ycVec3.h")
	#include "ycVec3.h"
	typedef ycVec3 MM_Vec3;
#else
	typedef struct MM_Vec3
	{
		float x, y, z;
	} MM_Vec3;
#endif

#if defined MM_USE_YC_TYPES && __has_include("ycVec4.h")
	#include "ycVec4.h"
	typedef ycVec4 MM_Vec4;
#else
	typedef struct MM_Vec4
	{
		float x, y, z, w;
	} MM_Vec4;
#endif

#if defined MM_USE_YC_TYPES && __has_include("ycMtx4.h")
	#include "ycMtx4.h"
	typedef ycMtx4 MM_Mtx;
#else
	typedef struct MM_Mtx
	{
	#if defined __cplusplus || ( defined __STDC_VERSION__ && __STDC_VERSION__ >= 201112L )
		//union
		//{
		//	struct { MM_Vec4 x, y, z, t; };
			float a[ 16 ];
		//	float m[ 4 ][ 4 ];
		//};
	#else
		float a[ 16 ];
	#endif
	} MM_Mtx;
#endif

#if defined MM_USE_YC_TYPES && __has_include("ycQuat.h")
	#include "ycQuat.h"
	typedef ycQuat MM_Quat;
#else
	typedef struct MM_Quat
	{
		float x, y, z, w;
	} MM_Quat;
#endif

#if defined MM_USE_YC_TYPES && __has_include("ycTransform.h")
	#include "ycTransform.h"
	typedef ycTransform MM_Transform;
#else
	typedef struct MM_Transform
	{
		MM_Quat r; // rotation
		MM_Vec3 s; // scale
		MM_Vec3 t; // translation
	} MM_Transform;
#endif

#if defined MM_USE_YC_TYPES && __has_include("ycAABB.h")
	#include "ycAABB.h"
	typedef ycAABB MM_AABB;
#else
	typedef struct MM_AABB
	{
		MM_Vec3 center;
		MM_Vec3 extents;
	} MM_AABB;
#endif

#if defined MM_USE_YC_TYPES && __has_include("ycCircle.h")
	#include "ycCircle.h"
	typedef ycCircle MM_Circle;
#else
	typedef struct MM_Circle
	{
		MM_Vec3 center;
		MM_Vec3 normal;
		float radius;
	} MM_Circle;
#endif

#if defined MM_USE_YC_TYPES && __has_include("ycSphere.h")
	#include "ycSphere.h"
	typedef ycSphere MM_Sphere;
#else
	typedef struct MM_Sphere
	{
		MM_Vec3 center;
		float radius;
	} MM_Sphere;
#endif

#if defined MM_USE_YC_TYPES && __has_include("ycLineSeg.h")
	#include "ycLineSeg.h"
	typedef ycLineSeg MM_LineSeg;
#else
	typedef struct MM_LineSeg
	{
		MM_Vec3 p1, p2;
	} MM_LineSeg;
#endif

#if defined MM_USE_YC_TYPES && __has_include("ycStringRef.h")
	#include "ycStringRef.h"
	typedef ycStringRef MM_StringRef;
#else
	typedef struct MM_StringRef // this is not guaranteed to be NUL terminated (but often is)
	{
		const char* str;
		size_t len;
	} MM_StringRef;
#endif

#if defined MM_USE_YC_TYPES && __has_include("ycRtti.h")
	#include "ycRtti.h"
	typedef ycRtti MM_Rtti;
#else
	typedef struct MM_Rtti
	{
		uint64_t typeId;
	} MM_Rtti;
#endif

typedef struct MinaModRenderCtx
{
	MinaModRenderObject* renderObject;
	const MM_Mtx* proj;
	const MM_Mtx* view;
	ycRenderCmdList* cmdList;
	ycRenderDrawCall* drawCall;
} MinaModRenderCtx;

#if defined MM_USE_YC_TYPES && __has_include("ycVertexFormats.h")
	#include "ycVertexFormats.h"
	typedef ycVertexFormats::PTC MM_Vertex_PTC;
#else
	typedef struct MM_Vertex_PTC
	{
		MM_Vec3  pos;
		float    u, v;
		MM_Color color;
	} MM_Vertex_PTC;
#endif
