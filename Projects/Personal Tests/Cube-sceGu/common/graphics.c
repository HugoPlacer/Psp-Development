#include "graphics.h"

#include <pspgu.h>
#include <pspdisplay.h>

void initGraphics()
{
    void *fbp0 = getStaticVramBuffer(PSP_BUF_WIDTH, PSP_SCR_HEIGHT, GU_PSM_8888);
    void *fbp1 = getStaticVramBuffer(PSP_BUF_WIDTH, PSP_SCR_HEIGHT, GU_PSM_8888);
    void *zbp = getStaticVramBuffer(PSP_BUF_WIDTH, PSP_SCR_HEIGHT, GU_PSM_4444);

    sceGuInit();

    sceGuStart(GU_DIRECT, list);
    sceGuDrawBuffer(GU_PSM_8888, fbp0, PSP_BUF_WIDTH);
    sceGuDispBuffer(PSP_SCR_WIDTH, PSP_SCR_HEIGHT, fbp1, PSP_BUF_WIDTH);
    sceGuDepthBuffer(zbp, PSP_BUF_WIDTH);

    sceGuOffset(2048 - (PSP_SCR_WIDTH / 2), 2048 - (PSP_SCR_HEIGHT / 2));
    sceGuViewport(2048, 2048, PSP_SCR_WIDTH, PSP_SCR_HEIGHT);

    sceGuDepthRange(65535, 0);

    sceGuEnable(GU_SCISSOR_TEST);
    sceGuScissor(0, 0, PSP_SCR_WIDTH, PSP_SCR_HEIGHT);

    sceGuEnable(GU_DEPTH_TEST);
    sceGuDepthFunc(GU_GEQUAL);

    sceGuFrontFace(GU_CW);
    sceGuEnable(GU_CULL_FACE);

    sceGuShadeModel(GU_SMOOTH);

    //sceGuEnable(GU_TEXTURE_2D); //????
    sceGuEnable(GU_CLIP_PLANES);

    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);
}

void termGraphics()
{
    sceGuTerm();
}

void startFrame()
{
    sceGuStart(GU_DIRECT, list);
}

void endFrame()
{
    sceGuFinish();
    sceGuSync(0, 0);
    sceDisplayWaitVblankStart();
    sceGuSwapBuffers();
}