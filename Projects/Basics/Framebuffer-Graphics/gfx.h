#include <stdint.h>

void GFX_init();
void GFX_clear(uint32_t color);
void GFX_swap_buffers();
void GFX_draw_rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, uint32_t color);