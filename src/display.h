#pragma once

#include <vector>

#include "color.h"

#include "pixel_buffer.h"

/*      Chip-8 Screen Coordinate Space           */
/*         64pixels - x                          */
/* -------------------------------               */
/* |(0,0)                        |  32 pixels -y */
/* |                             |               */
/* |                      (63,31)|               */
/* -------------------------------               */


/**
 * Draws a sprite on the screen buffer at the provided coordinates
 *
 * returns true if any of the pixels are flipped from set to unset
 */
bool drawSpriteOnScreen(int row, int col, const PixelBuffer<Color>& sprite, PixelBuffer<Color>& screen);
