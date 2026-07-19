/*
Drag to select animations (like an RTS), selected anims will show their
palettes. Press P to randomize a color in the palettes of selected anims.
*/

#include "MinaModAPI.h"
#include "MinaModEnums.h"

#include <math.h>
#include <vector>

MinaModAPI* Mina = nullptr;

ycDrawUtil* dd = nullptr;
MM_Rtti entityRtti;
MM_Rtti gameAnimRtti;
MM_Rtti animTileRtti;
float totalElapsed = 0.0f;
std::vector< MM_WeakPtr* > selection;
bool selecting = false;
MM_Vec2 selectionStart;
MM_Vec2 selectionEnd;

void WorldUpdate( void* );

extern "C"
__declspec(dllexport)
void MinaMod_Init( MinaModAPI* mm )
{
	Mina = mm;
	Mina->InstallHook( "WorldUpdate", 0, WorldUpdate );

	entityRtti.typeId   = Mina->Hash64( "ycEntity", 8 );
	gameAnimRtti.typeId = Mina->Hash64( "GameAnim", 8 );
	animTileRtti.typeId = Mina->Hash64( "AnimTile", 8 );
}

template< class t_type > t_type Min( t_type a, t_type b ) { return a >= b ? b : a; }
template< class t_type > t_type Max( t_type a, t_type b ) { return a >= b ? a : b; }

ycComponent* EntityFindComponentByType( ycEntity* entity, MM_Rtti rtti )
{
	size_t numComponents = Mina->EntityGetChildren( entity, nullptr, 0 );
	if( numComponents == 0 ) { return nullptr; }
	ycComponent** components = (ycComponent**)Mina->Alloc( sizeof(ycComponent*) * numComponents );
	Mina->EntityGetChildren( entity, components, numComponents );
	for( size_t i = 0; i != numComponents; ++i )
	{
		ycComponent* c = components[ i ];
		MM_Rtti componentType = Mina->ComponentGetType( c );
		if( componentType.typeId == rtti.typeId )
		{
			Mina->Free( components );
			return c;
		}
	}
	Mina->Free( components );
	return nullptr;
}

void SelectGameAnims( ycEntity* root )
{
	size_t numComponents = Mina->EntityGetChildren( root, nullptr, 0 );
	if( numComponents == 0 ) { return; }
	ycComponent** components = (ycComponent**)Mina->Alloc( sizeof(ycComponent*) * numComponents );
	Mina->EntityGetChildren( root, components, numComponents );
	for( size_t i = 0; i != numComponents; ++i )
	{
		ycComponent* c = components[ i ];
		MM_Rtti componentType = Mina->ComponentGetType( c ) ;
		if( componentType.typeId != entityRtti.typeId )
		{
			continue;
		}
		ycEntity* entity = (ycEntity*)c;
		if( EntityFindComponentByType( entity, animTileRtti ) ) // skip anim tiles, theres too many of them and it crowds the screen
		{
			continue;
		}
		GameAnim* gameAnim = (GameAnim*)EntityFindComponentByType( entity, gameAnimRtti );
		if( gameAnim )
		{
			MM_Transform transform = Mina->EntityGetWorldTransform( entity );
			MM_Vec3 pos = transform.t;
			float selectionMinX = Min( selectionStart.x, selectionEnd.x );
			float selectionMaxX = Max( selectionStart.x, selectionEnd.x );
			float selectionMinY = Min( selectionStart.y, selectionEnd.y );
			float selectionMaxY = Max( selectionStart.y, selectionEnd.y );
			if( pos.x >= selectionMinX && pos.x <= selectionMaxX && pos.y >= selectionMinY && pos.y <= selectionMaxY )
			{
				selection.push_back( Mina->CreateWeakPtr(gameAnim) );
			}
		}
	}
	Mina->Free( components );
};

void DrawCross( MM_Vec3 pos, float extents, MM_Color color )
{
	MM_Vec3 top    = MM_Vec3{ pos.x, pos.y+extents };
	MM_Vec3 bottom = MM_Vec3{ pos.x, pos.y-extents };
	Mina->DebugDrawLine( dd, top, bottom, color, true );
	MM_Vec3 left   = MM_Vec3{ pos.x-extents, pos.y };
	MM_Vec3 right  = MM_Vec3{ pos.x+extents, pos.y };
	Mina->DebugDrawLine( dd, left, right, color, true );
}

void DrawCrossThick( MM_Vec3 pos, float extents, float thickness, MM_Color color )
{
	Mina->DebugDrawRectSolid( dd, pos, thickness, extents*2.0f, color, true );
	Mina->DebugDrawRectSolid( dd, pos, extents*2.0f, thickness, color, true );
}

void WorldUpdate( void* pCtx )
{
	struct WorldUpdateCtx
	{
		World* world;
		float elapsed;
	};
	WorldUpdateCtx* ctx = (WorldUpdateCtx*)pCtx;
	World* world = ctx->world;
	if( world != Mina->PlayerGetWorld() )
	{
		return;
	}
	dd = Mina->GetDebugDraw( "World" );

	GameCamera* gameCamera = Mina->WorldGetGameCamera( world );

	MM_Vec2 mouseScreen;
	Mina->MouseGetPosGameCameraScreen( gameCamera, &mouseScreen );
	MM_Vec2 mouseWorld;
	Mina->GameCameraScreenToWorld( gameCamera, mouseScreen, &mouseWorld );

	MM_Vec3 minaPos = Mina->PlayerGetPos3();

	// begin selection
	if( !selecting )
	{
		if( Mina->IsButtonDown( YC_INPUT_MOUSE_LEFT ) )
		{
			selecting = true;
			selectionStart = mouseWorld;
		}
	}
	// update/end selection
	else
	{
		if( Mina->IsButtonHeld( YC_INPUT_MOUSE_LEFT ) )
		{
			MM_Vec3 selectionCenter{
				(selectionStart.x+mouseWorld.x)*0.5f,
				(selectionStart.y+mouseWorld.y)*0.5f,
				minaPos.z
			};
			float selectionWidth  = fabsf(selectionStart.x-mouseWorld.x);
			float selectionHeight = fabsf(selectionStart.y-mouseWorld.y);
			Mina->DebugDrawRect( dd, selectionCenter, selectionWidth, selectionHeight, MM_Color{255,255,255,255}, true );
		}
		else
		{
			selecting = false;
			selectionEnd = mouseWorld;

			// clear previous selection
			for( auto gameAnimWeakPtr : selection ) { Mina->DestroyWeakPtr( gameAnimWeakPtr ); }
			selection.clear();

			// find new selection
			SelectGameAnims( Mina->WorldGetGameRootEntity( world ) );
		}
	}

	// draw selected items
	for( auto gameAnimWeakPtr : selection )
	{
		ycComponent* gameAnim = (ycComponent*)Mina->WeakPtrGet( gameAnimWeakPtr );
		if( gameAnim == nullptr ) { continue; } // skip components that don't exist anymore, could remove them from the list here too
		ycEntity* entity = Mina->ComponentGetParent((ycComponent*)gameAnim);

		MM_Transform transform = Mina->EntityGetWorldTransform( entity );
		MM_Vec3 pos = transform.t;

		ycPaletteTexture* pal = Mina->GameAnimGetPalette( gameAnim );
		if( pal == nullptr ) { continue; }

		uint32_t palWidth = Mina->PaletteGetWidth( pal );

		uint32_t maxEntriesPerRow = 16;
		uint32_t rows = (palWidth+maxEntriesPerRow-1)/maxEntriesPerRow;
		float palEntryWidth = 0.3f;
		float palEntryHeight = 0.2f;
		float totalPalWidth = palEntryWidth * float(rows > 1 ? maxEntriesPerRow : palWidth);
		float palDrawOffsetX = totalPalWidth * -0.5f + palEntryWidth*0.5f; // offset an extra half width since we're drawing rects from their center
		float palDrawOffsetY = -0.25f;
		MM_Vec3 palPos{ pos.x+palDrawOffsetX, pos.y+palDrawOffsetY, pos.z };
		for( uint32_t p = 0; p != palWidth; ++p )
		{
			MM_Color color;
			Mina->PaletteGetLocalColor( pal, p, &color );
			Mina->DebugDrawRectSolid( dd, palPos, palEntryWidth, palEntryHeight, color, true );
			palPos.x += palEntryWidth;
			if( ((p+1) % maxEntriesPerRow) == 0 )
			{
				palPos.x = pos.x+palDrawOffsetX;
				palPos.y -= palEntryHeight;
			}
		}

		DrawCross( pos, 0.5f, MM_Color{255,255,255,255} );

		// randomize palette entries
		/*
		to make this robust, we're gonna build a whole new palette, so it won't
		interfere with other things that may share
		*/
		if( Mina->IsKeyDown( YC_KEY_P ) )
		{
			ycPaletteTexture* newPal = Mina->ClonePalette( pal );
			Mina->PaletteSetGroup( newPal, -1 );
			int32_t randIdx = rand() % palWidth;
			MM_Color prevColor;
			Mina->PaletteGetLocalColor( newPal, randIdx, &prevColor );
			MM_Color newColor = { uint8_t(rand()%255), uint8_t(rand()%255), uint8_t(rand()%255), prevColor.a };
			Mina->PaletteWriteIndex( newPal, randIdx, newColor );
			Mina->GameAnimSetPalette( gameAnim, newPal );
			Mina->ReleasePalette( newPal );
		}
	}

	// draw a mouse cursor
	MM_Color crossColor =
	{
		uint8_t( 255.0f * sin(totalElapsed*1.11f*0.2f)*0.5f+0.5f ),
		uint8_t( 255.0f * sin(totalElapsed*1.33f*0.2f)*0.5f+0.5f ),
		uint8_t( 255.0f * sin(totalElapsed*1.73f*0.2f)*0.5f+0.5f ),
		255
	};
	DrawCrossThick( MM_Vec3{ mouseWorld.x, mouseWorld.y, minaPos.z }, 0.5f, 0.1f, crossColor );

	// we could also just unhide the system cursor
	//if( !Mina->MouseIsCursorVisible() )
	//{
	//	Mina->MouseSetCursorVisible( true );
	//}

	// this takes into account time dilation, ctx->elapsed doesn't
	totalElapsed += Mina->WorldGetElapsedTime( world );
}
