#include "../common/callbacks.h"
#include "../common/vram.h"
#include "../common/graphics.h"

#include <pspdisplay.h>

#include <pspgu.h>
#include <pspgum.h>

PSP_MODULE_INFO("Cube Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int running = 1;

struct Vertex
{
    float u, v;
    unsigned int color;
    float x,y,z;
};

struct Vertex __attribute__((aligned(16))) cube[12*3] =
{
	{0, 0, 0xff7f0000,-1,-1, 1}, // 0
	{1, 0, 0xff7f0000,-1, 1, 1}, // 4
	{1, 1, 0xff7f0000, 1, 1, 1}, // 5

	{0, 0, 0xff7f0000,-1,-1, 1}, // 0
	{1, 1, 0xff7f0000, 1, 1, 1}, // 5
	{0, 1, 0xff7f0000, 1,-1, 1}, // 1

	{0, 0, 0xff7f0000,-1,-1,-1}, // 3
	{1, 0, 0xff7f0000, 1,-1,-1}, // 2
	{1, 1, 0xff7f0000, 1, 1,-1}, // 6

	{0, 0, 0xff7f0000,-1,-1,-1}, // 3
	{1, 1, 0xff7f0000, 1, 1,-1}, // 6
	{0, 1, 0xff7f0000,-1, 1,-1}, // 7

	{0, 0, 0xff007f00, 1,-1,-1}, // 0
	{1, 0, 0xff007f00, 1,-1, 1}, // 3
	{1, 1, 0xff007f00, 1, 1, 1}, // 7

	{0, 0, 0xff007f00, 1,-1,-1}, // 0
	{1, 1, 0xff007f00, 1, 1, 1}, // 7
	{0, 1, 0xff007f00, 1, 1,-1}, // 4

	{0, 0, 0xff007f00,-1,-1,-1}, // 0
	{1, 0, 0xff007f00,-1, 1,-1}, // 3
	{1, 1, 0xff007f00,-1, 1, 1}, // 7

	{0, 0, 0xff007f00,-1,-1,-1}, // 0
	{1, 1, 0xff007f00,-1, 1, 1}, // 7
	{0, 1, 0xff007f00,-1,-1, 1}, // 4

	{0, 0, 0xff00007f,-1, 1,-1}, // 0
	{1, 0, 0xff00007f, 1, 1,-1}, // 1
	{1, 1, 0xff00007f, 1, 1, 1}, // 2

	{0, 0, 0xff00007f,-1, 1,-1}, // 0
	{1, 1, 0xff00007f, 1, 1, 1}, // 2
	{0, 1, 0xff00007f,-1, 1, 1}, // 3

	{0, 0, 0xff00007f,-1,-1,-1}, // 4
	{1, 0, 0xff00007f,-1,-1, 1}, // 7
	{1, 1, 0xff00007f, 1,-1, 1}, // 6

	{0, 0, 0xff00007f,-1,-1,-1}, // 4
	{1, 1, 0xff00007f, 1,-1, 1}, // 6
	{0, 1, 0xff00007f, 1,-1,-1}, // 5
};

struct Vertex __attribute__((aligned(16))) cube_indexed[8] = 
{
	{0, 0, 0xff7f0000,-1,-1, 1}, // 0
    {0, 1, 0xff7f0000, 1,-1, 1}, // 1
    {1, 0, 0xff7f0000, 1,-1,-1}, // 2
    {0, 0, 0xff7f0000,-1,-1,-1}, // 3
	{1, 0, 0xff7f0000,-1, 1, 1}, // 4
	{1, 1, 0xff7f0000, 1, 1, 1}, // 5
    {1, 1, 0xff7f0000, 1, 1,-1}, // 6
    {0, 1, 0xff7f0000,-1, 1,-1}, // 7
};

unsigned short __attribute__((aligned(16))) indices[12*3] = {
    0, 4, 5, 0, 5, 1, 3, 2, 6, 3, 6, 7, 0, 3, 7, 0, 7, 4, 0, 1, 2, 0, 2, 3, 4, 7, 6, 4, 6, 5
};

int main()
{
    SetupCallbacks();
    pspDebugScreenInit();

    initGraphics();

    int val = 0;

    while (running)
    {
        startFrame();

        //clear screen
    
        sceGuClearColor(0xff554433); // GU_RGBA, GU_ABGR, GU_ARGB, GU_COLOR in pspgu.h is useful
        sceGuClearDepth(0);
        sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

        // setup matrices for cube

        sceGumMatrixMode(GU_PROJECTION);
        sceGumLoadIdentity();
        sceGumPerspective(75.0f, 16.0f/9.0f, 0.5f, 1000.0f);

        sceGumMatrixMode(GU_VIEW);
        sceGumLoadIdentity();

        sceGumMatrixMode(GU_MODEL);
        sceGumLoadIdentity();
        {
                ScePspFVector3 pos = { 0, 0, -3.0f };
                ScePspFVector3 rot = { val * 0.79f * (GU_PI/180.0f), val * 0.98f * (GU_PI/180.0f), val * 1.32f * (GU_PI/180.0f) };
                sceGumTranslate(&pos);
                sceGumRotateXYZ(&rot);
        }

        // setup texture (not implemented)

        // draw cube

        //sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, 0, cube);
        sceGumDrawArray(GU_TRIANGLES, GU_INDEX_16BIT|GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 12*3, indices, cube_indexed);

        endFrame();

        val++;
    }

    termGraphics();

    sceKernelExitGame();
    return 0;
}