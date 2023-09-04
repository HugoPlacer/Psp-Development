#ifndef common_vram_h
#define common_vram_h

void *getStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm);

void *getStaticVramTexture(unsigned int width, unsigned int height, unsigned int psm);

#endif