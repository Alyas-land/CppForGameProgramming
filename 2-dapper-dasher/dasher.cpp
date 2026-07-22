/*
    Dapper Dasher Created By Alyas 
    Library Used: Raylib
    Version: 1.0
*/

#include <raylib.h>



int main(){

    // Set screen game size
    const int ScreenWidth{800};
    const int ScreenHeight{600};

    // Acceleration due to gravity
    float gravity{1.0f};
    float jumpVel{15.0f};
    bool isGrounded{false};


    // Rectangle dimensions
    Vector2 rectangleSize{50.0f, 80.0f};

    float posY{ScreenHeight - rectangleSize.y};
    float velocity{0.0f};

    InitWindow(ScreenWidth, ScreenHeight, "Dapper Dasher");
    SetTargetFPS(60);

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);
    
        // Check object on the ground
        if (posY >= (ScreenHeight - rectangleSize.y)){
            //rectanglr on the ground
            velocity = 0.0f;
            isGrounded = true;
        }
        else {
            // Rectangle on the air
            velocity += gravity;
        }
        // Check if space key is pressed and rectangle is on the ground
        if(IsKeyDown(KEY_SPACE) && isGrounded){
            velocity -= 30.0f;
            isGrounded = false;
        }
        // Update position
        posY += velocity;


        DrawRectangleV({ScreenWidth/2, posY}, rectangleSize, BLUE);



        EndDrawing();
    }
}
