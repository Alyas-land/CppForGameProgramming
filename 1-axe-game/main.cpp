#include "raylib.h"


int main(){
    // Set screen game size
    int ScreenWidth{1280};
    int ScreenHeight{720};
    InitWindow(ScreenWidth, ScreenHeight, "Axe Game");
    // set fps for game
    SetTargetFPS(60);

    // Circle coordinates
    Vector2 ballPosition = {ScreenWidth/2, ScreenHeight/2};
    // Axe coordinates 
    Vector2 rectanglePosition = {300 ,0};
    Vector2 rectangleSize = {50, 50};

    // loop game
    while(!WindowShouldClose()){
        /*
        Input logic and updating script 
        */
        if (IsKeyDown(KEY_A) && ballPosition.x > 0)
            ballPosition.x -= 3.5f;
        if (IsKeyDown(KEY_D) && ballPosition.x < ScreenWidth)
            ballPosition.x += 3.5f;
        if (IsKeyDown(KEY_W) && ballPosition.y > 0)
            ballPosition.y -= 3.5f;
        if (IsKeyDown(KEY_S) && ballPosition.y < ScreenHeight)
        ballPosition.y += 3.5f;
        
        /*
        Axe logic
        
        */

        // Begin game logic
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hi body", 640, 600, 20, LIGHTGRAY);
        DrawCircleV(ballPosition, 50.0f, BLUE);
        DrawRectangleV(rectanglePosition, rectangleSize, RED);
        

        // End game logic
        EndDrawing();
    }
}

