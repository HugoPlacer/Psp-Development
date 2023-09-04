#ifndef graphics_h
#define graphics_h

#define PSP_BUF_WIDTH (512)
#define PSP_SCR_WIDTH (480)
#define PSP_SCR_HEIGHT (272)

static unsigned int __attribute__((aligned(16))) list[262144];

void initGraphics();

void termGraphics();

void startFrame();

void endFrame();

#endif