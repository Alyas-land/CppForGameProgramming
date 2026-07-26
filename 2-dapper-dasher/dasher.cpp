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
    float gravity{1'000.0f};
    float jumpVel{-650.0f};
    bool isGrounded{false};
    float velocity{0.0f};

    // Scarf variable(dimensions)
    Texture2D scarfy = LoadTexture("assets/scarfy.png");
    Rectangle* scarfyRec = new Rectangle();
    scarfyRec->height = scarfy.height;
    scarfyRec->width = scarfy.width/6;
    scarfyRec->x = 0; 
    scarfyRec->y = 0; 
    Vector2* scarfyPos = new Vector2();
    scarfyPos->x = (ScreenWidth - scarfyRec->width)/2;
    scarfyPos->y = ScreenHeight - scarfyRec->height;

    // Nebula variables
    Texture2D nebula = LoadTexture("assets/12_nebula_spritesheet.png");
    Rectangle* nebRec = new Rectangle{
        0, // x position
        0, // y position
        nebula.height/8, // Height
        nebula.width/8   // Width
    };
    float nebVel{-600.0f};

    Vector2* nebPos = new Vector2{
        ScreenWidth, // x
        ScreenHeight - nebRec->height // y
    };
    
    int nebVelocity{};

    // Frame animation
    int frame{0};
    float updateTimeAnim{1.0f/16.0f};
    float runningTimeAnim{0};

    
    while(!WindowShouldClose()){
        const float deltaTime = GetFrameTime();

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
            velocity += gravity * deltaTime;
        }
        // Check if space key is pressed and rectangle is on the ground
        if(IsKeyDown(KEY_SPACE) && isGrounded){
            velocity += jumpVel;
            isGrounded = false;
        }
        // Update nebula position
        nebPos->x += nebVel * deltaTime;

        // Update scarfy position
        scarfyPos->y += velocity * deltaTime;
        
        // Update running time
        runningTimeAnim += deltaTime;
        if (runningTimeAnim >= updateTimeAnim){
            // Check scarfy on gound or on air and continue or pause animation frame
            if (!isGrounded) {
                if (scarfyRec->x <= (3 * scarfyRec->width)) scarfyRec->x = 0;
                scarfyRec->x = scarfyRec->x = 5;
            }
            else{
                runningTimeAnim = 0.0f;
                scarfyRec->x = (frame * scarfyRec->width);
                frame++;
                if(frame > 5) frame=0;
                
            }
        }
        
        // Draw nebula
        DrawTextureRec(nebula, *nebRec, *nebPos, WHITE);
        // Draw Scarfy
        DrawTextureRec(scarfy, *scarfyRec, *scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    delete scarfyPos, scarfyRec;
    delete nebRec, nebPos;
    CloseWindow();

}
