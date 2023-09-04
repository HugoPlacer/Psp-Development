#include "vram.h"

#include <pspgu.h>
#include <pspge.h>

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