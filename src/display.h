#pragma once

#include "bitmap.h"

/*         64pixels - x                          */
/* -------------------------------               */
/* |(0,0)                        |  32 pixels -y */
/* |                             |               */
/* |                      (63,31)|               */
/* -------------------------------               */
void drawSprite(Bitmap& bitmap);

Bitmap initializeBitmap(int width, int height, ColorT color);
