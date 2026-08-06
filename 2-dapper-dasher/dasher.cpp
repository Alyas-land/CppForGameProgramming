/*
    Dapper Dasher Created By Alyas 
    Library Used: Raylib
    Version: 1.0
*/

#include <raylib.h>

struct AnimData
{
    /* data */
    Texture2D object;
    Rectangle rec;
    Vector2 pos;
    float velocity;
    float runningAnim;
    float updateAnim;
    int frame;
};


int main(){

    // Set screen game size
    const int ScreenWidth{800};
    const int ScreenHeight{600};
    // Initialize game screen
    InitWindow(ScreenWidth, ScreenHeight, "Dapper Dasher");
    SetTargetFPS(60);
    
    // Initialize audio device
    InitAudioDevice();
    Music music = LoadMusicStream("assets/TarHawk.mp3");
    if (!IsMusicValid(music)){ TraceLog(LOG_ERROR, "Failed to load music!"); }
    else {TraceLog(LOG_INFO, "Music loaded successfully!"); }
    PlayMusicStream(music);
    
    
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
    AnimData* nebulaa = new AnimData{};
    nebulaa->object = LoadTexture("assets/12_nebula_spritesheet.png");
    nebulaa->rec = {
        0, // x position
        0, // y position
        static_cast<float>(nebulaa->object.width/8), // Width
        static_cast<float>(nebulaa->object.height/8), // Height
        };
    nebulaa->pos = {
        ScreenWidth, // x
        ScreenHeight - nebulaa->rec.height // y
    };
    nebulaa->velocity = -600.0f;
    nebulaa->runningAnim = 0;
    nebulaa->updateAnim = 1.0f/ 30.0f;
    nebulaa->frame = 0;

    AnimData nebulaArray[3] {};

    for (int i=0; i<4; i++){
        nebulaArray[i].object = LoadTexture("assets/12_nebula_spritesheet.png");
        /*
        Initialize rectangle
        */
        nebulaArray[i].rec.width = static_cast<float>(nebulaa->object.width/8);
        nebulaArray[i].rec.height = static_cast<float>(nebulaa->object.width/8);
        nebulaArray[i].rec.x = 0.0;
        nebulaArray[i].rec.y = 0.0;
        /*
        Initialize position
        */
       nebulaArray[i].pos.y = ScreenHeight - nebulaa->rec.height;
        
    }



    // Scarfy frame animation
    int frame{0};
    float updateTimeAnim{1.0f/16.0f};
    float runningTimeAnim{0};


    
    while(!WindowShouldClose()){
        const float deltaTime = GetFrameTime();

        // Update music buffer
        UpdateMusicStream(music);

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
        
        // Update nebula position6
        nebulaa->pos.x += nebulaa->velocity * deltaTime;

        // Update scarfy position
        scarfyPos->y += velocity * deltaTime;
        
        // Update running time
        runningTimeAnim += deltaTime;
        if (runningTimeAnim >= updateTimeAnim){
            // Check scarfy on gound or on air and continue or pause animation frame
            if (!isGrounded) {
                scarfyRec->x = 5 * scarfyRec->width ;
            }
            else{
                runningTimeAnim = 0.0f;
                scarfyRec->x = (frame * scarfyRec->width);
                frame++;
                if(frame > 5) frame=0;
                
            }
        }

        // Update nebula 2 running time
        nebulaa->runningAnim += deltaTime;
        if(nebulaa->runningAnim >= nebulaa->updateAnim){
            nebulaa->runningAnim = 0;
            nebulaa->rec.x = (nebulaa->frame * nebulaa->rec.width);
            nebulaa->frame++;
            if (nebulaa->frame >= 8) nebulaa->frame = 0;
        }
        
        
        // Draw nebula
        DrawTextureRec(nebulaa->object, nebulaa->rec, nebulaa->pos, RED);
        // Draw Scarfy
        DrawTextureRec(scarfy, *scarfyRec, *scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    // UnloadTexture(nebula);
    // Unload music stream buffers from RAM
    UnloadMusicStream(music);
    // Close audio device 
    CloseAudioDevice();
    delete scarfyPos, scarfyRec;
    // delete nebRec, nebPos;
    CloseWindow();

}
