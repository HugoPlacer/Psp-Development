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

typedef struct
{
    float x, y, z;
    float yaw, pitch;
} Camera3D;

void apply_camera2d(const Camera2D *cam)
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

void apply_camera3d(const Camera3D *cam)
{
    sceGumMatrixMode(GU_VIEW);
    sceGumLoadIdentity();

    // SCALE -> ROTATION -> TRANSLATION normalmente
    // TRANSLATION -> ROTATION -> SCALE en psp

    ScePspFVector3 v = {cam->x, cam->y, cam->z};
    sceGumTranslate(&v);

    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();
}


typedef struct {
    float x, y, z;
    float rx, ry, rz;
    float sx, sy, sz;

    Mesh *mesh;
    Texture *tex;
} Cube;

Cube *create_cube(float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz, Texture *tex)
{
    Cube *cube = malloc(sizeof(Cube));
    if (cube == NULL)
        return NULL;

    cube->mesh = create_mesh(8, 36);
    if (cube->mesh == NULL)
    {
        free(cube);
        return NULL;
    }

    cube->x = x;
    cube->y = y;
    cube->z = z;
    cube->rx = rx;
    cube->ry = ry;
    cube->rz = rz;
    cube->sx = sx;
    cube->sy = sy;
    cube->sz = sz;
    cube->tex = tex;
    cube->mesh->index_count = 36;

    ((Vertex *)cube->mesh->data)[0] = create_vert(0, 0, 0xFFFFFFFF,-1, 1, 1), //3
    ((Vertex *)cube->mesh->data)[1] = create_vert(1, 0, 0xFFFFFFFF, 1, 1, 1), //2
    ((Vertex *)cube->mesh->data)[2] = create_vert(1, 1, 0xFFFFFFFF, 1,-1, 1), //1
    ((Vertex *)cube->mesh->data)[3] = create_vert(0, 1, 0xFFFFFFFF,-1,-1, 1), //0

    ((Vertex *)cube->mesh->data)[4] = create_vert(0, 1, 0xFFFFFFFF,-1, 1, -1), //7
    ((Vertex *)cube->mesh->data)[5] = create_vert(1, 1, 0xFFFFFFFF, 1, 1, -1), //6
    ((Vertex *)cube->mesh->data)[6] = create_vert(1, 0, 0xFFFFFFFF, 1, -1, -1), //5
    ((Vertex *)cube->mesh->data)[7] = create_vert(0, 0, 0xFFFFFFFF,-1, -1, -1), //4


    cube->mesh->indices[0] = 0;
    cube->mesh->indices[1] = 1;
    cube->mesh->indices[2] = 2;
    cube->mesh->indices[3] = 2;
    cube->mesh->indices[4] = 3;
    cube->mesh->indices[5] = 0;
    cube->mesh->indices[6] = 1;
    cube->mesh->indices[7] = 5;
    cube->mesh->indices[8] = 6;
    cube->mesh->indices[9] = 6;
    cube->mesh->indices[10] = 2;
    cube->mesh->indices[11] = 1;
    cube->mesh->indices[12] = 7;
    cube->mesh->indices[13] = 6;
    cube->mesh->indices[14] = 5;
    cube->mesh->indices[15] = 5;
    cube->mesh->indices[16] = 4;
    cube->mesh->indices[17] = 7;
    cube->mesh->indices[18] = 4;
    cube->mesh->indices[19] = 0;
    cube->mesh->indices[20] = 3;
    cube->mesh->indices[21] = 3;
    cube->mesh->indices[22] = 7;
    cube->mesh->indices[23] = 4;
    cube->mesh->indices[24] = 4;
    cube->mesh->indices[25] = 5;
    cube->mesh->indices[26] = 1;
    cube->mesh->indices[27] = 1;
    cube->mesh->indices[28] = 0;
    cube->mesh->indices[29] = 4;
    cube->mesh->indices[30] = 3;
    cube->mesh->indices[31] = 2;
    cube->mesh->indices[32] = 6;
    cube->mesh->indices[33] = 6;
    cube->mesh->indices[34] = 7;
    cube->mesh->indices[35] = 3;


    sceKernelDcacheWritebackInvalidateAll();

    return cube;
}

void draw_cube(Cube *cube)
{
    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();

    ScePspFVector3 v = {
        .x = cube->x,
        .y = cube->y,
        .z = cube->z,
    };
    sceGumTranslate(&v);

    ScePspFVector3 r = {
        .x = cube->rx,
        .y = cube->ry,
        .z = cube->rz,
    };
    sceGumRotateXYZ(&r);

    ScePspFVector3 s = {
        .x = cube->sx,
        .y = cube->sy,
        .z = cube->sz};
    sceGumScale(&s);

    bind_texture(cube->tex);
    draw_mesh(cube->mesh);
}

void destroy_cube(Cube *cube)
{
    destroy_mesh(cube->mesh);
    free(cube);
}



int main()
{
    SetupCallbacks();

    initGraphics(list);
    //sceGuDisable(GU_TEXTURE_2D);

    // setup matrices

    sceGumMatrixMode(GU_PROJECTION);
    sceGumLoadIdentity();
    sceGumPerspective(75.0f,16.0f/9.0f,0.5f,1000.0f);

    sceGumMatrixMode(GU_VIEW);
    sceGumLoadIdentity();

    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();

    Texture *texture = load_texture("UVChecker.png", GU_FALSE, GU_TRUE);
    if (!texture)
        goto cleanup;
    
    Cube* cube = create_cube(0.0f, 0.0f, -5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, texture);

    Camera3D camera =
        {
            .x = 0,
            .y = 0,
            .z = 0,
            .yaw = 0.0f,
            .pitch = 0.0f};

    int val = 0;

    while (running)
    {
        startFrame(list);

        // Enable blend
        sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
        sceGuEnable(GU_BLEND);

        // clear screen

        sceGuClearColor(0xff554433); // GU_RGBA, GU_ABGR, GU_ARGB, GU_COLOR in pspgu.h is useful
        sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

        apply_camera3d(&camera);

        draw_cube(cube);

        endFrame();
        val++;
        cube->rx = val * 0.79f * (GU_PI/180.0f);
        cube->ry = val * 0.98f * (GU_PI/180.0f);
        cube->rz = val * 1.32f * (GU_PI/180.0f);
    }

    destroy_cube(cube);

cleanup:

    termGraphics();

    sceKernelExitGame();
    return 0;
}