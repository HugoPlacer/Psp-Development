#include "../common/callbacks.h"
#include "../common/common-sce.h"
#include "game.h"
#include <malloc.h>

#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>
#include <string.h>
#include <math.h>

PSP_MODULE_INFO("Flappy Bird", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int running = 1;
static unsigned int __attribute__((aligned(16))) list[262144];

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
        
        sprite->x += 0.01f;
    }

    destroy_sprite(sprite);

cleanup:

    termGraphics();

    sceKernelExitGame();
    return 0;
}
