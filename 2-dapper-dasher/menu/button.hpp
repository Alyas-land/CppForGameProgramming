#pragma once
#include <raylib.h>

class Button{
    public:
        Button(const char* imagePath, Vector2 imagePosition, float scale);
        ~Button();
        void draw();
        bool isPressed(Vector2 mousePosition, bool mousePressed);

    private:
        Texture2D texture;
        Vector2 position;
}