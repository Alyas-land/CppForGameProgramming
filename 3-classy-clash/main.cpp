#include <raylib.h>

int main(){
    const int windowWidth{384};
    const int windowHeight{384};

    InitWindow(windowWidth, windowHeight, "Alyas's Top Down");
    Image icon = LoadImage("assets/bush.png");
    SetWindowIcon(icon);
    SetTargetFPS(60);

    // Load tecture
    Texture2D map = LoadTexture("assets/WorldMap.png");
    

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);
        Vector2 mapPos{0.0, 0.0};
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);





        EndDrawing();
    }
    UnloadTexture(map);

    CloseWindow();
}