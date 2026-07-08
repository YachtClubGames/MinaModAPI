#include "MinaModAPI.h"
#include "MinaModEnums.h"

#include <stdlib.h> // rand
#include <vector>

MinaModAPI* Mina = nullptr;

struct TileLevelEntity
{
    World* world;
    ycTileLevel2Entity* tileLevelEntity;
};

struct WorldCtx
{
    World* world;
};

struct DebugMessage
{
    const char* msg;
    float opacity;
};
std::vector< DebugMessage > DebugMessages;

void GameInit( void* );
void WorldUpdate( void* );
void CustomUpdate( void* );

// Chests require two spawn points, one for the chest itself, and one for the entity inside
// The chest spawn point doesn't need to do much, but it needs to exist so that it can have a child.
// The best place to learn about the format of these entries is by looking at the level .tlb.yc files
const char* kChestDesc = "ycTileLevel2Entity { m_entityType: 69, m_spawnType: kTileLevel2EntitySpawnType_Disable };";
const char* kChestContentsDesc[] =
{
    // some joules
    "ycTileLevel2Entity { m_props: [ ycTileLevel2Property{ m_nameHash: 757711815 }, ycTileLevel2Property{ m_nameHash: 1441311248, m_value: \"MagicSmall\", } ], m_scale: ycVec2{ x: 1, y: 1 }, m_entityType: 36, m_spawnType: kTileLevel2EntitySpawnType_Contents };",
    // daggers
    "ycTileLevel2Entity { m_props: [ ycTileLevel2Property{ m_nameHash: 757711815 }, ycTileLevel2Property{ m_nameHash: 1441311248, m_value: \"Daggers\", } ], m_scale: ycVec2{ x: 1, y: 1 }, m_entityType: 36, m_spawnType: kTileLevel2EntitySpawnType_Contents };",
    // the world map
    "ycTileLevel2Entity { m_props: [ ycTileLevel2Property{ m_nameHash: 757711815 }, ycTileLevel2Property{ m_nameHash: 1441311248, m_value: \"WorldMap\", } ], m_scale: ycVec2{ x: 1, y: 1 }, m_entityType: 36, m_spawnType: kTileLevel2EntitySpawnType_Contents };",
    // a spark
    "ycTileLevel2Entity { m_props: [ ycTileLevel2Property{ m_nameHash: 757711815 }, ycTileLevel2Property{ m_nameHash: 1441311248, m_value: \"Spark\", } ], m_scale: ycVec2{ x: 1, y: 1 }, m_entityType: 36, m_spawnType: kTileLevel2EntitySpawnType_Contents };",
    // a gooper
    "ycTileLevel2Entity { m_scale: ycVec2{ x: 1, y: 1 }, m_entityType: 14, m_spawnType: kTileLevel2EntitySpawnType_Contents };"
};
#define ARRAY_SIZE( x ) (sizeof(x)/sizeof(x[0]))

ycTileLevel2Entity* ChestLevelEntity = nullptr;
ycTileLevel2Entity* ChestContentsLevelEntities[ ARRAY_SIZE(kChestContentsDesc) ];

extern "C"
__declspec(dllexport)
void MinaMod_Init( MinaModAPI* mm )
{
    Mina = mm;

    Mina->InstallHook( "GameInit", 0, GameInit );
    Mina->InstallHook( "WorldUpdate", 0, WorldUpdate );
}

void GameInit( void* )
{
    // the world update queue is not initialized yet during MinaMod_Init
    Mina->UpdateQueueAdd( Mina->GameGetWorldUpdateQueue(), CustomUpdate, nullptr );

    // load a font so we can use DebugDraw's text rendering
    // your mod must have a data/debugdraw.font.yc for this to work
    ycFileRefBase* fileRef = Mina->CreateFileRef( "debugdraw.font.yc" );
    bool fontLoaded = Mina->FileRefWaitForLoaded( fileRef );
    Mina->Assert( fontLoaded, "Could not find debugdraw.font.yc" );

    // cache level entities
    ChestLevelEntity = Mina->CreateTileLevelEntity( kChestDesc );
    for( int i = 0; i != ARRAY_SIZE(kChestContentsDesc); ++i )
    {
        ChestContentsLevelEntities[ i ] = Mina->CreateTileLevelEntity( kChestContentsDesc[i] );
    }
}

void WorldUpdate( void* pCtx )
{
    WorldCtx* ctx = (WorldCtx*)pCtx;

    // there can be many Worlds in existence at once, we only care about the one the player is in
    if( ctx->world != Mina->PlayerGetWorld() )
    {
        return;
    }
    
    bool isCtrl = Mina->IsKeyHeld( YC_KEY_LCTRL ) || Mina->IsKeyDown( YC_KEY_LCTRL ) || Mina->IsKeyHeld( YC_KEY_RCTRL ) || Mina->IsKeyDown( YC_KEY_RCTRL );
    if( Mina->IsKeyDown( YC_KEY_C ) && isCtrl )
    {
        // the spawn points will be automatically destroyed with the WorldRegion, but we could destroy them
        // earlier by tracking object lifetime with a weak pointer
        World* world = ctx->world;
        WorldRegion* worldRegion = Mina->PlayerGetWorldRegion();
        SpawnManager* spawnManager = Mina->WorldRegionGetSpawnManager( worldRegion );;
        SpawnPoint* chestSpawnPoint = Mina->SpawnManagerCreateSpawnPoint2( spawnManager, worldRegion, ChestLevelEntity );
        SpawnPoint* contentsSpawnPoint = Mina->SpawnManagerCreateSpawnPoint2( spawnManager, worldRegion, ChestContentsLevelEntities[ rand() % ARRAY_SIZE(ChestContentsLevelEntities) ] );
        Mina->SpawnPointSetupParentSpawnPoint( contentsSpawnPoint, chestSpawnPoint );

        MM_Vec3 pos = Mina->PlayerGetPos3();
        Mina->SpawnEntity2( Mina->WorldGetGameRootEntity(world), ENTITYTYPE_CHEST, pos, MM_Vec3{1.0f,1.0f,1.0f}, 0.0f, 1, chestSpawnPoint, nullptr, nullptr );

        DebugMessages.insert( DebugMessages.begin(), { "Spawned a chest!", 1.0f } );
    }
}

void CustomUpdate( void* )
{
    // display debug messages
    // this could go in WorldUpdate, but then its draw/fade would be conditional on world existence,
    // and FixedUpdate occurs too early in the frame to use DebugDraw

    ycDrawUtil* dd = Mina->GetDebugDraw( "Hud" );
    float y = 0.0f;
    for( auto i = DebugMessages.begin(); i != DebugMessages.end(); /**/ )
    {
        uint8_t opacity = uint8_t( 255.0f * i->opacity );
        Mina->DebugDrawText( dd, i->msg, MM_Color{   0,   0,   0, opacity }, MM_Vec3{ 3, y-3, 0 }, 30 );
        Mina->DebugDrawText( dd, i->msg, MM_Color{ 255, 255, 255, opacity }, MM_Vec3{ 0, y  , 0 }, 30 );
        i->opacity -= 0.005f;
        y -= 40;
        if( i->opacity <= 0.0f ) {  i = DebugMessages.erase( i ); }
        else { ++i; }
    }
}
