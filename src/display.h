#pragma once

#include "bitmap.h"

struct Sprite
{
    int x;
    int y;
    int width;
    int height;
};

/*         64pixels - x                          */
/* -------------------------------               */
/* |(0,0)                        |  32 pixels -y */
/* |                             |               */
/* |                      (63,31)|               */
/* -------------------------------               */
void drawSprite(const Sprite& sprite, Bitmap& bitmap);
