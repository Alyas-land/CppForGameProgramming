/*
    Dapper Dasher Created By Alyas 
    Library Used: Raylib
    Version: 1.0
*/

#include <raylib.h>



int main(){

    // Set screen game size
    int ScreenWidth{800};
    int ScreenHeight{600};
    InitWindow(ScreenWidth, ScreenHeight, "Dapper Dasher");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);




        EndDrawing();
    }
}
