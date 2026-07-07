#include "MinaModAPI.h"
#include "MinaModEnums.h"

MinaModAPI* Mina = nullptr;

MM_Rtti entityRtti;
ycDrawUtil* dd = nullptr;

void WorldUpdate( void* );

extern "C"
MM_EXPORT
void MinaMod_Init( MinaModAPI* mm )
{
    Mina = mm;
    Mina->InstallHook( "WorldUpdate", 0, WorldUpdate );

    entityRtti = Mina->Hash64( "ycEntity", 8 );
}

/*
doing a full scene traversal is slow, if you need to do this every frame try
to do one scan and extract all of the information you need in a single pass
*/
void Traverse( ycEntity* entity, uint32_t depth )
{
    size_t numComponents = Mina->EntityGetChildren( entity, nullptr, 0 );
    if( numComponents == 0 ) { return; }
    ycComponent** components = (ycComponent**)Mina->Alloc( sizeof(ycComponent*) * numComponents );
    Mina->EntityGetChildren( entity, components, numComponents );
    for( size_t i = 0; i != numComponents; ++i )
    {
        ycComponent* c = components[ i ];
        MM_StringRef typeName = Mina->ComponentGetTypeName( c );
        Mina->Log( "%*c%.*s\n", depth*2, ' ', typeName.len, typeName.str );
        if( Mina->ComponentIsa( c, entityRtti ) )
        {
            Traverse( (ycEntity*)c, depth+1 );
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

    if( Mina->IsKeyDown( YC_KEY_G ) )
    {
        Mina->Log( "Traversing scene graph...\n" );
        Traverse( Mina->WorldGetGameRootEntity( ctx->world ), 1 );
    }
}
