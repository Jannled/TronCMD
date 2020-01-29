#include "bitmap.h"

void setBit(Bitmap bm, size_t x, size_t y)
{
    bm[y][x/16] |= (1 << (x%16));
}

bool getBit(Bitmap bm, size_t x, size_t y)
{
    return bm[y][x/16] & (1 << (x%16));
}

void clearBitmap(Bitmap bm)
{
    for(int y=0; y<BITMAP_HEIGHT; y++)
        for(int x=0; x<BITMAP_WIDTH; x++)
            bm[y][x/16] &= ~(1 << (x%16));
}