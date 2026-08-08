/*
    Dapper Dasher Created By Alyas 
    Library Used: Raylib
    Version: 1.0
*/

#include <raylib.h>
#include <cstdlib>




struct AnimData
{
    /* data */
    Rectangle rec;
    Vector2 pos;
    float velocity;
    float runningAnim;
    float updateAnim;
    int frame;
};

// Initial functions
bool checkOnGrounded(AnimData PlayerData, int WindowHeight);
void UpdateAnimation(AnimData nebulaArray[], int numOfNebula, float deltaTime);
AnimData UpdateAnimation(AnimData data, float deltaTime, int maxFrame);
void SpawnNebulae(AnimData nebulaArray[], int numOfNebula, Texture2D nebula, int ScreenHeight, int ScreenWidth);

int main(){

    // Set screen game size
    const int ScreenWidth{800};
    const int ScreenHeight{600};
    // Initialize game screen
    InitWindow(ScreenWidth, ScreenHeight, "Dapper Dasher");
    SetTargetFPS(60);
    
    // Initialize audio device
    InitAudioDevice();
    Music music = LoadMusicStream("assets/Edgerunners-YouCan'tRunFroMeInspired.mp3");
    if (!IsMusicValid(music)){ TraceLog(LOG_ERROR, "Failed to load music!"); }
    else {TraceLog(LOG_INFO, "Music loaded successfully!"); }
    PlayMusicStream(music);
    
    
    // Acceleration due to gravity
    float gravity{1'000.0f};
    float jumpVel{-650.0f};
    bool isGrounded{false};

    // Scarf variable(dimensions)
    Texture2D scarfy = LoadTexture("assets/scarfy.png");
    AnimData scarfyDetail{
        {
            // Rectangle init
            0.0, // x 
            0.0, // y
            scarfy.width/6, // width
            scarfy.height // height
        }, 
        {
            // Position init
            (ScreenWidth - scarfyDetail.rec.width)/2, // x
            ScreenHeight - scarfyDetail.rec.height // y
        },
        0.0, // velocity
        0.0, // runningAnim
        1.0f/16.0f, // updateAnim
        0 // frame
    };

    // Nebula variables
    Texture2D nebula = LoadTexture("assets/12_nebula_spritesheet.png");
    const int numOfNebula{4};
    AnimData nebulaArray[numOfNebula] {};

    // for (int i=0; i<numOfNebula; i++){
    //     /*
    //     Initialize rectangle
    //     */
    //     nebulaArray[i].rec.width = static_cast<float>(nebula.width/8);
    //     nebulaArray[i].rec.height = static_cast<float>(nebula.width/8);
    //     nebulaArray[i].rec.x = 0.0;
    //     nebulaArray[i].rec.y = 0.0;
    //     /*
    //     Initialize position
    //     */
    //    nebulaArray[i].pos.y = ScreenHeight - nebula.height/8;
    
    //    nebulaArray[i].velocity = -600.0f;
    //    nebulaArray[i].frame = 0;
    //    nebulaArray[i].runningAnim = 0.0;
    //    nebulaArray[i].updateAnim = 0.0;
    // }

    // nebulaArray[0].pos.x = ScreenWidth;
    // nebulaArray[1].pos.x = ScreenWidth + 300;
    // nebulaArray[2].pos.x = ScreenWidth + 600;

    SpawnNebulae(nebulaArray, numOfNebula, nebula, ScreenHeight, ScreenWidth);
    
    

    
    while(!WindowShouldClose()){
        const float deltaTime = GetFrameTime();

        // Update music buffer
        UpdateMusicStream(music);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Check object on the ground
        if (checkOnGrounded(scarfyDetail, ScreenHeight)){
            //rectanglr on the ground
            scarfyDetail.velocity = 0.0f;
            isGrounded = true;
        }
        else {
            // Rectangle on the air
            scarfyDetail.velocity += gravity * deltaTime;
        }
        // Check if space key is pressed and rectangle is on the ground
        if(IsKeyDown(KEY_SPACE) && isGrounded){
            scarfyDetail.velocity += jumpVel;
            isGrounded = false;
        }
        
        
        // Update scarfy position
        scarfyDetail.pos.y += scarfyDetail.velocity * deltaTime;
        
        // Update running time scarfy
        if (isGrounded) {
            scarfyDetail = UpdateAnimation(scarfyDetail, deltaTime, 5);
            // Check scarfy on gound or on air and continue or pause animation frame  
        }
        else{
            scarfyDetail.rec.x = 5 * scarfyDetail.rec.width ;
        }
        
        // Update nebula position6
        for (int i=0; i<numOfNebula; i++){
            nebulaArray[i].pos.x += nebulaArray[i].velocity * deltaTime;
        }
        //Update nebulae animation
        for (int i=0; i<numOfNebula; i++){
            // update data for each nebula by pass to UpdateAnimation function
            nebulaArray[i] = UpdateAnimation(nebulaArray[i], deltaTime, 8);
            }
        
        
        // Now, nothing ...
        //UpdateAnimation(nebulaArray, numOfNebula, deltaTime);
        
        
        
        // Draw nebulae
        for (int i=0; i<numOfNebula; i++){
            if (i % 3 == 0){
                 DrawTextureRec(nebula, nebulaArray[i].rec, nebulaArray[i].pos, LIGHTGRAY);
            }
            else if (i % 2 == 0){
                 DrawTextureRec(nebula, nebulaArray[i].rec, nebulaArray[i].pos, ORANGE);
            }
            if (i % 2 != 0){
                 DrawTextureRec(nebula, nebulaArray[i].rec, nebulaArray[i].pos, RED);
            }
        }
        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyDetail.rec, scarfyDetail.pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    // UnloadTexture(nebula);
    // Unload music stream buffers from RAM
    UnloadMusicStream(music);
    // Close audio device 
    CloseAudioDevice();
    // delete nebRec, nebPos;
    CloseWindow();

}

// check player on gounded or not
bool checkOnGrounded(AnimData PlayerData, int WindowHeight){
    return (PlayerData.pos.y >= (WindowHeight - PlayerData.rec.height));
}

void SpawnNebulae(AnimData nebulaArray[], int numOfNebula, Texture2D nebula, int ScreenHeight, int ScreenWidth){
        for (int i=0; i<numOfNebula; i++){
            /*
            Initialize rectangle
            */
            nebulaArray[i].rec.width = static_cast<float>(nebula.width/8);
            nebulaArray[i].rec.height = static_cast<float>(nebula.width/8);
            nebulaArray[i].rec.x = 0.0;
            nebulaArray[i].rec.y = 0.0;
            /*
            Initialize position
            */
           nebulaArray[i].pos.y = ScreenHeight - nebula.height/8;
        
           nebulaArray[i].velocity = -600.0f;
           nebulaArray[i].frame = 0;
           nebulaArray[i].runningAnim = 0.0;
           nebulaArray[i].updateAnim = 0.0;
        }
    
        nebulaArray[0].pos.x = ScreenWidth;
        nebulaArray[1].pos.x = ScreenWidth + 300;
        nebulaArray[2].pos.x = ScreenWidth + 600;        
    }

// update animaion of enemy(nebula) each frame in game loop
void UpdateAnimation(AnimData nebulaArray[], int numOfNebula, float deltaTime){
    for (int i=0; i<numOfNebula; i++){
        nebulaArray[i].runningAnim += deltaTime;
        if (nebulaArray[i].runningAnim >= nebulaArray[i].updateAnim){
            nebulaArray[i].runningAnim = 0;
            nebulaArray[i].rec.x = (nebulaArray[i].frame * nebulaArray[i].rec.width);
            nebulaArray[i].frame++;
            if(nebulaArray[i].frame >= 8) nebulaArray[i].frame = 0;
        }
    }
}

AnimData UpdateAnimation(AnimData data, float deltaTime, int maxFrame){
    data.runningAnim += deltaTime;
    if (data.runningAnim >= data.updateAnim){
        data.runningAnim = 0;
        data.rec.x = (data.frame * data.rec.width);
        data.frame++;
        if(data.frame > maxFrame) data.frame = 0;
    }

    return data;

}