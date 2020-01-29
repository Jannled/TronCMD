#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define BITMAP_WIDTH  128
#define BITMAP_HEIGHT 40

typedef uint16_t Bitmap[BITMAP_HEIGHT][BITMAP_WIDTH/16];

void setBit(Bitmap bm, size_t x, size_t y);
bool getBit(Bitmap bm, size_t x, size_t y);

void clearBitmap(Bitmap bm);

#endif // BITMAP_H