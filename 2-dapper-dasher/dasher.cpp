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
    // Initialize game screen
    InitWindow(ScreenWidth, ScreenHeight, "Dapper Dasher");
    SetTargetFPS(60);
    
    // Acceleration due to gravity
    float gravity{1.0f};
    float jumpVel{15.0f};
    bool isGrounded{false};
    float velocity{0.0f};

    // Sprite dimensions
    Texture2D scarfy = LoadTexture("assets/scarfy.png");
    Rectangle* scarfyRec;
    scarfyRec->height = scarfy.height;
    scarfyRec->width = scarfy.width;
    scarfyRec->x = 0; 
    scarfyRec->y = 0; 
    Vector2* scarfyPos;
    scarfyPos->x = (ScreenWidth - scarfyRec->width)/2;
    scarfyPos->y = ScreenHeight - scarfyRec->height;

    float velocity{0.0f};

    

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);
    
        // Check object on the ground
        if (scarfyPos->y >= (ScreenHeight - scarfyRec->height)){
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
        scarfyPos->y += velocity;
        DrawTextureRec(scarfy, *scarfyRec, *scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();

}
