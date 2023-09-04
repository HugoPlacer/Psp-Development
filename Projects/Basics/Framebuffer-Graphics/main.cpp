//This aproach uses software rendering

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include "gfx.h"

PSP_MODULE_INFO("FrameBuffer Graphics", 0, 1, 0);

int exit_callback(int arg1, int arg2, void *commond)
{
    sceKernelExitGame();
    return 0;
}

int callbackThread(SceSize args, void *argp)
{
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);

    sceKernelSleepThreadCB();
    return 0;
}

void setupCallbacks()
{
    int thid = sceKernelCreateThread("update_thread", callbackThread, 0x11, 0xFA0, 0, NULL);
    if (thid >= 0)
    {
        sceKernelStartThread(thid, 0, NULL);
    }
}

int main()
{
    setupCallbacks();
    GFX_init();

    while(true){
        GFX_clear(0xFFFFCA82);

        GFX_draw_rect(10, 10, 30, 30, 0xFF00FFFF);

        GFX_swap_buffers();
        sceDisplayWaitVblankStart();
    }
}