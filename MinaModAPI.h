#pragma once

#include <stdint.h>
#include <stddef.h> // size_t
#ifndef __cplusplus
	#include <stdbool.h> // c bool
#endif

#include "MinaModTypes.h"

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
	they _cannot be run from inside MinaModRenderFunc_.
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
	struct MinaModRenderObject*( *CreateRenderObject )( MM_CLASS ycRenderPass* renderPass, MinaModRenderFunc renderFunc, void* userData );
	void( *DestroyRenderObject )( struct MinaModRenderObject* renderObject );
	const union MM_Mtx*( *GetRenderObjectTransform )( struct MinaModRenderObject* renderObject );
	void( *SetRenderObjectTransform )( struct MinaModRenderObject* renderObject, const union MM_Mtx* transform ); // transform should be modified from update, not MinaModRenderFunc

	void( *RenderDrawCallSetIndexBuffer )( struct ycRenderDrawCall* dc, MM_CLASS ycGpuBuffer* ib );
	void( *RenderDrawCallSetVertexBuffer )( struct ycRenderDrawCall* dc, MM_CLASS ycGpuBuffer* vb );
	void( *RenderDrawCallSetTexture )( struct ycRenderDrawCall* dc, MM_CLASS ycTexture* tex );
	
	void( *RenderCmdDraw )( MM_CLASS ycRenderCmdList* cmds, struct ycRenderDrawCall* dc, uint32_t vertexCount, uint32_t startVertex );
	void( *RenderCmdDrawIndexed )( MM_CLASS ycRenderCmdList* cmds, struct ycRenderDrawCall* dc, uint32_t indexCount, uint32_t startIndex );

	// debug draw functions should be used from the game update, not from MinaModRenderFunc
	/* valid debug draw names:
		World
		Hud
		WorldPersist
		EngineHUD
	*/
	MM_CLASS ycDrawUtil*( *GetDebugDraw )( const char* name );
	void( *DebugDrawRect )( MM_CLASS ycDrawUtil* dd, struct MM_Vec3 center, float w, float h, struct MM_Color color, bool disableDepthTest );
	void( *DebugDrawRectSolid )( MM_CLASS ycDrawUtil* dd, struct MM_Vec3 center, float w, float h, struct MM_Color color, bool disableDepthTest );
	void( *DebugDrawLine )( MM_CLASS ycDrawUtil* dd, struct MM_Vec3 p1, struct MM_Vec3 p2, struct MM_Color color, bool disableDepthTest );
	void( *DebugDrawTexturedQuad )( MM_CLASS ycDrawUtil* dd, MM_CLASS ycTexture* tex, struct MM_Vec3 center, float w, float h, struct MM_Color mulColor, bool disableDepthTest );

	// entities & components

	MM_CLASS GameComponent* ( *SpawnEntity2 )( MM_CLASS ycEntity* parent, uint32_t entityType, struct MM_Vec3 pos, struct MM_Vec3 scale, float rot, int32_t collisionLayer, MM_CLASS SpawnPoint* spawnPoint, void*, void* ); // set last two parameters to nullptr

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
	void( *GameAnimInit )( MM_CLASS ycComponent* anim, const char* filename, void* ); // set third argument to null
	void( *GameAnimPlayDir )( MM_CLASS ycComponent* anim, const char* seqName, int32_t loops, float speed, bool forceRestart );
	void( *GameAnimPlay )( MM_CLASS ycComponent* anim, const char* seqName, int32_t loops, float speed, bool forceRestart );
	bool( *GameAnimIsPaused )( MM_CLASS ycComponent* anim );
	void( *GameAnimSetPaused )( MM_CLASS ycComponent* anim, bool paused );
	bool( *GameAnimIsDone )( MM_CLASS ycComponent* anim );
	bool( *GameAnimIsNewFrame )( MM_CLASS ycComponent* anim );
	uint32_t( *GameAnimGetSeqFrameIdx )( MM_CLASS ycComponent* anim );
	struct MM_StringRef( *GameAnimGetSeqName )( MM_CLASS ycComponent* anim );
	struct MM_StringRef( *GameAnimGetSeqNameNoDir )( MM_CLASS ycComponent* anim );

	// update queues
	MM_CLASS ycUpdateQueue*( *WorldGetPlayerUpdateQueue )( MM_CLASS World* world );
	MM_CLASS ycUpdateQueue*( *WorldGetEntityUpdateQueue )( MM_CLASS World* world );
	MM_CLASS ycUpdateQueue*( *WorldGetEntityHitUpdateQueue )( MM_CLASS World* world );
	MM_CLASS ycUpdateQueue*( *WorldGetSystemPreUpdateQueue )( MM_CLASS World* world );
	MM_CLASS ycUpdateQueue*( *WorldGetSystemPostUpdateQueue )( MM_CLASS World* world );
	MM_CLASS ycUpdateQueue*( *WorldGetEntityPostUpdateQueue )( MM_CLASS World* world );
	MM_CLASS ycUpdateQueue*( *WorldGetEntityPostArtUpdateQueue )( MM_CLASS World* world );
	MM_CLASS ycUpdateQueue*( *WorldGetEntityPreUpdateQueue )( MM_CLASS World* world );
	MM_CLASS ycUpdateQueue*( *WorldGetPostSimUpdateQueue )( MM_CLASS World* world );
	MM_CLASS ycUpdateQueue*( *WorldGetHUDUpdateQueue )( MM_CLASS World* world );
	MM_CLASS ycUpdateQueue*( *WorldGetPauseUpdateQueue )( MM_CLASS World* world );
	MM_CLASS ycUpdateQueue*( *WorldGetPauseCheckUpdateQueue )( MM_CLASS World* world );
	MM_CLASS ycUpdateQueue*( *GameGetWorldUpdateQueue )(); // the game's update queue of worlds
	void*( *UpdateQueueAdd )( MM_CLASS ycUpdateQueue* updateQueue, MinaModUpdateQueueCallback cb, void* userData ); // returns a handle to be used with UpdateQueueRemove
	void( *UpdateQueueRemove )( void* handle );

	// pause
	void( *WorldPause )( MM_CLASS World* world, bool menu );
	void( *WorldResume )( MM_CLASS World* world );
	bool( *WorldIsPaused )( MM_CLASS World* world );
	bool( *WorldIsPauseAllowed )( MM_CLASS World* world );
	void( *WorldSetPauseAllowed )( MM_CLASS World* world, bool enable );

	// weak pointers / safe references
	struct MM_WeakPtr*( *CreateWeakPtr )( void* componentOrEntity );
	void( *DestroyWeakPtr )( struct MM_WeakPtr* weakPtr );
	void*( *WeakPtrGet )( struct MM_WeakPtr* weakPtr );

	// debug draw
	void( *DebugDrawTexturedQuadUV )( MM_CLASS ycDrawUtil* dd, MM_CLASS ycTexture* tex, struct MM_Vec3 center, struct MM_Vec2 size, struct MM_Vec2 uvCenter, struct MM_Vec2 uvSize, struct MM_Color mulColor, bool disableDepthTest );
	// to use the text functionality, a mod must load a debugdraw.font.yc file
	MM_Vec3( *DebugDrawText )( MM_CLASS ycDrawUtil* dd, const char* text, struct MM_Color color, struct MM_Vec3 pos, float fontSize ); // returns dimensions of the text
	MM_Vec3( *DebugDrawTextAlign )( MM_CLASS ycDrawUtil* dd, const char* text, struct MM_Color color, struct MM_Vec3 pos, uint64_t align, struct MM_Vec2 dimensions, float fontSize );

	// file access
	MM_CLASS ycFileRefBase*( *CreateFileRef )( const char* name ); // this does not block, it will return immediately
	void( *DestroyFileRef )( MM_CLASS ycFileRefBase* fileRef );
	bool( *FileRefWaitForLoaded )( MM_CLASS ycFileRefBase* fileRef ); // blocks until the file is loaded or an error occurs, returns true if the file was loaded
	const uint8_t*( *FileRefGetData )( MM_CLASS ycFileRefBase* fileRef );
	size_t( *FileRefGetSize )( MM_CLASS ycFileRefBase* fileRef );

	// player
	struct MM_Vec3( *PlayerGetPos3 )();
	void ( *PlayerSetPos3 )( struct MM_Vec3 pos );
	MM_CLASS World*( *PlayerGetWorld )();
	MM_CLASS WorldRegion*( *PlayerGetWorldRegion )();

	// GameComponent
	MM_CLASS World*( *GameComponentGetWorld )( MM_CLASS GameComponent* component );
	MM_CLASS WorldRegion*( *GameComponentGetWorldRegion )( MM_CLASS GameComponent* component );

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
	uint8_t( *TileLevelEntityGetSpawnType )( const char* name ); // returns 0xff if no valid value is found
	struct ycTileLevel2Entity*( *CreateTileLevelEntity )( const char* ycdata ); // returned pointer should be freed with DestroyTileLevelEntity
	void( *DestroyTileLevelEntity )( struct ycTileLevel2Entity* tileLevelEntity );
	char*( *SpawnPointGetTileLevelEntity )( MM_CLASS SpawnPoint* spawnPoint ); // returned string should be freed with Free()
	MM_CLASS SpawnPoint*( *GameComponentGetSpawnPoint )( MM_CLASS GameComponent* component );
	MM_CLASS SpawnManager*( *WorldRegionGetSpawnManager )( MM_CLASS WorldRegion* worldRegion );
	MM_CLASS SpawnPoint*( *SpawnManagerCreateSpawnPoint )( MM_CLASS SpawnManager* spawnManager, MM_CLASS WorldRegion* worldRegion, struct MM_Vec3 pos, struct MM_Vec3 scale, float rot, uint32_t entityType, uint8_t spawnType, uint8_t tileLayerIndex, int32_t collisionLayerIndex );
	MM_CLASS SpawnPoint*( *SpawnManagerCreateSpawnPoint2 )( MM_CLASS SpawnManager* spawnManager, MM_CLASS WorldRegion* worldRegion, const struct ycTileLevel2Entity* tileLevelEntity );
	void( *SpawnManagerDestroySpawnPoint )( MM_CLASS SpawnManager* spawnManager, MM_CLASS SpawnPoint* spawnPoint );
	MM_CLASS SpawnPoint*( *SpawnManagerGetSpawnPointByName )( MM_CLASS SpawnManager* spawnManager, const char* name );
	MM_CLASS SpawnPoint*( *SpawnManagerGetSpawnPointByNameHash )( MM_CLASS SpawnManager* spawnManager, uint32_t nameHash );
	MM_CLASS SpawnPoint*( *SpawnManagerGetSpawnPointByTileLevelEntity )( MM_CLASS SpawnManager* spawnManager, const ycTileLevel2Entity* tileLevelEntity );
	MM_CLASS SpawnPoint*( *SpawnManagerGetSpawnPointByNameLevelHash )( MM_CLASS SpawnManager* spawnManager, uint64_t nameLevelHash );
	uint8_t( *SpawnPointGetTileLayerIndex )( MM_CLASS SpawnPoint* spawnPoint );
	bool( *SpawnPointIsPersistent )( MM_CLASS SpawnPoint* spawnPoint );
	bool( *SpawnPointIsEntitySpawned )( MM_CLASS SpawnPoint* spawnPoint );
	bool( *SpawnPointIsAwaitingSpawn )( MM_CLASS SpawnPoint* spawnPoint );
	bool( *SpawnPointIsEntityCulled )( MM_CLASS SpawnPoint* spawnPoint );
	bool( *SpawnPointIsEntityKilled )( MM_CLASS SpawnPoint* spawnPoint );
	bool( *IsEntityPermanentKilled )( MM_CLASS SpawnPoint* spawnPoint, bool checkSecretDirt );
	bool( *SpawnPointIsEntityPermanentKilledType )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointReset )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointResetPosToStart )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointResetAll )( MM_CLASS SpawnPoint* spawnPoint );
	bool( *SpawnPointIsDisabled )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointDisable )( MM_CLASS SpawnPoint* spawnPoint ); // call Reset() to return to AwaitingSpawn
	void( *SpawnPointSetSpawnType )( MM_CLASS SpawnPoint* spawnPoint, uint8_t spawnType );
	uint8_t( *SpawnPointGetSpawnType )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointDisownParent )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointSetupParentSpawnPoint )( MM_CLASS SpawnPoint* spawnPoint, MM_CLASS SpawnPoint* parent ); // same as calling SetParent + SetChild, and also saves the starting position
	void( *SpawnPointSetParentSpawnPoint )( MM_CLASS SpawnPoint* spawnPoint, MM_CLASS SpawnPoint* parent );
	void( *SpawnPointSetChildSpawnPoint )( MM_CLASS SpawnPoint* spawnPoint, MM_CLASS SpawnPoint* child );
	bool( *SpawnPointHasChildSpawnPoint )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointSetChildSpawnEnabled )( MM_CLASS SpawnPoint* spawnPoint, bool enabled );
	bool( *SpawnPointIsChildSpawnEnabled )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointSetForceChildSpawn )( MM_CLASS SpawnPoint* spawnPoint, bool force );
	bool( *SpawnPointIsForceChildSpawn )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointSetForceChildOffset )( MM_CLASS SpawnPoint* spawnPoint, bool force );
	bool( *SpawnPointIsForceChildOffset )( MM_CLASS SpawnPoint* spawnPoint );
	MM_CLASS SpawnPoint*( *SpawnPointGetParent )( MM_CLASS SpawnPoint* spawnPoint );
	MM_CLASS SpawnPoint*( *SpawnPointGetChild )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointSetChildOffset )( MM_CLASS SpawnPoint* spawnPoint, struct MM_Vec3 offset );
	struct MM_Vec3( *SpawnPointGetChildOffset )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointSetChildSpawnDir )( MM_CLASS SpawnPoint* spawnPoint, struct MM_Vec3 dir );
	struct MM_Vec3( *SpawnPointGetChildSpawnDir )( MM_CLASS SpawnPoint* spawnPoint );
	uint32_t( *SpawnPointGetEntityType )( MM_CLASS SpawnPoint* spawnPoint );
	uint32_t( *SpawnPointGetNameHash )( MM_CLASS SpawnPoint* spawnPoint );
	uint64_t( *SpawnPointGetNameLevelHash )( MM_CLASS SpawnPoint* spawnPoint );
	uint32_t( *SpawnPointGetLayerNameHash )( MM_CLASS SpawnPoint* spawnPoint );
	struct MM_AABB( *SpawnPointGetArea )( MM_CLASS SpawnPoint* spawnPoint );
	int32_t( *SpawnPointGetCollisionLayer )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointSetCollisionLayer )( MM_CLASS SpawnPoint* spawnPoint, uint32_t idx );
	struct MM_Vec3( *SpawnPointGetPos )( MM_CLASS SpawnPoint* spawnPoint );
	struct MM_Vec3( *SpawnPointGetPosStart )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointSetPos )( MM_CLASS SpawnPoint* spawnPoint, struct MM_Vec3 pos );
	struct MM_Vec3( *SpawnPointGetScale )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointSetScale )( MM_CLASS SpawnPoint* spawnPoint, struct MM_Vec3 scale );
	float( *SpawnPointGetRotation )( MM_CLASS SpawnPoint* spawnPoint );
	void( *SpawnPointSetRotation )( MM_CLASS SpawnPoint* spawnPoint, float rot );
	void( *SpawnPointSetSpawnedEntity )( MM_CLASS SpawnPoint* spawnPoint, MM_CLASS GameComponent* entity );
	MM_CLASS GameComponent*( *SpawnPointGetSpawnedEntity )( MM_CLASS SpawnPoint* spawnPoint );
	struct MM_StringRef( *SpawnPointGetProperty )( MM_CLASS SpawnPoint* spawnPoint, const char* name, struct MM_StringRef defaultValue );
	struct MM_StringRef( *SpawnPointGetPropertyByHash )( MM_CLASS SpawnPoint* spawnPoint, uint32_t hash, struct MM_StringRef defaultValue );
	bool( *SpawnPointGetPropertyBool )( MM_CLASS SpawnPoint* spawnPoint, const char* propName, bool defaultValue );
	float( *SpawnPointGetPropertyFloat )( MM_CLASS SpawnPoint* spawnPoint, const char* propName, float defaultValue );
	int32_t( *SpawnPointGetPropertyInt )( MM_CLASS SpawnPoint* spawnPoint, const char* propName, int32_t defaultValue );
	bool( *SpawnPointGetPropertyExists )( MM_CLASS SpawnPoint* spawnPoint, const char* propName );
	bool( *SpawnPointGetPropertyExistsByHash )( MM_CLASS SpawnPoint* spawnPoint, uint32_t hash );
	struct MM_Vec2( *SpawnPointSpawnPointTransformPos )( struct MM_Vec2 pos ); // transform a position from raw level format
	struct MM_Vec2( *SpawnPointSpawnPointInvTransformPos )( struct MM_Vec2 pos ); // transform a position to raw level format
};
