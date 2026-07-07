#include "MinaModAPI.h"
#include "MinaModEnums.h"

#include <math.h>
#include <stdio.h>

MinaModAPI* Mina = nullptr;

void FixedUpdate( void* );

ycTexture* texture = nullptr;
ycGpuBuffer* vertexBuffer;
ycGpuBuffer* indexBuffer;

extern "C"
MM_EXPORT
void MinaMod_Init( MinaModAPI* mm )
{
    Mina = mm;
    Mina->InstallHook( "FixedUpdate", 0, FixedUpdate );
}

void FixedUpdate( void* )
{
    // init rendering stuff
    if( texture == nullptr )
    {
        const uint32_t w = 32;
        const uint32_t h = 32;
        texture = Mina->CreateTexture( w, h );
        MM_Color* texData = (MM_Color*)Mina->Alloc( sizeof(MM_Color)*w*h );
        for( uint32_t y = 0; y != h; ++y )
        {
            for( uint32_t x = 0; x != w; ++x )
            {
                texData[ y*w + x] = MM_Color{ 255, 255, 255, 255 };
            }
        }
        Mina->UpdateTexture( texture, texData );
        Mina->Free( texData );

        vertexBuffer = Mina->CreateVertexBuffer( 4 );
        // vertices are updated every frame

        indexBuffer = Mina->CreateIndexBuffer( 6 );
        uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
        Mina->UpdateGpuBuffer( indexBuffer, indices );

        Mina->CreateRenderObject( Mina->GetRenderPass( "hudEngine" ), []( void*, MM_RenderCtx* ctx )
        {
            ycRenderDrawCall* dc = ctx->drawCall;
            Mina->RenderDrawCallSetIndexBuffer( dc, indexBuffer );
            Mina->RenderDrawCallSetVertexBuffer( dc, vertexBuffer );
            Mina->RenderDrawCallSetTexture( dc, texture );
            Mina->RenderCmdDrawIndexed( ctx->cmdList, dc, 6, 0 );
        }, nullptr );
    }

    // update vertices
    static float elapsed = 0.0;
    float freq = 0.1f;
    float t = elapsed * freq;
    MM_Color color =
    {
        (uint8_t)(sin(t) * 127.5f + 127.5f),
        (uint8_t)(sin(t*0.9 + 2.0f) * 127.5f + 127.5f),
        (uint8_t)(sin(t*1.1 + 4.0f) * 127.5f + 127.5f),
        255
    };
    elapsed += 1.0f/6.0f;
    {
        float scale = 100.0f;
        float z = 0.5f;

        MM_Vertex_PTC verts[4];
        verts[0].pos = MM_Vec3{ -1.0f * scale, 1.0f * scale, z };
        verts[0].u = 0.0f;
        verts[0].v = 0.0f;
        verts[0].color = color;

        verts[1].pos = MM_Vec3{ 1.0f * scale, 1.0f * scale, z };
        verts[1].u = 1.0f;
        verts[1].v = 0.0f;
        verts[1].color = color;

        verts[2].pos = MM_Vec3{ 1.0f * scale, -1.0f * scale, z };
        verts[2].u = 1.0f;
        verts[2].v = 1.0f;
        verts[2].color = color;

        verts[3].pos = MM_Vec3{ -1.0f * scale, -1.0f * scale, z };
        verts[3].u = 0.0f;
        verts[3].v = 1.0f;
        verts[3].color = color;
        Mina->UpdateGpuBuffer( vertexBuffer, verts );
    }
}
