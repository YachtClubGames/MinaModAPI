#pragma once

#include "MinaModTypes.h"

// FixedUpdate
struct FixedUpdateCtx
{
	float elapsed; // frame delta, 1/60 or 1/120
};

// GameStateTransition
struct GameStateTransitionCtx
{
	int32_t* pGameState; // pointer to the destination game state, can be modified
};

// GameInit
// a bit later than MinaMod_Init, after most systems are initialized

// GameShutdown

// WorldConstruct
struct WorldConstructCtx
{
	World* world;
};

// WorldDestroy
struct WorldDestroyCtx
{
	World* world;
};

// WorldUpdate
struct WorldUpdateCtx
{
	World* world;
	float elapsed;
};

// WorldUpdateEnd
// occurs in the same function as WorldUpdate, but after other objects and systems have updated
// same WorldUpdateCtx as WorldUpdate

// ItemsOnPickup
// runs at the start of Items::OnPickup
struct ItemsOnPickupCtx
{
	int32_t*  collectionIndex; // pointer arguments can be modified to change what the original function will see, if it runs afterward
	int32_t*  itemType;
	Player**  ppPlayer;
	const     MM_Vec3* pos;
	bool*     presentAllowed;
	int32_t*  subweaponUseBonus;
	int32_t*  shop;
	uint32_t* cheatFlags;
	bool*     subweaponBonusSlot;
	bool      modHandled; // set to true to prevent the original from running afterward
};

// ItemsOnPickupDone
// runs at the start of Items::OnPickupDone
struct ItemsOnPickupDoneCtx
{
	int32_t*       collectionIndex; // pointer arguments can be modified to change what the original function will see, if it runs afterward
	int32_t*       itemType;
	Player**       ppPlayer;
	const MM_Vec3* pos;
	int32_t*       subweaponUseBonus;
	int32_t*       shop;
	uint32_t*      cheatFlags;
	bool*          subweaponBonusSlot;
	bool           modHandled; // set to true to prevent the original from running afterward
};

// IsItemCollected
// runs at the start of Items::IsItemCollected
struct IsItemCollectedCtx
{
	ItemCollection* collection;
	SaveSlot*       saveSlot;
	int32_t         index;
	bool            includePawnShop;
	bool            includeEarlyCollected;
	bool            modHandled; // set to true to prevent the original from running afterward
	bool            modRetVal; // if modHandled is set, what should OnPickup() return?
};

// PickupOnPickup
// runs at the start of Pickup::OnPickup
struct PickupOnPickupCtx
{
	Pickup*         pickup;
	PickupListener* listener;
	bool            modHandled; // set to true to prevent the original from running afterward
	bool            modRetVal; // if modHandled is set, what should OnPickup() return?
};

// ShopItemRefresh
// runs at the start of ShopItem::Refresh
struct ShopItemRefreshCtx
{
	ShopItem* shopItem;
	bool modHandled; // set to true to prevent the original from running afterward
};

// AreaManagerNewArea
// runs at the start of AreaManager
struct AreaManagerNewAreaCtx
{
	int32_t* oldArea; // pointer arguments can be modified to change what the original function will see, if it runs afterward
	int32_t* newArea;
	bool modHandled; // set to true to prevent the original from running afterward
};

// ChestConstruct
// runs at the end of the Chest constructor
struct ChestConstructCtx
{
	Chest* chest;
};

// ycKeyboardUpdate
// runs at the start of the keyboard update
struct ycKeyboardUpdateCtx
{
	uint32_t* keysDown;           // bitmaps of keys [(YC_KEY_COUNT+31)/32]
	uint32_t* keysDownFirstFrame; // these are https://github.com/YachtClubGames/Propeller/blob/master/engine/src/ycBitField.h with YC_KEY_* as indices
};

// ycMouseUpdate
// runs at the start of the mouse update
struct ycMouseUpdateCtx
{
	float*   mouseDown; // [YC_TOUCH_COUNT]
	bool*    doubleClick;
	MM_Vec2* mouseScroll;
	MM_Vec2* mouseDelta; // only used in relative mouse mode
};

// ycControllerUpdate
// runs at the start of the controller update, only for controller 0
struct ycControllerUpdateCtx
{
	int32_t   channel;
	int32_t   _unused;
	bool*     exists;
	uint64_t* buttonDown; // bit field of YC_INPUT_*
	int16_t*  leftStickX;
	int16_t*  leftStickY;
	int16_t*  rightStickX;
	int16_t*  rightStickY;
	int16_t*  triggerLeft;
	int16_t*  triggerRight;
};
