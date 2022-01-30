#include "../include/Rectangle.hpp"

void Rectangle::render(
  const float& xCoord, const float& yCoord,
  ALLEGRO_COLOR rectColor
) {
  al_draw_filled_rectangle(xCoord, yCoord, xCoord+w, yCoord+h, rectColor);
  return;
}