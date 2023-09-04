#include "../common/callbacks.h"

#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>

PSP_MODULE_INFO("Context Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#define PSP_BUF_WIDTH (512)
#define PSP_SCR_WIDTH (480)
#define PSP_SCR_HEIGHT (272)

int running = 1;

static unsigned int __attribute__((aligned(16))) list[262144];

static unsigned int getMemorySize(unsigned int width, unsigned int height, unsigned int psm)
{
    unsigned int size = width * height;

    switch (psm)
    {
    case GU_PSM_T4:
        return size / 2;
    case GU_PSM_T8:
        return size;

    case GU_PSM_5650:
    case GU_PSM_5551:
    case GU_PSM_4444:
    case GU_PSM_T16:
        return size * 2;

    case GU_PSM_8888:
    case GU_PSM_T32:
        return size * 4;

    default:
        return 0;
    }
}

void *getStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm)
{
    static unsigned int staticOffset = 0;

    unsigned int memSize = getMemorySize(width, height, psm);

    void *result = (void *)staticOffset;

    staticOffset += memSize;

    return result;
}

void *getStaticVramTexture(unsigned int width, unsigned int height, unsigned int psm)
{
    void *result = getStaticVramBuffer(width, height, psm);
    return (void *)(((unsigned int)result) + ((unsigned int)sceGeEdramGetAddr()));
}

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

    sceGuEnable(GU_TEXTURE_2D);
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

int main()
{

    SetupCallbacks();

    initGraphics();

    while (running)
    {
        startFrame();

        sceGuClearColor(0xFF00FF00); // GU_RGBA, GU_ABGR, GU_ARGB, GU_COLOR in pspgu.h is useful
        sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

        endFrame();
    }

    termGraphics();

    sceKernelExitGame();
    return 0;
}