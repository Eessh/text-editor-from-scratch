#pragma once

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Rectangle.hpp"

class TextBlock {
  public:
  std::string text;
  Rectangle* boundingRect;

  TextBlock(const std::string& s): text(s), boundingRect(nullptr) {}

  void render(
    const float& xCoord, const float& yCoord,
    const float& horizontalPadding, const float& verticalPadding,
    ALLEGRO_FONT* font
  );
};