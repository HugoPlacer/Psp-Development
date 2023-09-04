#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <fstream>
#include <iostream>
#include <string>

PSP_MODULE_INFO("File Operations", 0, 1, 0);

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

    std::ofstream file("test.txt");
    file << "1 2 3! Hello PSP!" << std::endl;
    file.close();

    std::ifstream file2("test.txt");
    std::string str;
    std::getline(file2, str);
    file2.close();


    pspDebugScreenInit();
    pspDebugScreenPrintf(str.c_str());

    while(1){
        
    }
}