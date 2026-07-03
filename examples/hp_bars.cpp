#include "MinaModAPI.h"
#include "MinaModEnums.h"

MinaModAPI* Mina = nullptr;

ycDrawUtil* dd = nullptr;
MM_Rtti entityRtti;
MM_Rtti combatCoreRtti;

void WorldUpdate( void* );

extern "C"
__declspec(dllexport)
void MinaMod_Init( MinaModAPI* mm )
{
    Mina = mm;
    Mina->InstallHook( "WorldUpdate", 0, WorldUpdate );

	entityRtti = Mina->Hash64( "ycEntity", 8 );
	combatCoreRtti = Mina->Hash64( "CombatCore", 10 );
}

void TraverseCombat( ycEntity* entity )
{
    size_t numComponents = Mina->EntityGetChildren( entity, nullptr, 0 );
    if( numComponents == 0 ) { return; }
    ycComponent** components = (ycComponent**)Mina->Alloc( sizeof(ycComponent*) * numComponents );
    Mina->EntityGetChildren( entity, components, numComponents );
    for( size_t i = 0; i != numComponents; ++i )
    {
        ycComponent* c = components[ i ];
        MM_Rtti componentType = Mina->ComponentGetType( c ) ;
        if( componentType == entityRtti )
        {
            TraverseCombat( (ycEntity*)c );
        }
        else if( componentType == combatCoreRtti )
        {
            MM_Transform transform = Mina->EntityGetWorldTransform( Mina->ComponentGetParent( c ) );
            MM_Vec3 pos = transform.t;
            pos.y += 1.5f;
            float barWidth = 1.0f;
            float barHeight = 0.2f;
            float border = 0.1f;
            Mina->DebugDrawRectSolid( dd, pos, barWidth+border*2.0f, barHeight+border*2.0f, MM_Color{ 0, 0, 0, 255 }, true );
            float healthPerc = Mina->CombatCoreGetHealth( c ) / Mina->CombatCoreGetHealthMax( c );
            float greenBarWidth = healthPerc/barWidth;
            pos.x -= (barWidth-greenBarWidth)*0.5f; // offset since this is drawing from center
            Mina->DebugDrawRectSolid( dd, pos, greenBarWidth, barHeight, MM_Color{ 0, 255, 0, 255 }, true );
        }
    }
    Mina->Free( components );
};

void WorldUpdate( void* pCtx )
{
	struct WorldUpdateCtx
	{
		World* world;
	};
	WorldUpdateCtx* ctx = (WorldUpdateCtx*)pCtx;
	dd = Mina->GetDebugDraw( "World" );
	TraverseCombat( Mina->WorldGetGameRootEntity( ctx->world ) );
}
