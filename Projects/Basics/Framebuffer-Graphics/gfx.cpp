#include "gfx.h"
#include <pspge.h>
#include <pspdisplay.h>
#include <psputils.h>

uint32_t* draw_buffer;
uint32_t* disp_buffer;

void GFX_init()
{
    draw_buffer = (uint32_t*)sceGeEdramGetAddr();
    disp_buffer = (uint32_t*)sceGeEdramGetAddr() + (272 * 512 * sizeof(uint32_t));

    sceDisplaySetMode(0, 480, 272);
    sceDisplaySetFrameBuf(disp_buffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, 1);
}
void GFX_clear(uint32_t color)
{
    for(int i = 0;i < 512 * 272; i++){
        draw_buffer[i] = color;
    }
}
void GFX_swap_buffers()
{
    uint32_t* temp = disp_buffer;
    disp_buffer = draw_buffer;
    draw_buffer = temp;

    sceKernelDcacheWritebackInvalidateAll();
    sceDisplaySetFrameBuf(disp_buffer, 512, PSP_DISPLAY_PIXEL_FORMAT_8888, PSP_DISPLAY_SETBUF_NEXTFRAME);
}
void GFX_draw_rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, uint32_t color)
{
    if(x > 480){
        x = 480;
    }
    if(y > 480){
        y = 480;
    }

    if(x + w > 480){
        w = 480 - x;
    }

    if(y + h > 272){
        h = 272 - y;
    }

    int off = x + (y * 512);
    for(int y1 = 0; y1 < h; y1++){
        for(int x1 = 0; x1 < w; x1++){
            draw_buffer[x1 + off + y1 * 512] = color;
        }
    }
}