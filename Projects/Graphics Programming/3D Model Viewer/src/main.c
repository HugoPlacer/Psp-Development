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
    sceGumOrtho(-16.0f / 9.0f, 16.0f / 9.0f, -1.0f, 1.0f, -10.0f, 10.0f);

    sceGumMatrixMode(GU_VIEW);
    sceGumLoadIdentity();

    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();

    Texture *texture = load_texture("container.jpg", GU_FALSE, GU_TRUE);
    if (!texture)
        goto cleanup;

    Sprite *sprite = create_sprite(-0.5f, 0.0f, 1.0f, 1.0f, texture);
    if (!sprite)
        goto cleanup;

    Camera2D camera =
        {
            .x = 0,
            .y = 0,
            .rot = 45.0f};

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

        apply_camera(&camera);

        draw_sprite(sprite);

        endFrame();

        camera.rot += 1.0f;
        camera.y = sinf(camera.rot / 180.0f * 5.0f) * 0.5f;
        sprite->x = sinf(camera.rot / 180.0f);
    }

    destroy_sprite(sprite);

cleanup:

    termGraphics();

    sceKernelExitGame();
    return 0;
}