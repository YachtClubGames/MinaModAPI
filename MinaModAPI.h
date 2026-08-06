#pragma once

#include <stdint.h>
#include <stddef.h> // size_t
#ifndef __cplusplus
	#include <stdbool.h> // c bool
#endif

// if you have the classes from here:
// https://github.com/YachtClubGames/Propeller
// you can set this to use the real types directly
//#if defined __cplusplus && defined __has_include && __has_include("ycCommon.h")
	/*
	This must remain off for now, it is ABI-incompatible, we can resolve this
	when we are moving out of experimental, when there will be other ABI-breaking
	changes anyway. Specifically, on Windows, functions that return MM_ types by
	value are not compatible.
	https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170#return-values

	You _can_ use the Propeller types yourself, casting MM_ types to their yc
	equivalents will work in your mod code. But the mod API functions cannot
	safely return some of them by value.
	*/
	//#define MM_USE_YC_TYPES
//#endif

#include "MinaModTypes.h"

// portable export attribute for the MinaMod_Init entry point
#ifdef __cplusplus
	#define MM_EXPORT_EXTERN extern "C"
#else
	#define MM_EXPORT_EXTERN
#endif
#ifdef _WIN32
	#define MM_EXPORT MM_EXPORT_EXTERN __declspec(dllexport)
#else
	#define MM_EXPORT MM_EXPORT_EXTERN __attribute__(( visibility( "default" ) ))
#endif

enum { MinaModAPI_Version = 1 };

typedef void( *MM_HookCallback )( void* pCtx );

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
	void      ( *PlayerSetJoulesUpgrade )( int32_t );
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
	they _cannot be run from inside MinaModRenderFunc_.
	*/
	ycTexture*   ( *CreateTexture )( uint32_t width, uint32_t height ); // texture is MM_Color[width*height]
	void         ( *UpdateTexture )( ycTexture* tex, const void* data );
	void         ( *DestroyTexture )( ycTexture* tex );

	ycGpuBuffer* ( *CreateIndexBuffer )( uint32_t count ); // index buffer data is uint32_t[count]
	ycGpuBuffer* ( *CreateVertexBuffer )( uint32_t count ); // vertex buffer data is MM_Vertex_PTC[count]
	void         ( *UpdateGpuBuffer )( ycGpuBuffer* ib , const void* data );
	void         ( *DestroyGpuBuffer )( ycGpuBuffer* ib );

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
	ycRenderPass*       ( *GetRenderPass )( const char* name );
	MinaModRenderObject*( *CreateRenderObject )( ycRenderPass* renderPass, MinaModRenderFunc renderFunc, void* userData );
	void                ( *DestroyRenderObject )( MinaModRenderObject* renderObject );
	const MM_Mtx*       ( *GetRenderObjectTransform )( MinaModRenderObject* renderObject );
	void                ( *SetRenderObjectTransform )( MinaModRenderObject* renderObject, const MM_Mtx* transform ); // transform should be modified from update, not MinaModRenderFunc

	void                ( *RenderDrawCallSetIndexBuffer )( ycRenderDrawCall* dc, ycGpuBuffer* ib );
	void                ( *RenderDrawCallSetVertexBuffer )( ycRenderDrawCall* dc, ycGpuBuffer* vb );
	void                ( *RenderDrawCallSetTexture )( ycRenderDrawCall* dc, ycTexture* tex );
	
	void                ( *RenderCmdDraw )( ycRenderCmdList* cmds, ycRenderDrawCall* dc, uint32_t vertexCount, uint32_t startVertex );
	void                ( *RenderCmdDrawIndexed )( ycRenderCmdList* cmds, ycRenderDrawCall* dc, uint32_t indexCount, uint32_t startIndex );

	// debug draw functions should be used from the game update, not from MinaModRenderFunc
	/* valid debug draw names:
		World
		Hud
		WorldPersist
		EngineHUD
	*/
	ycDrawUtil*( *GetDebugDraw )( const char* name );
	void       ( *DebugDrawRect )( ycDrawUtil* dd, MM_Vec3 center, float w, float h, MM_Color color, bool disableDepthTest );
	void       ( *DebugDrawRectSolid )( ycDrawUtil* dd, MM_Vec3 center, float w, float h, MM_Color color, bool disableDepthTest );
	void       ( *DebugDrawLine )( ycDrawUtil* dd, MM_Vec3 p1, MM_Vec3 p2, MM_Color color, bool disableDepthTest );
	void       ( *DebugDrawTexturedQuad )( ycDrawUtil* dd, ycTexture* tex, MM_Vec3 center, float w, float h, MM_Color mulColor, bool disableDepthTest );

	// entities & components

	GameComponent*( *SpawnEntity2 )( ycEntity* parent, uint32_t entityType, MM_Vec3 pos, MM_Vec3 scale, float rot, int32_t collisionLayer, SpawnPoint* spawnPoint, void*, void* ); // set last two parameters to nullptr

	ycEntity*     ( *WorldGetGameRootEntity )( World* world );
	ycEntity*     ( *WorldGetSystemRootEntity )( World* world );
	ycEntity*     ( *WorldGetMenuRootEntity )( World* world );
	ycEntity*     ( *WorldGetHUDRootEntity )( World* world );
	World*        ( *EntityGetWorld )( ycEntity* entity );
	size_t        ( *EntityGetChildren )( ycEntity* entity, ycComponent** children, size_t bufElemCount ); // always returns the total count even if the buffer is not large enough; pass null/0 to just get the count
	ycComponent*  ( *EntityGetMainComponent )( ycEntity* entity );
	MM_StringRef  ( *ComponentGetTypeName )( ycComponent* component );
	ycComponent*  ( *PlayerGetComponent )();
	ycEntity*     ( *ComponentGetParent )( ycComponent* component );
	MM_Rtti       ( *ComponentGetType )( ycComponent* component );
	bool          ( *ComponentIsa )( ycComponent* component, MM_Rtti rtti ); // includes inheritance
	MM_Transform  ( *EntityGetLocalTransform )( ycEntity* entity );
	void          ( *EntitySetLocalTransform )( ycEntity* entity, const MM_Transform* transform );
	MM_Transform  ( *EntityGetWorldTransform )( ycEntity* entity );
	void          ( *EntitySetWorldTransform )( ycEntity* entity, const MM_Transform* transform );
	void          ( *ComponentMove )( ycComponent* component, MM_Vec3 vel ); // works through a MoveComponent, if a relevant one exists; does nothing otherwise

	// CombatCore component
	float        ( *CombatCoreGetHealth )( ycComponent* combatCore );
	void         ( *CombatCoreSetHealth )( ycComponent* combatCore, float hp );
	float        ( *CombatCoreGetHealthMax )( ycComponent* combatCore );
	void         ( *CombatCoreSetHealthMax )( ycComponent* combatCore, float hp );
	CombatShape* ( *CombatCoreGetAttackShape )( ycComponent* combatCore );
	CombatShape* ( *CombatCoreGetDefenseShape )( ycComponent* combatCore );
	uint32_t     ( *CombatCoreGetAttackMask )( ycComponent* combatCore );
	void         ( *CombatCoreSetAttackMask )( ycComponent* combatCore, uint32_t mask );
	uint32_t     ( *CombatCoreGetDefenseMask )( ycComponent* combatCore );
	void         ( *CombatCoreSetDefenseMask )( ycComponent* combatCore, uint32_t mask );
	uint32_t     ( *CombatShapeGetShapeCount )( CombatShape* shape );
	bool         ( *CombatShapeIsAABB )( CombatShape* shape, uint32_t shapeIndex );
	bool         ( *CombatShapeIsSphere )( CombatShape* shape, uint32_t shapeIndex );
	bool         ( *CombatShapeIsLineSeg )( CombatShape* shape, uint32_t shapeIndex );
	bool         ( *CombatShapeGetAABB )( CombatShape* shape, uint32_t shapeIndex, MM_AABB* aabb ); // returns false if shape is not an AABB
	bool         ( *CombatShapeGetSphere )( CombatShape* shape, uint32_t shapeIndex, MM_Sphere* sphere );
	bool         ( *CombatShapeGetLineSeg )( CombatShape* shape, uint32_t shapeIndex, MM_LineSeg* lineSeg );
	void         ( *CombatShapeSetAABB )( CombatShape* shape, uint32_t shapeIndex, const MM_AABB* aabb ); // these functions can append a new shape
	void         ( *CombatShapeSetSphere )( CombatShape* shape, uint32_t shapeIndex, const MM_Sphere* sphere );
	void         ( *CombatShapeSetLineSeg )( CombatShape* shape, uint32_t shapeIndex, const MM_LineSeg* lineSeg );

	// GameAnim component
	void        ( *GameAnimInit )( ycComponent* anim, const char* filename, void* ); // set third argument to null
	void        ( *GameAnimPlayDir )( ycComponent* anim, const char* seqName, int32_t loops, float speed, bool forceRestart );
	void        ( *GameAnimPlay )( ycComponent* anim, const char* seqName, int32_t loops, float speed, bool forceRestart );
	bool        ( *GameAnimIsPaused )( ycComponent* anim );
	void        ( *GameAnimSetPaused )( ycComponent* anim, bool paused );
	bool        ( *GameAnimIsDone )( ycComponent* anim );
	bool        ( *GameAnimIsNewFrame )( ycComponent* anim );
	uint32_t    ( *GameAnimGetSeqFrameIdx )( ycComponent* anim );
	MM_StringRef( *GameAnimGetSeqName )( ycComponent* anim );
	MM_StringRef( *GameAnimGetSeqNameNoDir )( ycComponent* anim );

	// update queues
	ycUpdateQueue*( *WorldGetPlayerUpdateQueue )( World* world );
	ycUpdateQueue*( *WorldGetEntityUpdateQueue )( World* world );
	ycUpdateQueue*( *WorldGetEntityHitUpdateQueue )( World* world );
	ycUpdateQueue*( *WorldGetSystemPreUpdateQueue )( World* world );
	ycUpdateQueue*( *WorldGetSystemPostUpdateQueue )( World* world );
	ycUpdateQueue*( *WorldGetEntityPostUpdateQueue )( World* world );
	ycUpdateQueue*( *WorldGetEntityPostArtUpdateQueue )( World* world );
	ycUpdateQueue*( *WorldGetEntityPreUpdateQueue )( World* world );
	ycUpdateQueue*( *WorldGetPostSimUpdateQueue )( World* world );
	ycUpdateQueue*( *WorldGetHUDUpdateQueue )( World* world );
	ycUpdateQueue*( *WorldGetPauseUpdateQueue )( World* world );
	ycUpdateQueue*( *WorldGetPauseCheckUpdateQueue )( World* world );
	ycUpdateQueue*( *GameGetWorldUpdateQueue )(); // the game's update queue of worlds
	void*         ( *UpdateQueueAdd )( ycUpdateQueue* updateQueue, MinaModUpdateQueueCallback cb, void* userData ); // returns a handle to be used with UpdateQueueRemove
	void          ( *UpdateQueueRemove )( void* handle );

	// pause
	void( *WorldPause )( World* world, bool menu );
	void( *WorldResume )( World* world );
	bool( *WorldIsPaused )( World* world );
	bool( *WorldIsPauseAllowed )( World* world );
	void( *WorldSetPauseAllowed )( World* world, bool enable );

	// weak pointers / safe references
	MM_WeakPtr*( *CreateWeakPtr )( void* componentOrEntity );
	void       ( *DestroyWeakPtr )( MM_WeakPtr* weakPtr );
	void*      ( *WeakPtrGet )( MM_WeakPtr* weakPtr );

	// debug draw
	void   ( *DebugDrawTexturedQuadUV )( ycDrawUtil* dd, ycTexture* tex, MM_Vec3 center, MM_Vec2 size, MM_Vec2 uvCenter, MM_Vec2 uvSize, MM_Color mulColor, bool disableDepthTest );
	// to use the text functionality, a mod must load a debugdraw.font.yc file (see examples/chests.cpp)
	MM_Vec3( *DebugDrawText )( ycDrawUtil* dd, const char* text, MM_Color color, MM_Vec3 pos, float fontSize ); // returns dimensions of the text
	MM_Vec3( *DebugDrawTextAlign )( ycDrawUtil* dd, const char* text, MM_Color color, MM_Vec3 pos, uint64_t align, MM_Vec2 dimensions, float fontSize );

	// file access
	ycFileRefBase*( *CreateFileRef )( const char* name ); // this does not block, it will return immediately
	void          ( *DestroyFileRef )( ycFileRefBase* fileRef );
	bool          ( *FileRefWaitForLoaded )( ycFileRefBase* fileRef ); // blocks until the file is loaded or an error occurs, returns true if the file was loaded
	const uint8_t*( *FileRefGetData )( ycFileRefBase* fileRef );
	size_t        ( *FileRefGetSize )( ycFileRefBase* fileRef );

	// player
	MM_Vec3     ( *PlayerGetPos3 )();
	void        ( *PlayerSetPos3 )( MM_Vec3 pos );
	World*      ( *PlayerGetWorld )();
	WorldRegion*( *PlayerGetWorldRegion )();

	// GameComponent
	World*      ( *GameComponentGetWorld )( GameComponent* component );
	WorldRegion*( *GameComponentGetWorldRegion )( GameComponent* component );

	// Spawn Points
	/* valid spawn type names:
		Infinite                 Respawn when entity culled, respawn when entity killed.
		PersistentA              Spawn once immediately on level start, regardless of spawn camera rules. culls with world
		Persistent               Spawn once immediately on level start, regardless of spawn camera rules. culls with region
		Room                     Spawn once immediately on room gameplay start.
		RoomTransition           Spawn once immediately on room transition start.
		RoomTransitionInfinite   Spawn on room transition start, otherwise behave like infinite.
		RoomViewInfinite         Spawn on room transition start (if in initial room view), otherwise behave like infinite.
		Contents                 Spawn once when parent spawn point has a killed object.
		Child                    Spawn when parent spawn point spawns.
		RoomInfinite             Spawns on room gameplay start. Respawns like infinite if killed (and still in room)
		RangeEnter               Spawns on player entering range.
		RangeExit                Spawns on player leaving range.
		Present                  Spawn is triggered within code. Presented by an NPC or created through a script.
		Disable                  Don't spawn at all.
		SpawnChildren            Only spawn children, don't spawn us.
	*/
	uint8_t            ( *TileLevelEntityGetSpawnType )( const char* name ); // returns 0xff if no valid value is found
	ycTileLevel2Entity*( *CreateTileLevelEntity )( const char* ycdata ); // returned pointer should be freed with DestroyTileLevelEntity
	void               ( *DestroyTileLevelEntity )( ycTileLevel2Entity* tileLevelEntity );
	char*              ( *SpawnPointGetTileLevelEntity )( SpawnPoint* spawnPoint ); // returned string should be freed with Free()
	SpawnPoint*        ( *GameComponentGetSpawnPoint )( GameComponent* component );
	SpawnManager*      ( *WorldRegionGetSpawnManager )( WorldRegion* worldRegion );
	SpawnPoint*        ( *SpawnManagerCreateSpawnPoint )( SpawnManager* spawnManager, WorldRegion* worldRegion, MM_Vec3 pos, MM_Vec3 scale, float rot, uint32_t entityType, uint8_t spawnType, uint8_t tileLayerIndex, int32_t collisionLayerIndex );
	SpawnPoint*        ( *SpawnManagerCreateSpawnPoint2 )( SpawnManager* spawnManager, WorldRegion* worldRegion, const ycTileLevel2Entity* tileLevelEntity );
	void               ( *SpawnManagerDestroySpawnPoint )( SpawnManager* spawnManager, SpawnPoint* spawnPoint );
	SpawnPoint*        ( *SpawnManagerGetSpawnPointByName )( SpawnManager* spawnManager, const char* name );
	SpawnPoint*        ( *SpawnManagerGetSpawnPointByNameHash )( SpawnManager* spawnManager, uint32_t nameHash );
	SpawnPoint*        ( *SpawnManagerGetSpawnPointByTileLevelEntity )( SpawnManager* spawnManager, const ycTileLevel2Entity* tileLevelEntity );
	SpawnPoint*        ( *SpawnManagerGetSpawnPointByNameLevelHash )( SpawnManager* spawnManager, uint64_t nameLevelHash );
	uint8_t            ( *SpawnPointGetTileLayerIndex )( SpawnPoint* spawnPoint );
	bool               ( *SpawnPointIsPersistent )( SpawnPoint* spawnPoint );
	bool               ( *SpawnPointIsEntitySpawned )( SpawnPoint* spawnPoint );
	bool               ( *SpawnPointIsAwaitingSpawn )( SpawnPoint* spawnPoint );
	bool               ( *SpawnPointIsEntityCulled )( SpawnPoint* spawnPoint );
	bool               ( *SpawnPointIsEntityKilled )( SpawnPoint* spawnPoint );
	bool               ( *IsEntityPermanentKilled )( SpawnPoint* spawnPoint, bool checkSecretDirt );
	bool               ( *SpawnPointIsEntityPermanentKilledType )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointReset )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointResetPosToStart )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointResetAll )( SpawnPoint* spawnPoint );
	bool               ( *SpawnPointIsDisabled )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointDisable )( SpawnPoint* spawnPoint ); // call Reset() to return to AwaitingSpawn
	void               ( *SpawnPointSetSpawnType )( SpawnPoint* spawnPoint, uint8_t spawnType );
	uint8_t            ( *SpawnPointGetSpawnType )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointDisownParent )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointSetupParentSpawnPoint )( SpawnPoint* spawnPoint, SpawnPoint* parent ); // same as calling SetParent + SetChild, and also saves the starting position
	void               ( *SpawnPointSetParentSpawnPoint )( SpawnPoint* spawnPoint, SpawnPoint* parent );
	void               ( *SpawnPointSetChildSpawnPoint )( SpawnPoint* spawnPoint, SpawnPoint* child );
	bool               ( *SpawnPointHasChildSpawnPoint )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointSetChildSpawnEnabled )( SpawnPoint* spawnPoint, bool enabled );
	bool               ( *SpawnPointIsChildSpawnEnabled )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointSetForceChildSpawn )( SpawnPoint* spawnPoint, bool force );
	bool               ( *SpawnPointIsForceChildSpawn )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointSetForceChildOffset )( SpawnPoint* spawnPoint, bool force );
	bool               ( *SpawnPointIsForceChildOffset )( SpawnPoint* spawnPoint );
	SpawnPoint*        ( *SpawnPointGetParent )( SpawnPoint* spawnPoint );
	SpawnPoint*        ( *SpawnPointGetChild )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointSetChildOffset )( SpawnPoint* spawnPoint, MM_Vec3 offset );
	MM_Vec3            ( *SpawnPointGetChildOffset )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointSetChildSpawnDir )( SpawnPoint* spawnPoint, MM_Vec3 dir );
	MM_Vec3            ( *SpawnPointGetChildSpawnDir )( SpawnPoint* spawnPoint );
	uint32_t           ( *SpawnPointGetEntityType )( SpawnPoint* spawnPoint );
	uint32_t           ( *SpawnPointGetNameHash )( SpawnPoint* spawnPoint );
	uint64_t           ( *SpawnPointGetNameLevelHash )( SpawnPoint* spawnPoint );
	uint32_t           ( *SpawnPointGetLayerNameHash )( SpawnPoint* spawnPoint );
	MM_AABB            ( *SpawnPointGetArea )( SpawnPoint* spawnPoint );
	int32_t            ( *SpawnPointGetCollisionLayer )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointSetCollisionLayer )( SpawnPoint* spawnPoint, uint32_t idx );
	MM_Vec3            ( *SpawnPointGetPos )( SpawnPoint* spawnPoint );
	MM_Vec3            ( *SpawnPointGetPosStart )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointSetPos )( SpawnPoint* spawnPoint, MM_Vec3 pos );
	MM_Vec3            ( *SpawnPointGetScale )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointSetScale )( SpawnPoint* spawnPoint, MM_Vec3 scale );
	float              ( *SpawnPointGetRotation )( SpawnPoint* spawnPoint );
	void               ( *SpawnPointSetRotation )( SpawnPoint* spawnPoint, float rot );
	void               ( *SpawnPointSetSpawnedEntity )( SpawnPoint* spawnPoint, GameComponent* entity );
	GameComponent*     ( *SpawnPointGetSpawnedEntity )( SpawnPoint* spawnPoint );
	MM_StringRef       ( *SpawnPointGetPropertyString )( SpawnPoint* spawnPoint, const char* name, MM_StringRef defaultValue );
	MM_StringRef       ( *SpawnPointGetPropertyByHash )( SpawnPoint* spawnPoint, uint32_t hash, MM_StringRef defaultValue );
	bool               ( *SpawnPointGetPropertyBool )( SpawnPoint* spawnPoint, const char* propName, bool defaultValue );
	float              ( *SpawnPointGetPropertyFloat )( SpawnPoint* spawnPoint, const char* propName, float defaultValue );
	int32_t            ( *SpawnPointGetPropertyInt )( SpawnPoint* spawnPoint, const char* propName, int32_t defaultValue );
	bool               ( *SpawnPointGetPropertyExists )( SpawnPoint* spawnPoint, const char* propName );
	bool               ( *SpawnPointGetPropertyExistsByHash )( SpawnPoint* spawnPoint, uint32_t hash );
	MM_Vec2            ( *SpawnPointSpawnPointTransformPos )( MM_Vec2 pos ); // transform a position from raw level format
	MM_Vec2            ( *SpawnPointSpawnPointInvTransformPos )( MM_Vec2 pos ); // transform a position to raw level format

	// set the contents of a file programmatically, this will only take effect after all existing references to the file are unloaded, and then new copies are loaded
	// the buffer passed to this must be allocated with Alloc()
	// calling this during MinaMod_Init is effectively the same as placing files in the mod's data directory
	void( *SetDataFile )( const char* path, const void* buf, size_t len );

	// GameAnim
	float            ( *GameAnimGetCurrentFrameTime )( ycComponent* anim ); // time into current frame
	void             ( *GameAnimAddFrameTime )( ycComponent* anim, float seconds ); // adds time to the current frame's time
	void             ( *GameAnimSetFrameTime )( ycComponent* anim, float seconds ); // overwrites the current frame's time, but only this once (does not affect later plays of this frame)
	uint32_t         ( *GameAnimGetNumLoopsPlayed )( ycComponent* anim );
	void             ( *GameAnimSetVisible )( ycComponent* anim, bool visible );
	bool             ( *GameAnimIsVisible )( ycComponent* anim );
	void             ( *GameAnimSetMulColor )( ycComponent* anim, MM_Color color );
	void             ( *GameAnimGetMulColor )( ycComponent* anim, MM_Color* outColor );
	void             ( *GameAnimGetWorldTransform )( ycComponent* anim, MM_Transform* outTransform );
	void             ( *GameAnimSetLocalTransform )( ycComponent* anim, const MM_Transform* transform );
	void             ( *GameAnimGetLocalTransform )( ycComponent* anim, MM_Transform* outTransform );
	void             ( *GameAnimSetLocalPosition )( ycComponent* anim, MM_Vec3 pos );
	void             ( *GameAnimGetLocalPosition )( ycComponent* anim, MM_Vec3* outPos );
	void             ( *GameAnimSetLocalScale )( ycComponent* anim, MM_Vec3 scale );
	void             ( *GameAnimGetLocalScale )( ycComponent* anim, MM_Vec3* outScale );
	void             ( *GameAnimSetLocalRotation )( ycComponent* anim, float rot );
	float            ( *GameAnimGetLocalRotation )( ycComponent* anim );
	uint32_t         ( *GameAnimLookAheadSeqFrameIdx )( ycComponent* anim, float elapsedTime ); // simulate the sequence for the elapsed time and return what the current frame would be
	void             ( *GameAnimSetSeqFrameIdx )( ycComponent* anim, uint32_t seqFrameIdx ); // frame of the current sequence to display
	uint32_t         ( *GameAnimGetNumSeqFrames )( ycComponent* anim ); // number of frames in the current sequence, 0 if no sequence is set
	void             ( *GameAnimSetPlayRate )( ycComponent* anim, float playRate );
	float            ( *GameAnimGetPlayRate )( ycComponent* anim );
	bool             ( *GameAnimGetPropertyExists )( ycComponent* anim, const char* name );
	bool             ( *GameAnimGetPropertyBool )( ycComponent* anim, const char* name );
	const char*      ( *GameAnimGetPropertyString )( ycComponent* anim, const char* name, const char* defaultValue ); // defaultValue will be returned if no property exists
	int32_t          ( *GameAnimGetPropertyInt )( ycComponent* anim, const char* name, int32_t defaultValue ); // defaultValue will be returned if no property exists
	float            ( *GameAnimGetPropertyFloat )( ycComponent* anim, const char* name, float defaultValue ); // defaultValue will be returned if no property exists
	void             ( *GameAnimGetPropertyPoint )( ycComponent* anim, const char* name, MM_Vec2* outPos);
	void             ( *GameAnimGetPropertyAnchor )( ycComponent* anim, const char* name, MM_Vec2* outPos, float* outAngle );
	void             ( *GameAnimGetPropertyRect )( ycComponent* anim, const char* name, MM_AABB* outValue );
	void             ( *GameAnimGetPropertyCircle )( ycComponent* anim, const char* name, MM_Circle* outValue );
	void             ( *GameAnimGetCurrentFrameBound )( ycComponent* anim, MM_AABB* outValue ); // the bounding box of the underlying raw frame
	ycPaletteTexture*( *GameAnimGetPalette )( ycComponent* anim );
	void             ( *GameAnimSetPalette )( ycComponent* anim, ycPaletteTexture* pal ); // palettes are reference counted, this adds a reference
	void             ( *GameAnimSetPaletteFile )( ycComponent* anim, const char* filename );

	// ycPaletteTexture
	ycPaletteTexture*( *CreatePalette )( const char* filename );
	ycPaletteTexture*( *ClonePalette )( ycPaletteTexture* pal );
	void             ( *ReleasePalette )( ycPaletteTexture* pal ); // palettes are reference counted
	int32_t          ( *PaletteGetIndex )( ycPaletteTexture* pal, MM_Color localColor );
	void             ( *PaletteWrite )( ycPaletteTexture* pal, const MM_Color* colors, int32_t offset, int32_t count );
	void             ( *PaletteWriteIndex )( ycPaletteTexture* pal, int32_t index, MM_Color color );
	void             ( *PaletteSetWidth )( ycPaletteTexture* pal, int32_t width );
	uint32_t         ( *PaletteGetWidth )( ycPaletteTexture* pal );
	void             ( *PaletteGetLocalColor )( ycPaletteTexture* pal, int32_t index, MM_Color* colorOut ); // local palette only
	void             ( *PaletteGetGlobalColor )( ycPaletteTexture* pal, int32_t index, MM_Color* colorOut ); // takes group palettes into account
	void             ( *PaletteSetGroup )( ycPaletteTexture* pal, int32_t group ); // -1 is 'no group'
	int32_t          ( *PaletteGetGroup )( ycPaletteTexture* pal );
	ycPaletteTexture*( *PaletteGetGroupPal )( ycPaletteTexture* pal );

	// ycCamera and GameCamera
	/* GameCamera is a ycCamera, functions that take a ycCamera will work on a GameCamera, but the reverse is not true */
	ycCamera*    ( *RenderPassGetCamera )( ycRenderPass* renderPass );
	GameCamera*  ( *WorldGetGameCamera )( World* world );

	const MM_Mtx*( *CameraGetProj )( ycCamera* camera );
	void         ( *CameraSetProj )( ycCamera* camera, const MM_Mtx* proj );
	const MM_Mtx*( *CameraGetView )( ycCamera* camera );
	void         ( *CameraSetView )( ycCamera* camera, const MM_Mtx* view );
	bool         ( *CameraIsOrtho )( ycCamera* camera );
	const MM_Mtx*( *CameraGetViewToWorld )( ycCamera* camera ); // inverse view
	const MM_Mtx*( *CameraGetProjToView )( ycCamera* camera ); // inverse proj
	void         ( *CameraGetEyePos )( ycCamera* camera, MM_Vec3* outPos );
	void         ( *CameraGetLookDir )( ycCamera* camera, MM_Vec3* outDir );

	void         ( *GameCameraScreenToWorld )( GameCamera* gameCamera, MM_Vec2 screen, MM_Vec2* outPos );
	void         ( *GameCameraWorldToScreen )( GameCamera* gameCamera, MM_Vec3 world, MM_Vec2* outPos );
	bool         ( *GameCameraIsOnScreenPoint )( GameCamera* gameCamera, MM_AABB target );
	bool         ( *GameCameraIsOnScreenRect )( GameCamera* gameCamera, MM_Vec3 center, MM_Vec3 extents );
	bool         ( *GameCameraIsTracking )( GameCamera* gameCamera );
	void         ( *GameCameraEnableTracking )( GameCamera* gameCamera, bool enable );
	void         ( *GameCameraSetLocalBound )( GameCamera* gameCamera, MM_AABB bound );
	void         ( *GameCameraGetLocalBound )( GameCamera* gameCamera, MM_AABB* outValue );
	void         ( *GameCameraGetLocalBoundByIndex )( GameCamera* gameCamera, uint32_t roomIndex, MM_AABB* outValue );
	void         ( *GameCameraSetLocalBoundActive )( GameCamera* gameCamera, bool active );
	bool         ( *GameCameraIsLocalBoundActive )( GameCamera* gameCamera );
	void         ( *GameCameraSetIgnoreBounds )( GameCamera* gameCamera, bool ignore );
	bool         ( *GameCameraIsIgnoringBound )( GameCamera* gameCamera );
	bool         ( *GameCameraIsPointInLocalBound )( GameCamera* gameCamera, MM_Vec3 pos );
	bool         ( *GameCameraIsPointInAnyBound )( GameCamera* gameCamera, MM_Vec3 pos );
	bool         ( *GameCameraIsBoxInLocalBound )( GameCamera* gameCamera, MM_AABB box );

	// mouse
	void( *MouseGetPos )( MM_Vec2* outPos ); // returns value in a space where the top left is (-1,1) and the bottom right is (1,-1)
	void( *MouseGetPosPixels )( MM_Vec2* outPos ); // top left is (0,0) and the bottom right is whatever the window resolution is
	void( *MouseGetPosGameCameraScreen )( GameCamera* gameCamera, MM_Vec2* screenPos ); // convert a value from MouseGetPos to the coordinate space expected by GameCameraScreenToWorld
	bool( *MouseIsCursorVisible )();
	void( *MouseSetCursorVisible )( bool visible );

	// world
	float( *WorldGetTimeScale )( World* world );
	float( *WorldGetElapsedTime )( World* world ); // elapsed time taking time scale into account

	// ycTextComponent
	void         ( *TextComponentSetText )( ycComponent* textComponent, const char* const text );
	const char*  ( *TextComponentGetText )( ycComponent* textComponent );
	void         ( *TextComponentSetColor )( ycComponent* textComponent, MM_Color color );
	void         ( *TextComponentGetColor )( ycComponent* textComponent, MM_Color* color );
	float        ( *TextComponentGetWidth )( ycComponent* textComponent );
	float        ( *TextComponentGetHeight )( ycComponent* textComponent );
	void         ( *TextComponentSetVisible )( ycComponent* textComponent, bool visible );
	bool         ( *TextComponentIsVisible )( ycComponent* textComponent );
	void         ( *TextComponentSetRenderPass )( ycComponent* textComponent, ycRenderPass* renderPass );
	ycRenderPass*( *TextComponentGetRenderPass )( ycComponent* textComponent );
	uint32_t     ( *TextComponentGetTotalLineCount )( ycComponent* textComponent );
	void         ( *TextComponentSetLocalTransform )( ycComponent* textComponent, const MM_Transform* transform );
	void         ( *TextComponentGetLocalTransform )( ycComponent* textComponent, MM_Transform* transform );
	void         ( *TextComponentSetLocalPosition )( ycComponent* textComponent, const MM_Vec3* pos );
	void         ( *TextComponentGetLocalPosition )( ycComponent* textComponent, MM_Vec3* pos );
	void         ( *TextComponentGetBounds )( ycComponent* textComponent, MM_AABB* bounds );

	// misc
	void             ( *PlayerUpdateStats )(); // this is usually automatically called by things like PlayerSetHealthUpgrade, PlayerSetStat, PlayerSetTrinketMax, PlayerSetTrinketCollected
	bool             ( *WaterListenerIsInDeepWater )( WaterListener* waterListener, bool ignoreEnabled );
	void             ( *PhysicsComponentGetAABB )( PhysicsComponent* physicsComponent, MM_AABB* aabb, bool local, uint32_t shapeFlags );
	CarryableObject* ( *CarryManagerGetClosestCarryableObject )( CarryManager* carryManager, MM_AABB box, int32_t collisionLayer, float maxDist, int32_t* dstOverlappingObjectCount, uint64_t collideMaskIgnore );
	void             ( *ItemsSetItemCollected )( int32_t index, bool collected, ItemCollection* collection, SaveSlot* slot  );
	bool             ( *ItemsIsItemCollected )( int32_t index, ItemCollection* collection, SaveSlot* slot, bool includePawnShop, bool includeEarlyCollected );
	void             ( *GetScreenResolution )( uint32_t* width, uint32_t* height );
	const char*      ( *GetCurrentModPath )(); // gets the path to the mod's install folder, only valid during Mod_Init -- save it if you'll need it later!
	uint32_t         ( *GetModVersion )( const char* name ); // returns uint32_t(-1) if the mod is not loaded

	// menu
	PagedMenu*               ( *CreatePagedMenu )( ycEntity* parent, OptionsMenu* container, const char* titleRowID, const char* iconSeq );
	void                     ( *PagedMenuCreateDisplay )( PagedMenu* pagedMenu );
	void                     ( *PagedMenuAddControl )( PagedMenu* pagedMenu, ycUpdateQueue* updateQueue, void* page, OptionsMenuControl* control );
	void                     ( *PagedMenuActivate )( PagedMenu* pagedMenu, ycUpdateQueue* updateQueue );
	OptionsMenuControl*      ( *CreateOptionsMenuControl )( ycEntity* parent, const char* labelName );
	OptionsMenuControlSlider*( *CreateOptionsMenuControlSlider )( ycEntity* parent, const char* labelName, uint32_t maxValue, uint32_t defaultValue, uint32_t initialValue );

	// entity
	void                     ( *EntityDockComponent )( ycEntity* parent, ycComponent* child, uint32_t flags );
	void                     ( *EntityDockEntity )( ycEntity* parent, ycEntity* child, uint32_t flags );
	void                     ( *EntityReparentEntity )( ycEntity* newParent, ycEntity* child, uint32_t flags );

	// world
	void                     ( *WorldQueueDestroyEntity )( World* world, ycEntity* entity, const bool depthFirst );
	void                     ( *WorldQueueDestroyComponent )( World* world, ycComponent* component, const bool depthFirst );
	/*
	Global,                   JugFire,                  FireTile, // global is only used under special circumstances
	BrambleTile,              BramblePlant,             ShortcutPipe,
	WaterValve,               AnimTile,                 WeaponMerchantAnimTile,
	MirrorWarpAnimTile,       HealingWater,             BurrowWall,
	Weather,                  Vent,                     WarpDoor,
	WebTile,                  SpiritEnemy,              Statue,
	StatueHead,               MoneyNumber,              AgroArea,
	ShockTrooper,             EmptyGrave,               LightningRod,
	SplitEnemy,               MagicNumber,              PressurePlate,
	ArrowTrap,                DuchessBossTentacle,      DuchessBossThrone,
	DukeNPC,                  GeyserHole,               PumpkinHandsEnemy,
	KeyBlockChain,            KeyBlock,                 NPCPasserbyRect,
	NPCPasserby,              MirrorRect,               Necromancer,
	EggSac,                   Puffer,                   LeafPile,
	SpringBellows,            PumpkinHandsHintArea,     JumpDownArea,
	JumpDownPushoutArea,      AxeBlocker,               FishRaiser,
	ShallowWaterArea,         LadderBlocker,            BoneDustTile,
	OldManWaterBearNPC,       BrainBossEye,             BrainBossGroundTear,
	BrainBossCrusher,         BrainBossSnake,           SkullkerIceSpike,
	GrindRail,                GrindRailJunction,        EndlessSpawnZone,
	MinerBossFractalTile,     RespawnMarkerArea,        GlassFlipper,
	Minion,                   AbductedMinion,           AbductedElectricNode,
	AbductedProj,             AbductedNPC,              RainbowPlatform,
	SpawnRangeArea,           WanderBox,                DarknessArea,
	FogThrowerProjectile,     TowerAttachmentDevice,    TowerCog,
	TowerBarrier,             AreaMarker,               PitMarker,
	SpecialCollision,         RoomSaveMarker,           IceBlock,
	DakAckProj,               Rope,                     MaidNPC,
	NPC,                      BurrowCheckpoint,         BarrierParasol,
	ButlerFurfball,           LavaTrenchTile,           WeaponsmithProj,
	Bomb,                     FloatingVirusCloud,       Breakable,
	BardProj,                 BayouBandMember,          EvraSkeleton,
	EvraOrb,                  ThorneMine,               ThorneMissile,
	MothBossProj,             Fountain,                 BlackHolePit,
	BrainlessBrain,           Kite,                     GhostReflection,
	PhaseChangerFlame,        DinnerChair,              CatGhost,
	DinnerCutscene,           TrainConductor,           TrainManager,
	TrainAuthority,           TrainAnim,                LionelNPC,
	ElectricFloorEffect,      TailorCurtain,            SidearmSaver,
	Wrecker,                  RingMasterNPC,            MinigameRing,
	BossRing,                 Interact,                 BouncePlant,
	FireWall,                 SineKnife,                SecretPFDirt,
	BossGate,                 LightningProj,            Huntsman,
	Boat,                     GigaThorneNPC,            GigaLionelArm,
	CampfireKid,              JugLobber,                Paladin,
	MothNPC,                  BossArea,                 RushPlatform,
	BoneBeachMonsterLayer,    Fish,                     FishShadow,
	CrackIce,                 CrackIceLight,            FishingProj,
	FishingRaft,              Pickup,                   Steam,
	KickCan,                  CameraAutoScroll,         NewspaperStand,
	VialDecoy,                TowerKillLine,            TrooperMine,
	BasementSecret,           CreditsLionelBoat,        TimedSwitchOre,
	RainbowPlatformStatic,    Mandrake,                 BossFodder,
	Ooze,                     Abducted,                 MovingLayer,
	FishAreaInfo,             FishBossProj,             TrainingDummy,
	GigaLionelAbsorbParticle, CalciumHoleAnimTile,      Merman,
	ShadowElevator,           PlanetHazard,             BigFrogBubble,
	JugBottle,                Spark,                    SparkDoor,
	WeatherEffect,
	*/
	size_t        ( *WorldGetEntityList )( World* world, const char* list, GameComponent** gameComponents, size_t bufElemCount ); // always returns the total count even if the buffer is not large enough; pass null/0 to just get the count
	void          ( *WorldEnableEntityUpdate )( World* world, bool enable );
	bool          ( *WorldIsEntityUpdateEnabled )( World* world );
	GameComponent*( *WorldGetEntityBySpawnPoint )( World* world, const MM_StringRef* name );

	// cheat manager
	void( *CheatManagerSetCheatApplied )( int32_t cheat, bool active, uint32_t saveSlot ); // pass saveSlot=uint32_t(-1) to use the active save slot
	bool( *CheatManagerIsCheatApplied )( int32_t cheat, uint32_t saveSlot );
	void( *CheatManagerActivateSaveCheats )();

	// compression/encoding
	uint32_t( *wfLZ_GetMaxCompressedSize )( const uint32_t inSize );
	uint32_t( *wfLZ_GetWorkMemSize )();
	uint32_t( *wfLZ_CompressFast )( const uint8_t* const in, const uint32_t inSize, uint8_t* const out, const uint8_t* workMem, const uint32_t swapEndian );
	uint32_t( *wfLZ_GetDecompressedSize )( const uint8_t* const in );
	uint32_t( *wfLZ_GetCompressedSize )( const uint8_t* const in );
	void    ( *wfLZ_Decompress )( const uint8_t* const in, uint8_t* const out );
	uint64_t( *Base64CalcDecodedSize )( MM_StringRef v );
	void    ( *Base64Decode )( uint8_t* dst, uint64_t dstSize, MM_StringRef str );
	uint64_t( *Base64CalcEncodedSize )( uint64_t inSize );
	void    ( *Base64Encode )( const uint8_t* src, uint64_t srcSize, char* dst, uint64_t dstSize );

	// raw access to internal structures and data, it's possible that these may change in a patch
	// the underlying ABI is _not stable_, use at your own risk
	/*
	g_defaultMem,               kTrinketNames,              s_rItems,
	s_rItemCollection,          s_rWarpData,                g_cheatManager,
	s_rShopDef,                 Mina::OnBurrowJump,         SessionManager::ActivateSaveSlot
	Pickup::Init,               ShopMenu::InitState,        HubFountain::Bulb::Update,
	Player::SetBurrowGround,    Player::RopeClimbStart,     LevelUpMenu::Update,
	BouncePlant::CollideWith,   BouncePlant::BounceLaunch,  SpringBellows::CollideWith,
	TrainAuthority::OnNPCEvent, Shop::IsOutOfStock,         ShopMenu::SetCursor,
	PawnShopNPC::OnNPCEvent,    CheatManager::ToggleCheat,  CheatManager::SetCheatApplied,
	Shop::Get,                  Player::PickUpAnyNearbyCarryableObject,
	*/
	void*( *GetSymAddr )( const char* name );
};
