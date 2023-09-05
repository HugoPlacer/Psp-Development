#include "../common/callbacks.h"
#include "../common/common-sce.h"
#include <malloc.h>

#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>
#include <string.h>
#include <math.h>

PSP_MODULE_INFO("Texture Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int running = 1;
static unsigned int __attribute__((aligned(16))) list[262144];

typedef struct
{
    void *data;
    u16 *indices;
    u32 index_count;
} Mesh;

Mesh *create_mesh(u32 vcount, u32 index_count)
{
    Mesh *mesh = malloc(sizeof(Mesh));
    if (mesh == NULL)
        return NULL;

    mesh->data = memalign(16, sizeof(Vertex) * vcount);
    if (mesh->data == NULL)
    {
        free(mesh);
        return NULL;
    }

    mesh->indices = memalign(16, sizeof(u16) * index_count);
    if (mesh->indices == NULL)
    {
        free(mesh->data);
        free(mesh);
        return NULL;
    }

    mesh->index_count = index_count;

    return mesh;
}

void draw_mesh(Mesh *mesh)
{
    sceGumDrawArray(GU_TRIANGLES, GU_INDEX_16BIT | GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, mesh->index_count, mesh->indices, mesh->data);
}

void destroy_mesh(Mesh *mesh)
{
    free(mesh->data);
    free(mesh->indices);
    free(mesh);
}

typedef struct
{
    float x, y;
    float rot;
    float sx, sy;

    int layer;

    Mesh *mesh;
    Texture *tex;
} Sprite;

Vertex create_vert(float u, float v, unsigned int color, float x, float y, float z)
{
    Vertex vert = {
        .u = u,
        .v = v,
        .color = color,
        .x = x,
        .y = y,
        .z = z,
    };
    return vert;
}

typedef struct {
    float w, h; //el tamaño en pixeles de cada subtextura
} TextureAtlas;

// revisar esta funcion porque no acabo de entender que hacen los calculos
void get_uv_index(TextureAtlas* atlas, float* buf, int idx){
    int row = idx / (int)atlas->w;
    int column = idx % (int)atlas->h;

    float sizeX = 1.f / ((float)atlas->w);
    float sizeY = 1.f / ((float)atlas->h);

    float y = (float)row * sizeY;
    float x = (float)column * sizeX;

    float h = y + sizeY;
    float w = x + sizeX;

    buf[0] = x;
    buf[1] = h; //y para hacer top left origin

    buf[2] = x;
    buf[3] = y;

    buf[4] = w;
    buf[5] = y;

    buf[6] = w;
    buf[7] = h;
}

typedef struct {
    int x, y;
    int tex_idx;
} Tile;

typedef struct {
    float x, y;
    float scale_x, scale_y;
    int w, h;
    TextureAtlas atlas;
    Texture* texture;
    Tile* tiles;
    Mesh* mesh;
} Tilemap;

Tilemap* create_tilemap(TextureAtlas atlas, Texture* tex, int sizex, int sizey){
    Tilemap* tilemap = (Tilemap*)malloc(sizeof(Tilemap));
    if(tilemap == NULL)
        return NULL;
    
    tilemap->tiles = (Tile*)malloc(sizeof(Tile) * sizex * sizey);
    if(tilemap->tiles == NULL){
        free(tilemap);
        return NULL;
    }

    tilemap->mesh = create_mesh(sizex * sizey * 4, sizex * sizey * 6);
    if(tilemap->mesh == NULL){
        free(tilemap->tiles);
        free(tilemap);
        return NULL;
    }

    memset(tilemap->mesh->data, 0, sizeof(Vertex) * sizex * sizey * 4);
    memset(tilemap->mesh->indices, 0, sizeof(u16) * sizex * sizey * 6);
    memset(tilemap->tiles, 0, sizeof(Tile) * sizex * sizey);

    tilemap->atlas = atlas;
    tilemap->texture = tex;
    tilemap->x = 0;
    tilemap->y = 0;
    tilemap->w = sizex;
    tilemap->h = sizey;
    tilemap->mesh->index_count = tilemap->w * tilemap->h * 6;
    tilemap->scale_x = 16.0f;
    tilemap->scale_y = 16.0f;

    return tilemap;
}

void destroy_tilemap(Tilemap* tilemap){
    destroy_mesh(tilemap->mesh);
    free(tilemap->tiles);
    free(tilemap);
}

void draw_tilemap(Tilemap* tilemap){
    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();

    ScePspFVector3 v = {
        .x = tilemap->x,
        .y = tilemap->y,
        .z = 0.0f,
    };
    sceGumTranslate(&v);

    ScePspFVector3 v1 = {
        .x = tilemap->scale_x,
        .y = tilemap->scale_y,
        .z = 0.0f,
    };
    sceGumScale(&v1);

    bind_texture(tilemap->texture);
    draw_mesh(tilemap->mesh);
}

void build_tilemap(Tilemap* tilemap){
    for(int i = 0; i < tilemap->w * tilemap->h; i++){
        float buf[8];
        get_uv_index(&tilemap->atlas, buf, tilemap->tiles[i].tex_idx);

        float tx = (float)tilemap->tiles[i].x;
        float ty = (float)tilemap->tiles[i].y;
        float tw = tx + 1.0f;
        float th = ty + 1.0f;

        ((Vertex*)tilemap->mesh->data)[i * 4 + 0] = create_vert(buf[0], buf[1], 0xFFFFFFFF, tx, ty, 0.0f);
        ((Vertex*)tilemap->mesh->data)[i * 4 + 1] = create_vert(buf[2], buf[3], 0xFFFFFFFF, tx, th, 0.0f);
        ((Vertex*)tilemap->mesh->data)[i * 4 + 2] = create_vert(buf[4], buf[5], 0xFFFFFFFF, tw, th, 0.0f);
        ((Vertex*)tilemap->mesh->data)[i * 4 + 3] = create_vert(buf[6], buf[7], 0xFFFFFFFF, tw, ty, 0.0f);

        tilemap->mesh->indices[i * 6 + 0] = (i * 4) + 0;
        tilemap->mesh->indices[i * 6 + 1] = (i * 4) + 1;
        tilemap->mesh->indices[i * 6 + 2] = (i * 4) + 2;
        tilemap->mesh->indices[i * 6 + 3] = (i * 4) + 2;
        tilemap->mesh->indices[i * 6 + 4] = (i * 4) + 3;
        tilemap->mesh->indices[i * 6 + 5] = (i * 4) + 0;
    }
    sceKernelDcacheWritebackInvalidateAll();
}

void draw_text(Tilemap* t, const char* str){
    int len = strlen(str);

    for(int i = 0; i < len; i++){
        char c = str[i];

        Tile tile = {
            .x = i,
            .y = 0,
            .tex_idx = c
        };

        t->tiles[i] = tile;
    }
}

Sprite *create_sprite(float x, float y, float sx, float sy, Texture *tex)
{
    Sprite *sprite = malloc(sizeof(Sprite));
    if (sprite == NULL)
        return NULL;

    sprite->mesh = create_mesh(4, 6);
    if (sprite->mesh == NULL)
    {
        free(sprite);
        return NULL;
    }

    sprite->x = x;
    sprite->y = y;
    sprite->layer = 0;
    sprite->rot = 0;
    sprite->sx = sx;
    sprite->sy = sy;
    sprite->tex = tex;
    sprite->mesh->index_count = 6;

    ((Vertex *)sprite->mesh->data)[0] = create_vert(0, 0, 0xFFFFFFFF, -0.25f, -0.25f, 0.0f);
    ((Vertex *)sprite->mesh->data)[1] = create_vert(0, 1, 0xFFFFFFFF, -0.25f, 0.25f, 0.0f);
    ((Vertex *)sprite->mesh->data)[2] = create_vert(1, 1, 0xFFFFFFFF, 0.25f, 0.25f, 0.0f);
    ((Vertex *)sprite->mesh->data)[3] = create_vert(1, 0, 0xFFFFFFFF, 0.25f, -0.25f, 0.0f);

    sprite->mesh->indices[0] = 0;
    sprite->mesh->indices[1] = 1;
    sprite->mesh->indices[2] = 2;
    sprite->mesh->indices[3] = 2;
    sprite->mesh->indices[4] = 3;
    sprite->mesh->indices[5] = 0;

    sceKernelDcacheWritebackInvalidateAll();

    return sprite;
}

void draw_sprite(Sprite *sprite)
{
    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();

    ScePspFVector3 v = {
        .x = sprite->x,
        .y = sprite->y,
        .z = sprite->layer,
    };
    sceGumTranslate(&v);
    sceGumRotateZ(sprite->rot);

    ScePspFVector3 s = {
        .x = sprite->sx,
        .y = sprite->sy,
        .z = 1.0f};
    sceGumScale(&s);

    bind_texture(sprite->tex);
    draw_mesh(sprite->mesh);
}

void destroy_sprite(Sprite *sprite)
{
    destroy_mesh(sprite->mesh);
    free(sprite);
}

typedef struct
{
    float x, y;
    float rot;
} Camera2D;

void apply_camera(const Camera2D *cam)
{
    sceGumMatrixMode(GU_VIEW);
    sceGumLoadIdentity();

    // SCALE -> ROTATION -> TRANSLATION normalmente
    // TRANSLATION -> ROTATION -> SCALE en psp

    ScePspFVector3 v = {cam->x, cam->y, 0.0f};
    sceGumTranslate(&v);
    sceGumRotateZ(cam->rot / 180.0f * GU_PI);

    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();
}

int main()
{
    SetupCallbacks();

    initGraphics(list);

    // setup matrices

    sceGumMatrixMode(GU_PROJECTION);
    sceGumLoadIdentity();
    sceGumOrtho(0, 480, 0.0f, 272.0f, -10.0f, 10.0f);

    sceGumMatrixMode(GU_VIEW);
    sceGumLoadIdentity();

    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();

    Texture *texture = load_texture("terrain.png", GU_FALSE, GU_TRUE);
    if (!texture)
        goto cleanup;
    
    Texture *texture2 = load_texture("default.png", GU_FALSE, GU_TRUE);
    if (!texture2)
        goto cleanup;
    
    TextureAtlas atlas = {.w = 16, .h = 16};
    Tilemap* tilemap = create_tilemap(atlas, texture, 16, 16); //los ultimos dos numeros estan relacionados con los bucles de abajo, si hay menos no se puede acceder a la memoria asi que es como si "permitiera" acceder a eso, tipo el numero/tamaño maximo de tiles
    tilemap->x = 0; //posicion del tilemap, descubrir como interactua con cada tile, si afecta o no y como contrarestarlo
    tilemap->y = 0;  //posicion del tilemap

    // for(int y = 0; y < 16; y++) {
    //     for(int x = 0; x < 16; x++) {
    //         Tile tile = {
    //             .x = x,
    //             .y = y,
    //             .tex_idx = x + y * 16 //el numero del final de esta multiplicaciobn (x + y * 10) esta relacionado con los de arriba
    //         };
    //         tilemap->tiles[x + y * 16] = tile;
    //     }
    // }

    Tile dirt = {
        .x = 2, //define la posicion en la que se renderiza la tile individual
        .y = 2, //define la posicion en la que se renderiza la tile individual
        .tex_idx = 0 + 2 //define que textura del atlas tiene la tile (sumar la x + la y (porque es una array lineal en realidad))
    };

    tilemap->tiles[0 + 1] = dirt; //asigna la informacion de la tile configurada en la array de tiles del tilemap creo

    build_tilemap(tilemap);

    Tilemap* tilemap2 = create_tilemap(atlas, texture2, 8, 8);
    tilemap2->x = 144;
    tilemap2->y = 16;

    draw_text(tilemap2, "Hello World!");
    build_tilemap(tilemap2);

    while (running)
    {
        startFrame(list);

        // Enable blend
        sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
        sceGuEnable(GU_BLEND);

        // We're doing a 2D
        sceGuDisable(GU_DEPTH_TEST);

        // clear screen

        sceGuClearColor(0xFF000000); // GU_RGBA, GU_ABGR, GU_ARGB, GU_COLOR in pspgu.h is useful
        sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT | GU_STENCIL_BUFFER_BIT);

        draw_tilemap(tilemap);
        draw_tilemap(tilemap2);

        endFrame();
    }

    destroy_tilemap(tilemap);
    destroy_tilemap(tilemap2);

cleanup:

    termGraphics();

    sceKernelExitGame();
    return 0;
}

