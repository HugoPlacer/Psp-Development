#ifndef COMMON_SCE_H
#define COMMON_SCE_H

// Define PSP Width / Height
#define PSP_BUF_WIDTH (512)
#define PSP_SCR_WIDTH (480)
#define PSP_SCR_HEIGHT (272)

typedef struct
{
    float u, v;
	unsigned int color;
	float x, y, z;
} Vertex;

typedef struct {
    unsigned int width, height;
    unsigned int pW, pH;
    void* data;
}Texture;

void reset_transform(float x, float y, float z);
Texture* load_texture(const char* filename, const int flip, const int vram);
void bind_texture(Texture* tex);

unsigned int getMemorySize(unsigned int width, unsigned int height, unsigned int psm);
void* getStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm);
void* getStaticVramTexture(unsigned int width, unsigned int height, unsigned int psm);

void initGraphics(void* list);
void startFrame(void* list);
void endFrame();
void termGraphics();

#endif