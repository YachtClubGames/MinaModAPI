#include "MinaModAPI.h"
#include "MinaModEnums.h"

MinaModAPI* Mina = nullptr;
char* copiedSave = nullptr;

void FixedUpdate( void* );

extern "C"
__declspec(dllexport)
void MinaMod_Init( MinaModAPI* mm )
{
    Mina = mm;
    Mina->InstallHook( "FixedUpdate", 0, FixedUpdate );
}

void FixedUpdate( void* )
{
    bool isCtrl = Mina->IsKeyHeld( YC_KEY_LCTRL ) || Mina->IsKeyDown( YC_KEY_LCTRL ) || Mina->IsKeyHeld( YC_KEY_RCTRL ) || Mina->IsKeyDown( YC_KEY_RCTRL );
    if( Mina->IsKeyDown( YC_KEY_C ) && isCtrl )
    {
        Mina->Log( "Copying active save slot.\n" );
        if( copiedSave )
        {
            Mina->Free( copiedSave );
        }
		Mina->PlayerFlushToSave(); // some variables don't directly read/write to save data, make sure those get written too
        copiedSave = Mina->GetActiveSaveSlotContents();
    }
    if( Mina->IsKeyDown( YC_KEY_V ) && isCtrl )
    {
        Mina->Log( "Pasting active save slot.\n" );
        if( copiedSave )
        {
            Mina->SetActiveSaveSlotContents( copiedSave );
			Mina->PlayerRestoreFromSave();
            Mina->StartActiveSaveSlot();
        }
        else
        {
            Mina->Log( "  No save copied!\n" );
        }
    }
    if( Mina->IsKeyDown( YC_KEY_Z ) && isCtrl )
    {
        Mina->Log( "  Reloading room...\n" );
        Mina->RoomReloadGameState();
    }
}
