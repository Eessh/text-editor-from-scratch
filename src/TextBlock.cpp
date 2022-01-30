#include "../include/TextBlock.hpp"

void TextBlock::render(
  const float& xCoord, const float& yCoord,
  const float& horizontalPadding, const float& verticalPadding,
  ALLEGRO_FONT* font
) {
  float fontWidth = al_get_text_width(font, text.c_str());
  float fontHeight = al_get_font_line_height(font);
  boundingRect = new Rectangle(fontWidth+2*horizontalPadding, fontHeight+2*verticalPadding);
  boundingRect->render(xCoord, yCoord, al_map_rgb(50, 50, 50));
  al_draw_text(font, al_map_rgb(255, 255, 255), xCoord+horizontalPadding, yCoord+verticalPadding, 0, text.c_str());
  return;
}