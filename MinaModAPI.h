#pragma once
#include <stdint.h>
#include <stddef.h> // size_t
#ifndef __cplusplus
	#include <stdbool.h> // c bool
#endif

enum { MinaModAPI_Version = 1 };

typedef void( *MM_VoidFP )();
typedef void( *MM_SetBoolFP )( bool );
typedef bool( *MM_GetBoolFP )();
typedef uint32_t( *MM_GetUIntFP )();
typedef void( *MM_SetUIntFP )( uint32_t );
typedef int32_t( *MM_GetIntFP )();
typedef void( *MM_SetIntFP )( int32_t );
typedef float( *MM_GetFloatFP )();
typedef void( *MM_SetFloatFP )( float );
typedef double( *MM_GetDoubleFP )();
typedef void( *MM_SetDoubleFP )( double );
typedef uint64_t( *MM_GetUInt64FP )();
typedef void( *MM_SetUInt64FP )( uint64_t );

typedef void*( *MM_AllocFP )( size_t );
typedef void( *MM_FreeFP )( void* );
typedef void( *MM_AssertFP )( bool condition, const char* msg, ... );
typedef void( *MM_LogFP )( const char* msg, ... );
typedef int32_t( *MM_GetActiveSaveSlotFP )();
typedef void( *MM_SetActiveSaveSlotFP )( uint32_t slot );
typedef bool( *MM_SetSaveSlotContentsFP )( uint32_t slot, const char* data );
typedef bool( *MM_SetActiveSaveSlotContentsFP )( const char* data );
typedef char*( *MM_GetActiveSaveSlotContentsFP )();
typedef void( *MM_PlayerGetPosFP )( float* x, float* y );
typedef void( *MM_PlayerSetPosFP )( float x, float y );
typedef void( *MM_PlayerSetKeyFoundFP )( uint32_t keyIdx, bool found );
typedef void( *MM_PlayerSetStatFP )( int32_t stat, int32_t level );
typedef int32_t( *MM_PlayerGetStatFP )( int32_t stat );
typedef void( *MM_PlayerSetWeaponLevelFP )( int32_t weaponIndex, int32_t level );
typedef int32_t( *MM_PlayerGetWeaponLevelFP )( int32_t weaponIndex );
typedef void( *MM_PlayerSetTrinketCollectedFP )( int32_t trinketIndex, bool found );
typedef bool( *MM_PlayerGetTrinketCollectedFP )( int32_t trinketIndex );
typedef bool( *MM_IsInputDownOrHeld )( uint32_t act_or_btn_or_key );

typedef void( *MM_HookCallback )( void* pCtx );
typedef void*( *MM_InstallHookFP )( const char* hookName, int32_t priority, MM_HookCallback hookCallback );
typedef void( *MM_RemoveHookFP )( void* pHookHandle );

struct MinaModAPI
{
	uintptr_t APIVersion;

	MM_InstallHookFP InstallHook;
	MM_RemoveHookFP RemoveHook;

	MM_LogFP Log;
	MM_AssertFP Assert;

	MM_AllocFP Alloc; // allocate and free memory using the game's memory manager
	MM_FreeFP Free;

	MM_SetBoolFP SetSaveWriteEnabled; // enable/disable save writing
	MM_GetBoolFP IsSaveWriteEnabled;
	MM_VoidFP ResetSave; // clear save data
	MM_VoidFP ResetSaveSlots;
	MM_GetActiveSaveSlotFP GetActiveSaveSlot; // get the current save slot index
	MM_SetActiveSaveSlotFP SetActiveSaveSlot; // load a save slot into the active slot
	MM_SetSaveSlotContentsFP SetSaveSlotContents; // set the contents of a save slot with ycData text
	MM_SetActiveSaveSlotContentsFP SetActiveSaveSlotContents; // set the contents of the currently active save slot with ycData text
	MM_GetActiveSaveSlotContentsFP GetActiveSaveSlotContents; // get the contents of the currently active save slot as ycData text; this must be Free'd using MinaModAPI::Free
	MM_GetDoubleFP GetActiveSaveSlotPlayTime; // query information about the current save slot's play time
	MM_GetDoubleFP GetActiveSaveSlotPlayTimeCleared;
	MM_GetDoubleFP GetActiveSaveSlotPlayTimeTotal;

	// player state
	MM_PlayerGetPosFP PlayerGetPos;
	MM_PlayerSetPosFP PlayerSetPos;
	MM_VoidFP PlayerDie;
	MM_SetIntFP PlayerSetJoules;
	MM_GetIntFP PlayerGetJoules;
	MM_SetIntFP PlayerSetJoulesMax;
	MM_SetFloatFP PlayerSetHealth;
	MM_GetFloatFP PlayerGetHealth;
	MM_SetIntFP PlayerSetHealthUpgrade;
	MM_SetUIntFP PlayerSetArmor;
	MM_SetFloatFP PlayerSetPlasma;
	MM_GetFloatFP PlayerGetPlasma;
	MM_SetIntFP PlayerSetVials;
	MM_GetIntFP PlayerGetVials;
	MM_SetIntFP PlayerSetMaxVials;
	MM_GetIntFP PlayerGetMaxVials;
	MM_SetIntFP PlayerSetWeapon_ItemType;
	MM_GetIntFP PlayerGetWeapon_ItemType;
	MM_SetIntFP PlayerSetWeapon_WeaponIndex;
	MM_GetIntFP PlayerGetWeapon_WeaponIndex;
	MM_SetIntFP PlayerSetSidearm;
	MM_GetIntFP PlayerGetSidearm;
	MM_SetIntFP PlayerSetSidearm2;
	MM_GetIntFP PlayerGetSidearm2;
	MM_SetUIntFP PlayerSetDonated;
	MM_GetUIntFP PlayerGetDonated;
	MM_SetIntFP PlayerSetBones;
	MM_GetIntFP PlayerGetBones;
	MM_SetIntFP PlayerSetBoneStone;
	MM_GetIntFP PlayerGetBoneStone;
	MM_SetIntFP PlayerSetKeys;
	MM_GetIntFP PlayerGetKeys;
	MM_PlayerSetKeyFoundFP PlayerSetKeyFound;
	MM_SetIntFP PlayerSetKeysSpent;
	MM_GetIntFP PlayerGetKeysSpent;
	MM_SetIntFP PlayerSetSpark;
	MM_GetIntFP PlayerGetSpark;
	MM_SetIntFP PlayerSetSparkMax;
	MM_GetIntFP PlayerGetSparkMax;
	MM_PlayerSetStatFP PlayerSetStat;
	MM_PlayerGetStatFP PlayerGetStat;
	MM_PlayerSetWeaponLevelFP PlayerSetWeaponLevel_ItemType;
	MM_PlayerGetWeaponLevelFP PlayerGetWeaponLevel_ItemType;
	MM_PlayerSetWeaponLevelFP PlayerSetWeaponLevel_WeaponIndex;
	MM_PlayerGetWeaponLevelFP PlayerGetWeaponLevel_WeaponIndex;
	MM_GetUIntFP PlayerGetUpgrades; // flags
	MM_SetUIntFP PlayerSetUpgrades;
	MM_GetUIntFP PlayerGetUpgradesSeen;
	MM_SetUIntFP PlayerSetUpgradesSeen;
	MM_SetUIntFP PlayerSetTrinketMax;
	MM_GetUIntFP PlayerGetTrinketMax;
	MM_PlayerSetTrinketCollectedFP PlayerSetTrinketCollected;
	MM_PlayerGetTrinketCollectedFP PlayerGetTrinketCollected;
	MM_SetUInt64FP PlayerSetBossesDefeated; // flags
	MM_GetUInt64FP PlayerGetBossesDefeated;

	// input
	MM_IsInputDownOrHeld IsActionDown;
	MM_IsInputDownOrHeld IsActionHeld;
	MM_IsInputDownOrHeld IsButtonDown;
	MM_IsInputDownOrHeld IsButtonHeld;
	MM_IsInputDownOrHeld IsKeyDown;
	MM_IsInputDownOrHeld IsKeyHeld;

	// game state
	MM_GetIntFP GetCurrentGameState;
	MM_SetIntFP TransitionToGameState;

	// room state
	MM_GetUIntFP GetRoomIndex;
	MM_GetFloatFP GetRoomTime;
	MM_VoidFP RoomReloadGameState;

	// session
	MM_VoidFP StartActiveSaveSlot;

	// entities
	MM_SetUIntFP SpawnEntity;

	// rng
	MM_SetUIntFP SeedGameRand;

	// misc/debug
	MM_VoidFP WarpToBoss;
	MM_VoidFP WarpToMiniBoss;
};
