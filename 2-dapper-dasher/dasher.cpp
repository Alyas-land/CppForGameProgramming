/*
    Dapper Dasher Created By Alyas 
    Library Used: Raylib
    Version: 1.0
*/
#include <raylib.h>
#include "button.hpp"

enum class GameState{
    MENU,
    PLAYING,
    EXIT
};

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
void SpawnNebulae(AnimData nebulaArray[], int numOfNebula, Texture2D nebula, int ScreenHeight, int ScreenWidth, float& finishLn);

int main(){

    // Set screen game size
    const int ScreenWidth{800};
    const int ScreenHeight{600};
    // Initialize game screen
    InitWindow(ScreenWidth, ScreenHeight, "Dapper Dasher");
    SetTargetFPS(60);

    // Initialize game state
    GameState state = GameState::MENU;
    /*
        Menu section
    */
    Texture2D backgroundMenu = LoadTexture("assets/explore-the-neon-lit-cyberpunk-city.png");
    // Start button
    Button startButton{
        "assets/start_button.png", // texture
        {ScreenWidth/2, (ScreenHeight/2) - 80}, // position
        0.30 // scale
    };
    startButton.fixPosition();

    // Option button
    Button optionButton{
        "assets/option_button.png", // texture
        {ScreenWidth/2, (ScreenHeight/2)}, // position
        0.30 // scale
    };
    optionButton.fixPosition();
    
    // Exit button
    Button exitButton{
        "assets/exit_button.png", // texture
        {ScreenWidth/2, (ScreenHeight/2) + 80}, // position
        0.30 // scale
    };
    exitButton.fixPosition();
    bool exit{false};
    
    // Music button
    Button musicButton{
        "assets/music_button.png", // texture
        {ScreenWidth-50, 50}, // position
        0.10 // scale
    };
    musicButton.fixPosition();

    const char developer[19] = "Developed By Alyas";
    const char github[22] = "GitHub.com/Alyas-Land";
    const char version[14] = "Version 1.0.0";
    const char gameOver[15] = "Game Over!";
    const char winner[15] = "You Win!";
    int framesCounter = 0;
    int framesCounterGameOver = 0;
    int framesCounterWinner = 0;
    
    // Initialize audio device
    InitAudioDevice();
    Music music = LoadMusicStream("assets/Edgerunners-YouCan'tRunFroMeInspired.mp3");
    if (!IsMusicValid(music)){ TraceLog(LOG_ERROR, "Failed to load music!"); }
    else {TraceLog(LOG_INFO, "Music loaded successfully!"); }
    PlayMusicStream(music);
     bool pause = false;
    
    
    // Acceleration due to gravity
    float gravity{1'000.0f};
    float jumpVel{-650.0f};
    bool isGrounded{false};


    // Initialize background
    Texture2D background = LoadTexture("assets/far-buildings.png");
    float moveBgX{};
    float moveBgX2{};

    // Initialize midground and foreground
    Texture2D midground = LoadTexture("assets/back-buildings.png");
    float midMoveBgX{};
    float midMoveBgX2{};
    Texture2D foreground = LoadTexture("assets/foreground.png");
    float foreMoveBgX{};

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
        1.0f/13.0f, // updateAnim
        0 // frame
    };
    bool collision{};

    // Nebula variables
    Texture2D nebula = LoadTexture("assets/12_nebula_spritesheet.png");
    const int numOfNebula{10};
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

    float finishLine {};
    SpawnNebulae(nebulaArray, numOfNebula, nebula, ScreenHeight, ScreenWidth, finishLine);
    
    

    
    while(!WindowShouldClose() && !exit){
        // Update music buffer
        UpdateMusicStream(music);
        if (state == GameState::MENU){
            // menu update
            Vector2 mousePosition = GetMousePosition();
            bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

            if (startButton.isPressed(mousePosition, mousePressed)){
                state = GameState::PLAYING;
            }
            else if (optionButton.isPressed(mousePosition, mousePressed)){
                // option state
            }
            else if (exitButton.isPressed(mousePosition, mousePressed)){
                state = GameState::EXIT;
            }
            else if (musicButton.isPressed(mousePosition, mousePressed)){
                pause = !pause;
                if(pause) {PauseMusicStream(music);}
                else {ResumeMusicStream(music);}
            }
            // for developer text
            framesCounter += 2;

            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTextureEx(backgroundMenu, {0, 0}, 0, 0.80, WHITE);
            startButton.draw();
            optionButton.draw();
            exitButton.draw();
            musicButton.draw();
            // DrawText("Developed By Alyas", 15, (ScreenHeight - 25), 20, ORANGE);
            DrawText(TextSubtext(developer, 0, framesCounter/10), 15, (ScreenHeight - 60), 20, ORANGE);
            DrawText(TextSubtext(github, 0, framesCounter/10), 15, (ScreenHeight - 25), 20, WHITE);
            DrawText(TextSubtext(version, 0, framesCounter/10), (ScreenWidth - 140), (ScreenHeight - 25), 20, ORANGE);
            EndDrawing();
        }
        else if (state == GameState::PLAYING){
            const float deltaTime = GetFrameTime();
            BeginDrawing();
            ClearBackground(RAYWHITE);
            // background
            if (moveBgX <= -background.width * 3.2){
                moveBgX = 0.0;
            }
            moveBgX -= 25 * deltaTime;
            Vector2 bgPosition {moveBgX, 0.0};
            DrawTextureEx(background, bgPosition, 0.0, 3.2, WHITE);
            Vector2 tempBgPosition {moveBgX + (background.width * 3.2), 0.0};
            DrawTextureEx(background, tempBgPosition, 0.0, 3.2, WHITE);
    
            // midground and foreground
            if (midMoveBgX <= -midground.width * 3.2){
                midMoveBgX = 0.0;
            }
            if (foreMoveBgX <= -foreground.width * 3.2){
                foreMoveBgX = 0.0;
            }
            midMoveBgX -= 40.0 * deltaTime;
            Vector2 midPosition {midMoveBgX, 0.0};
            DrawTextureEx(midground, midPosition, 0.0, 3.2, WHITE);
            Vector2 tempMidPosition {midMoveBgX + (midground.width * 3.2), 0.0};
            DrawTextureEx(midground, tempMidPosition, 0.0, 3.2, WHITE);
    
            foreMoveBgX -= 100.0 * deltaTime;
            Vector2 forePosition {foreMoveBgX, 0.0};
            DrawTextureEx(foreground, forePosition, 0.0, 3.2, WHITE);
            Vector2 tempForePosition {foreMoveBgX + (foreground.width * 3.2), 0.0};
            DrawTextureEx(foreground, tempForePosition, 0.0, 3.2, WHITE);
    
            // music button
            Vector2 mousePosition = GetMousePosition();
            bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
            musicButton.draw();
            if (musicButton.isPressed(mousePosition, mousePressed)){
                pause = !pause;
                if(pause) {PauseMusicStream(music);}
                else {ResumeMusicStream(music);}
            }
            
    
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

            // Update finish line
            finishLine += nebulaArray[numOfNebula - 1].velocity * deltaTime;

            //Update nebulae animation
            for (int i=0; i<numOfNebula; i++){
                // update data for each nebula by pass to UpdateAnimation function
                nebulaArray[i] = UpdateAnimation(nebulaArray[i], deltaTime, 8);
                }
            
            
            // Now, nothing ...
            //UpdateAnimation(nebulaArray, numOfNebula, deltaTime);
    
            for (AnimData nebula: nebulaArray){
                float pad{40};
                Rectangle nebRec{
                    nebula.pos.x + pad,
                    nebula.pos.y + pad,
                    nebula.rec.width - 2 * pad,
                    nebula.rec.height - 2 * pad
                };
                Rectangle scarfyRec{
                    scarfyDetail.pos.x,
                    scarfyDetail.pos.y,
                    scarfyDetail.rec.width,
                    scarfyDetail.rec.height,
                };
                if (CheckCollisionRecs(nebRec, scarfyRec)){
                    collision = true;
                }
            }

            if (collision){
                // Game Over
                framesCounterGameOver++;
                DrawText(TextSubtext(gameOver, 0, framesCounterGameOver/10), (ScreenWidth/2 - 200), (ScreenHeight/2), 70, RED);
            }
            else if (scarfyDetail.pos.x >= finishLine){
                framesCounterWinner++;
                DrawText(TextSubtext(winner, 0, framesCounterWinner/10), (ScreenWidth/2 - 170), (ScreenHeight/2), 80, GREEN);
            }
            else{
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
            }
    
            EndDrawing();
        }
        else if (state == GameState::EXIT){
            exit = true;
        }
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
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

void SpawnNebulae(AnimData nebulaArray[], int numOfNebula, Texture2D nebula, int ScreenHeight, int ScreenWidth, float& finishLn){
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
    
       nebulaArray[i].velocity = -200.0f;
       nebulaArray[i].frame = 0;
       nebulaArray[i].runningAnim = 0.0;
       nebulaArray[i].updateAnim = 0.0;
        
       nebulaArray[i].pos.x = ScreenWidth + i * 450; 
    }
    // Initial FinishLine
    finishLn = nebulaArray[numOfNebula - 1].pos.x + 200;
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