#pragma once

#include <inttypes.h>

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
bool drawSprite(int row, int col, const std::vector<uint8_t>& sprite_pixels,
                PixelBuffer<Color>& display);
