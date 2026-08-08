#include <raylib.h>

int main(){
    // Set screen game size
    int ScreenWidth{1280};
    int ScreenHeight{720};
    InitWindow(ScreenWidth, ScreenHeight, "Axe Game");
    // set fps for game
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();






        EndDrawing();

    }
    CloseWindow();
}