#include "display.h"

Bitmap drawSprite(Bitmap&& bitmap) {
  (void)bitmap;
  return {};
}

Bitmap initializeBitmap(int width, int height, ColorT color) {
  return Bitmap{width, height, std::vector<ColorT>(width * height, color)};
}
