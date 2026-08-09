#include <raylib.h>
#include "button.hpp"

int main(){
    // Set screen game size
    int ScreenWidth{1280};
    int ScreenHeight{720};
    InitWindow(ScreenWidth, ScreenHeight, "Axe Game");
    // set fps for game
    SetTargetFPS(60);

    Texture2D background = LoadTexture("assets/explore-the-neon-lit-cyberpunk-city.png");
    // Start button
    Button startButton{
        "assets/start_button.png", // texture
        {640, 240}, // position
        0.45 // scale
    };
    startButton.fixPosition();

    // Option button
    Button optionButton{
        "assets/option_button.png", // texture
        {640, 340}, // position
        0.45 // scale
    };
    optionButton.fixPosition();
    
    // Exit button
    Button exitButton{
        "assets/exit_button.png", // texture
        {640, 440}, // position
        0.45 // scale
    };
    exitButton.fixPosition();
    
    // Music button
    Button musicButton{
        "assets/music_button.png", // texture
        {ScreenWidth-50, 50}, // position
        0.15 // scale
    };
    musicButton.fixPosition();
    

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(background, {0, 0}, 0, 0.80, WHITE);
        startButton.draw();
        optionButton.draw();
        exitButton.draw();
        musicButton.draw();
        DrawText("Developed By Alyas", 25, (ScreenHeight - 35), 20, ORANGE);





        EndDrawing();

    }
    CloseWindow();
}