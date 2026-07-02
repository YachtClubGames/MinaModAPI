#pragma once

#include <stdint.h>
#include <stddef.h> // size_t
#ifndef __cplusplus
	#include <stdbool.h> // c bool
#endif

#include "MinaModTypes.h"

enum { MinaModAPI_Version = 1 };

typedef void( *MM_HookCallback )( void* pCtx );
typedef void( *MM_RenderFunc )( void* userData, struct MM_RenderCtx* ctx );

struct MinaModAPI
{
	uintptr_t APIVersion;

	void*     ( *InstallHook )( const char* hookName, int32_t priority, MM_HookCallback hookCallback );
	void      ( *RemoveHook )( void* pHookHandle );

	void      ( *Log )( const char* msg, ... );
	void      ( *Assert )( bool condition, const char* msg, ... );
	void*     ( *Alloc )( size_t ); // allocate and free memory using the game's memory manager
	void      ( *Free )( void* );

	void      ( *SetSaveWriteEnabled )( bool ); // enable/disable save writing
	bool      ( *IsSaveWriteEnabled )();
	void      ( *ResetSave )(); // clear save data
	void      ( *ResetSaveSlots )();
	
	int32_t   ( *GetActiveSaveSlot )(); // get the current save slot index
	void      ( *SetActiveSaveSlot )( uint32_t slot ); // load a save slot into the active slot
	bool      ( *SetSaveSlotContents )( uint32_t slot, const char* data ); // set the contents of a save slot with ycData text
	bool      ( *SetActiveSaveSlotContents )( const char* data ); // set the contents of the currently active save slot with ycData text
	char*     ( *GetActiveSaveSlotContents )(); // get the contents of the currently active save slot as ycData text; this must be Free'd using MinaModAPI::Free
	double    ( *GetActiveSaveSlotPlayTime )(); // query information about the current save slot's play time
	double    ( *GetActiveSaveSlotPlayTimeCleared )();
	double    ( *GetActiveSaveSlotPlayTimeTotal )();

	// player state
	void      ( *PlayerGetPos )( float* x, float* y );
	void      ( *PlayerSetPos )( float x, float y );
	void      ( *PlayerDie )();
	void      ( *PlayerSetJoules )( int32_t );
	int32_t   ( *PlayerGetJoules )();
	void      ( *PlayerSetJoulesMax )( int32_t );
	void      ( *PlayerSetHealth )( float );
	float     ( *PlayerGetHealth )();
	void      ( *PlayerSetHealthUpgrade )( int32_t );
	void      ( *PlayerSetArmor )( uint32_t );
	void      ( *PlayerSetPlasma )( float );
	float     ( *PlayerGetPlasma )();
	void      ( *PlayerSetVials )( int32_t );
	int32_t   ( *PlayerGetVials )();
	void      ( *PlayerSetMaxVials )( int32_t );
	int32_t   ( *PlayerGetMaxVials )();
	void      ( *PlayerSetWeapon_ItemType )( int32_t );
	int32_t   ( *PlayerGetWeapon_ItemType )();
	void      ( *PlayerSetWeapon_WeaponIndex )( int32_t );
	int32_t   ( *PlayerGetWeapon_WeaponIndex )();
	void      ( *PlayerSetSidearm )( int32_t );
	int32_t   ( *PlayerGetSidearm )();
	void      ( *PlayerSetSidearm2 )( int32_t );
	int32_t   ( *PlayerGetSidearm2 )();
	void      ( *PlayerSetDonated )( uint32_t );
	uint32_t  ( *PlayerGetDonated )();
	void      ( *PlayerSetBones )( int32_t );
	int32_t   ( *PlayerGetBones )();
	void      ( *PlayerSetBoneStone )( int32_t );
	int32_t   ( *PlayerGetBoneStone )();
	void      ( *PlayerSetKeys )( int32_t );
	int32_t   ( *PlayerGetKeys )();
	void      ( *PlayerSetKeyFound )( uint32_t keyIdx, bool found );
	void      ( *PlayerSetKeysSpent )( int32_t );
	int32_t   ( *PlayerGetKeysSpent )();
	void      ( *PlayerSetSpark )( int32_t );
	int32_t   ( *PlayerGetSpark )();
	void      ( *PlayerSetSparkMax )( int32_t );
	int32_t   ( *PlayerGetSparkMax )();
	void      ( *PlayerSetStat )( int32_t stat, int32_t level );
	int32_t   ( *PlayerGetStat )( int32_t stat );
	void      ( *PlayerSetWeaponLevel_ItemType )( int32_t itemType, int32_t level );
	int32_t   ( *PlayerGetWeaponLevel_ItemType )( int32_t itemType );
	void      ( *PlayerSetWeaponLevel_WeaponIndex )( int32_t weaponIndex, int32_t level );
	int32_t   ( *PlayerGetWeaponLevel_WeaponIndex )( int32_t weaponIndex );
	uint32_t  ( *PlayerGetUpgrades )(); // flags
	void      ( *PlayerSetUpgrades )( uint32_t );
	uint32_t  ( *PlayerGetUpgradesSeen )();
	void      ( *PlayerSetUpgradesSeen )( uint32_t );
	void      ( *PlayerSetTrinketMax )( uint32_t );
	uint32_t  ( *PlayerGetTrinketMax )();
	void      ( *PlayerSetTrinketCollected )( int32_t trinketIndex, bool found );
	bool      ( *PlayerGetTrinketCollected )( int32_t trinketIndex );
	void      ( *PlayerSetBossesDefeated )( uint64_t ); // flags
	uint64_t  ( *PlayerGetBossesDefeated )();

	// input
	bool      ( *IsActionDown )( uint32_t act );
	bool      ( *IsActionHeld )( uint32_t act );
	bool      ( *IsButtonDown )( uint32_t btn );
	bool      ( *IsButtonHeld )( uint32_t btn );
	bool      ( *IsKeyDown )( uint32_t key );
	bool      ( *IsKeyHeld )( uint32_t key );

	// game state
	int32_t   ( *GetCurrentGameState )();
	void      ( *TransitionToGameState )( int32_t gameState );

	// room state
	uint32_t  ( *GetRoomIndex )();
	float     ( *GetRoomTime )();
	void      ( *RoomReloadGameState )();

	// session
	void      ( *StartActiveSaveSlot )();

	// entities
	void      ( *SpawnEntity )( uint32_t entityType );

	// rng
	void      ( *SeedGameRand )( uint32_t seed );

	// misc/debug
	void      ( *WarpToBoss )();
	void      ( *WarpToMiniBoss )();

	uint32_t  ( *GetEnumUInt )( const char* name );
	int32_t   ( *GetEnumInt )( const char* name );
	uint64_t  ( *GetEnumUInt64 )( const char* name );
	int64_t   ( *GetEnumInt64 )( const char* name );
	uint32_t  ( *GetEnumHashedUInt )( uint64_t nameHash );
	int32_t   ( *GetEnumHashedInt )( uint64_t nameHash );
	uint64_t  ( *GetEnumHashedUInt64 )( uint64_t nameHash );
	int64_t   ( *GetEnumHashedInt64 )( uint64_t nameHash );

	uintptr_t ( *GetSharedValue )( const char* name ); // a look up table accessible by all mods
	void      ( *SetSharedValue )( const char* name, uintptr_t val );

	uint32_t  ( *Hash32 )( const void* data, size_t len );
	uint64_t  ( *Hash64 )( const void* data, size_t len );
	
	void      ( *RunHooks )( uint64_t hookNameHash, void* ctx );

	uint32_t  ( *GetGameRevision )();

	void      ( *PlayerFlushToSave )();
	void      ( *PlayerRestoreFromSave )();

	// audio
	void      ( *SoundPlay )( const char* name );
	bool      ( *SoundIsPlaying )( const char* name );
	void      ( *SoundStop )( const char* name );
	void      ( *MusicPlay )( const char* name );
	void      ( *MusicStop )();
	bool      ( *MusicIsAnyPlaying )();
	bool      ( *MusicIsPlaying )( const char* name );

	// rendering

	/*
	render resource management functions must be run in the standard update,
	they _cannot be run from inside MM_RenderFunc_.
	*/
	MM_CLASS ycTexture*( *CreateTexture )( uint32_t width, uint32_t height ); // texture is MM_Color[width*height]
	void( *UpdateTexture )( MM_CLASS ycTexture* tex, const void* data );
	void( *DestroyTexture )( MM_CLASS ycTexture* tex );

	MM_CLASS ycGpuBuffer* ( *CreateIndexBuffer )( uint32_t count ); // index buffer data is uint32_t[count]
	MM_CLASS ycGpuBuffer* ( *CreateVertexBuffer )( uint32_t count ); // vertex buffer data is MM_Vertex_PTC[count]
	void( *UpdateGpuBuffer )( MM_CLASS ycGpuBuffer* ib , const void* data );
	void( *DestroyGpuBuffer )( MM_CLASS ycGpuBuffer* ib );

	/* valid render pass names:
		opaqueLayersArea[0], opaqueLayersArea[1], opaqueLayersArea[2], opaqueLayersArea[3]
		opaqueLayersAreaDistortion[0], opaqueLayersAreaDistortion[1], opaqueLayersAreaDistortion[2], opaqueLayersAreaDistortion[3]
		opaqueLayers
		opaqueLayersPreDistortion
		opaqueLayersDistortion
		opaque
		transparent
		transparentOverlay
		sceneCopy
		hud
		death
		deathCopy
		hudOverlay
		hudPreTransition
		hudPostTransition
		opaquePostHud
		hudDebug
		postProcess
		hudEngine
	*/
	MM_CLASS ycRenderPass*( *GetRenderPass )( const char* name );
	struct MinaModRenderObject*( *CreateRenderObject )( MM_CLASS ycRenderPass* renderPass, MM_RenderFunc renderFunc, void* userData );
	void( *DestroyRenderObject )( struct MinaModRenderObject* renderObject );
	const union MM_Mtx*( *GetRenderObjectTransform )( struct MinaModRenderObject* renderObject );
	void( *SetRenderObjectTransform )( struct MinaModRenderObject* renderObject, const union MM_Mtx* transform ); // transform should be modified from update, not MM_RenderFunc

	void( *RenderDrawCallSetIndexBuffer )( struct ycRenderDrawCall* dc, MM_CLASS ycGpuBuffer* ib );
	void( *RenderDrawCallSetVertexBuffer )( struct ycRenderDrawCall* dc, MM_CLASS ycGpuBuffer* vb );
	void( *RenderDrawCallSetTexture )( struct ycRenderDrawCall* dc, MM_CLASS ycTexture* tex );
	
	void( *RenderCmdDraw )( MM_CLASS ycRenderCmdList* cmds, struct ycRenderDrawCall* dc, uint32_t vertexCount, uint32_t startVertex );
	void( *RenderCmdDrawIndexed )( MM_CLASS ycRenderCmdList* cmds, struct ycRenderDrawCall* dc, uint32_t indexCount, uint32_t startIndex );

	// debug draw functions should be used from the game update, not from MM_RenderFunc
	/* valid debug draw names:
	World
	WorldBlend
	WorldHD
	Hud
	GameHud
	WorldPersist
	EngineHUD
	*/
	MM_CLASS ycDrawUtil*( *GetDebugDraw )( const char* name );
	void( *DebugDrawRect )( MM_CLASS ycDrawUtil* dd, struct MM_Vec3 center, float w, float h, struct MM_Color color, bool disableDepthTest );
	void( *DebugDrawRectSolid )( MM_CLASS ycDrawUtil* dd, struct MM_Vec3 center, float w, float h, struct MM_Color color, bool disableDepthTest );
	void( *DebugDrawLine )( MM_CLASS ycDrawUtil* dd, struct MM_Vec3 p1, struct MM_Vec3 p2, struct MM_Color color, bool disableDepthTest );
	void( *DebugDrawTexturedQuad )( MM_CLASS ycDrawUtil* dd, MM_CLASS ycTexture* tex, struct MM_Vec3 center, float w, float h, struct MM_Color mulColor, bool disableDepthTest );

	// entities & components

	MM_CLASS ycComponent* ( *SpawnEntity2 )( MM_CLASS ycEntity* parent, uint32_t entityType, struct MM_Vec3 pos, struct MM_Vec3 scale, float rot, int32_t collisionLayer, void*, void*, void* ); // set last three parameters to nullptr

	MM_CLASS ycEntity* ( *WorldGetGameRootEntity )( MM_CLASS World* world );
	MM_CLASS ycEntity* ( *WorldGetSystemRootEntity )( MM_CLASS World* world );
	MM_CLASS ycEntity* ( *WorldGetMenuRootEntity )( MM_CLASS World* world );
	MM_CLASS ycEntity* ( *WorldGetHUDRootEntity )( MM_CLASS World* world );
	MM_CLASS World* ( *EntityGetWorld )( MM_CLASS ycEntity* entity );
	size_t( *EntityGetChildren )( MM_CLASS ycEntity* entity, MM_CLASS ycComponent** children, size_t bufElemCount ); // always returns the total count even if the buffer is not large enough; pass null/0 to just get the count
	MM_CLASS ycComponent* ( *EntityGetMainComponent )( MM_CLASS ycEntity* entity );
	struct MM_StringRef( *ComponentGetTypeName )( MM_CLASS ycComponent* component );
	MM_CLASS ycComponent* ( *PlayerGetComponent )();
	MM_CLASS ycEntity* ( *ComponentGetParent )( MM_CLASS ycComponent* component );
	MM_Rtti( *ComponentGetType )( MM_CLASS ycComponent* component );
	bool( *ComponentIsa )( MM_CLASS ycComponent* component, MM_Rtti rtti ); // includes inheritance
	struct MM_Transform ( *EntityGetLocalTransform )( MM_CLASS ycEntity* entity );
	void( *EntitySetLocalTransform )( MM_CLASS ycEntity* entity, const struct MM_Transform* transform );
	struct MM_Transform ( *EntityGetWorldTransform )( MM_CLASS ycEntity* entity );
	void( *EntitySetWorldTransform )( MM_CLASS ycEntity* entity, const struct MM_Transform* transform );
	void( *ComponentMove )( MM_CLASS ycComponent* component, struct MM_Vec3 vel ); // works through a MoveComponent, if a relevant one exists; does nothing otherwise

	// CombatCore component
	float( *CombatCoreGetHealth )( MM_CLASS ycComponent* combatCore );
	void( *CombatCoreSetHealth )( MM_CLASS ycComponent* combatCore, float hp );
	float( *CombatCoreGetHealthMax )( MM_CLASS ycComponent* combatCore );
	void( *CombatCoreSetHealthMax )( MM_CLASS ycComponent* combatCore, float hp );
	MM_CLASS CombatShape* ( *CombatCoreGetAttackShape )( MM_CLASS ycComponent* combatCore );
	MM_CLASS CombatShape* ( *CombatCoreGetDefenseShape )( MM_CLASS ycComponent* combatCore );
	uint32_t ( *CombatCoreGetAttackMask )( MM_CLASS ycComponent* combatCore );
	void ( *CombatCoreSetAttackMask )( MM_CLASS ycComponent* combatCore, uint32_t mask );
	uint32_t ( *CombatCoreGetDefenseMask )( MM_CLASS ycComponent* combatCore );
	void ( *CombatCoreSetDefenseMask )( MM_CLASS ycComponent* combatCore, uint32_t mask );
	uint32_t( *CombatShapeGetShapeCount )( MM_CLASS CombatShape* shape );
	bool( *CombatShapeIsAABB )( MM_CLASS CombatShape* shape, uint32_t shapeIndex );
	bool( *CombatShapeIsSphere )( MM_CLASS CombatShape* shape, uint32_t shapeIndex );
	bool( *CombatShapeIsLineSeg )( MM_CLASS CombatShape* shape, uint32_t shapeIndex );
	bool( *CombatShapeGetAABB )( MM_CLASS CombatShape* shape, uint32_t shapeIndex, struct MM_AABB* aabb ); // returns false if shape is not an AABB
	bool( *CombatShapeGetSphere )( MM_CLASS CombatShape* shape, uint32_t shapeIndex, struct MM_Sphere* sphere );
	bool( *CombatShapeGetLineSeg )( MM_CLASS CombatShape* shape, uint32_t shapeIndex, struct MM_LineSeg* lineSeg );
	void( *CombatShapeSetAABB )( MM_CLASS CombatShape* shape, uint32_t shapeIndex, const struct MM_AABB* aabb ); // these functions can append a new shape
	void( *CombatShapeSetSphere )( MM_CLASS CombatShape* shape, uint32_t shapeIndex, const struct MM_Sphere* sphere );
	void( *CombatShapeSetLineSeg )( MM_CLASS CombatShape* shape, uint32_t shapeIndex, const struct MM_LineSeg* lineSeg );

	// GameAnim component
	void( *GameAnimInit )( MM_CLASS ycComponent* anim, const char* filename, void* ); // set second argument to null
	void( *GameAnimPlayDir )( MM_CLASS ycComponent* anim, const char* seqName, int32_t loops, float speed, bool forceRestart );
	void( *GameAnimPlay )( MM_CLASS ycComponent* anim, const char* seqName, int32_t loops, float speed, bool forceRestart );
	bool( *GameAnimIsPaused )( MM_CLASS ycComponent* anim );
	void( *GameAnimSetPaused )( MM_CLASS ycComponent* anim, bool paused );
	bool( *GameAnimIsDone )( MM_CLASS ycComponent* anim );
	bool( *GameAnimIsNewFrame )( MM_CLASS ycComponent* anim );
	uint32_t( *GameAnimGetSeqFrameIdx )( MM_CLASS ycComponent* anim );
	struct MM_StringRef( *GameAnimGetSeqName )( MM_CLASS ycComponent* anim );
	struct MM_StringRef( *GameAnimGetSeqNameNoDir )( MM_CLASS ycComponent* anim );
};
