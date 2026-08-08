#include "button.hpp"

Button::Button(const char *imagePath, Vector2 imagePosition, float scale)
{
    texture = LoadTexture(imagePath);
    position = imagePosition;
}

