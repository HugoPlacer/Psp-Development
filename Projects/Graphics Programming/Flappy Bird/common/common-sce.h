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

typedef struct
{
    void *data;
    u16 *indices;
    u32 index_count;
} Mesh;

typedef struct
{
    float x, y;
    float rot;
    float sx, sy;

    int layer;

    Mesh *mesh;
    Texture *tex;
} Sprite;

typedef struct
{
    float x, y;
    float rot;
} Camera2D;

void reset_transform(float x, float y, float z);
Texture *load_texture(const char *filename, const int flip, const int vram);
void bind_texture(Texture* tex);

Mesh *create_mesh(u32 vcount, u32 index_count);
void draw_mesh(Mesh *mesh);
void destroy_mesh(Mesh *mesh);

Vertex create_vert(float u, float v, unsigned int color, float x, float y, float z);

Sprite *create_sprite(float x, float y, float sx, float sy, Texture *tex);
void draw_sprite(Sprite *sprite);
void destroy_sprite(Sprite *sprite);

void apply_camera(const Camera2D *cam);

unsigned int getMemorySize(unsigned int width, unsigned int height, unsigned int psm);
void* getStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm);
void* getStaticVramTexture(unsigned int width, unsigned int height, unsigned int psm);

void initGraphics(void* list);
void startFrame(void* list);
void endFrame();
void termGraphics();

#endif