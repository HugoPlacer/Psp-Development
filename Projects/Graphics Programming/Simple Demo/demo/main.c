#include "../common/callbacks.h"
#include "../common/common-sce.h"

#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>

#include <string.h>//??//??
#include <malloc.h>

PSP_MODULE_INFO("Texture Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int running = 1;
static unsigned int __attribute__((aligned(16))) list[262144];

Vertex __attribute__((aligned(16))) square_indexed[4] = {
    //change color to 0xFFFFFFFF to remove colours in images
    {0.0f, 0.0f, 0xFF00FFFF, -0.25f, -0.25f, -1.0f},
    {1.0f, 0.0f, 0xFFFF00FF, -0.25f, 0.25f, -1.0f},
    {1.0f, 1.0f, 0xFFFFFF00, 0.25f, 0.25f, -1.0f},
    {0.0f, 1.0f, 0xFF000000, 0.25f, -0.25f, -1.0f},
};

unsigned short __attribute__((aligned(16))) indices[6] = {
    0, 1, 2, 2, 3, 0
};

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

    Texture* tex = load_texture("container.jpg", GU_FALSE, GU_TRUE);
    Texture* tex2 = load_texture("circle.png", GU_FALSE, GU_TRUE);

    while (running)
    {
        startFrame(list);

        // Enable blend
        sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
        sceGuEnable(GU_BLEND);

        // We're doing a 2D
        sceGuDisable(GU_DEPTH_TEST);

        // clear screen

        sceGuClearColor(0xFFFFFFFFF); // GU_RGBA, GU_ABGR, GU_ARGB, GU_COLOR in pspgu.h is useful
        sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT | GU_STENCIL_BUFFER_BIT);

        // Draw Indexed Square
        reset_transform(-0.5f, 0.0f, 0.0f);
        bind_texture(tex);
        sceGumDrawArray(GU_TRIANGLES, GU_INDEX_16BIT | GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, indices, square_indexed);

        reset_transform(0.5f, 0.0f, 0.0f);
        bind_texture(tex2);
        sceGumDrawArray(GU_TRIANGLES, GU_INDEX_16BIT | GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, indices, square_indexed);

        endFrame();
    }

    termGraphics();

    sceKernelExitGame();
    return 0;
}