#pragma once

#include <stdint.h>
#include <stddef.h> // size_t
#ifndef __cplusplus
	#include <stdbool.h> // c bool
#endif

#include "MinaModTypes.h"

enum { MinaModAPI_Version = 1 };

typedef void( *MM_HookCallback )( void* pCtx );
typedef void( *MM_RenderFunc )( struct MM_RenderCtx* ctx );

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
	void( *SoundPlay )( const char* name );
	bool( *SoundIsPlaying )( const char* name );
	void( *SoundStop )( const char* name );
	void( *MusicPlay )( const char* name );
	void( *MusicStop )();
	bool( *MusicIsAnyPlaying )();
	bool( *MusicIsPlaying )( const char* name );

	//
	// rendering
	//

	/*
	render resource management functions must be run in the standard update,
	they _cannot be run from inside MM_RenderFunc_.
	*/
	MM_CLASS ycTexture*( *CreateTexture )( uint32_t width, uint32_t height ); // texture is MM_Color[width*height]
	void( *UpdateTexture )( MM_CLASS ycTexture* tex, const void* data );
	void( *DestroyTexture )( MM_CLASS ycTexture* tex );

	MM_CLASS ycGpuBuffer* ( *CreateIndexBuffer )( uint32_t count ); // index buffer data is uint32_t[count]
	MM_CLASS ycGpuBuffer* ( *CreateVertexBuffer )( uint32_t count );
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
	struct MinaModRenderObject*( *CreateRenderObject )( MM_CLASS ycRenderPass* renderPass, MM_RenderFunc renderFunc );
	void( *DestroyRenderObject )( struct MinaModRenderObject* renderObject );
	const union MM_Mtx*( *GetRenderObjectTransform )( struct MinaModRenderObject* renderObject );
	void( *SetRenderObjectTransform )( struct MinaModRenderObject* renderObject, const union MM_Mtx* transform ); // transform should be modified from update, not MM_RenderFunc

	void( *RenderDrawCallSetIndexBuffer )( struct ycRenderDrawCall* dc, MM_CLASS ycGpuBuffer* ib );
	void( *RenderDrawCallSetVertexBuffer )( struct ycRenderDrawCall* dc, MM_CLASS ycGpuBuffer* vb );
	void( *RenderDrawCallSetTexture )( struct ycRenderDrawCall* dc, MM_CLASS ycTexture* tex );
	
	void( *RenderCmdDraw )( MM_CLASS ycRenderCmdList* cmds, struct ycRenderDrawCall* dc, uint32_t vertexCount, uint32_t startVertex );
	void( *RenderCmdDrawIndexed )( MM_CLASS ycRenderCmdList* cmds, struct ycRenderDrawCall* dc, uint32_t indexCount, uint32_t startIndex );
};
