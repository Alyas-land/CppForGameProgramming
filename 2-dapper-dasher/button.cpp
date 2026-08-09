#include "button.hpp"

Button::Button(const char *imagePath, Vector2 imagePosition, float scale)
{
    // texture = LoadTexture(imagePath);
    Image image = LoadImage(imagePath);
    int orginalWidth = image.width;
    int orginalHeight = image.height;

    int newWidth = static_cast<int>(orginalWidth * scale);
    int newHeight = static_cast<int>(orginalHeight * scale);
    
    ImageResize(&image, newWidth, newHeight);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);

    position = imagePosition;
}

Button::~Button()
{
    UnloadTexture(texture);
}

void Button::draw()
{
    DrawTextureV(texture, position, WHITE);
}

void Button::fixPosition()
{
    position.x -= (texture.width/2);
    position.y -= (texture.height/2);
    
}

bool Button::isPressed(Vector2 mousePosition, bool mousePressed)
{
    Rectangle rect = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    if (CheckCollisionPointRec(mousePosition, rect) && mousePressed){
        return true;
    }
    return false;
}
