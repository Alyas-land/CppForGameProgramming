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
    float circleRadius{50.0};
    // Initialize the ball edge
    int leftCircleX = ballPosition.x - circleRadius;
    int rightCircleX = ballPosition.x + circleRadius;
    int topCircleY = ballPosition.y - circleRadius;
    int bottomCircleY = ballPosition.y + circleRadius;
    
    // Axe coordinates 
    Vector2 rectanglePosition = {300 ,0};
    Vector2 rectangleSize = {50, 50};
    int direction{10};
    // Initialize the rectangle edge
    int leftRectangleX = rectanglePosition.x;
    int rightRectangleX = rectanglePosition.x + rectangleSize.x;
    int topRectangleY = rectanglePosition.y;
    int bottomRectangleY = rectanglePosition.y + rectangleSize.y;

    // Logic game paramters
    bool collisionWithAxe = (leftRectangleX <= rightCircleX) &&
        (rightRectangleX >= leftCircleX) &&
        (topRectangleY <= bottomCircleY) &&
        (bottomRectangleY >= topCircleY);

    // loop game
    while(!WindowShouldClose()){
        // Begin game logic
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (
        ){
            collisionWithAxe = true;
        }

        if (collisionWithAxe){
           DrawText("Game Over!", (ScreenWidth/2 - 100), ScreenHeight/2, 40, RED); 
       }

       else{

           /*
           Input logic and updating script 
           */
           if (IsKeyDown(KEY_A) && ballPosition.x > 0)
               ballPosition.x -= 7.0f;
           if (IsKeyDown(KEY_D) && ballPosition.x < ScreenWidth)
               ballPosition.x += 7.0f;
           if (IsKeyDown(KEY_W) && ballPosition.y > 0)
               ballPosition.y -= 7.0f;
           if (IsKeyDown(KEY_S) && ballPosition.y < ScreenHeight)
               ballPosition.y += 7.0f;
           
           /*
           Axe logic
           */
           rectanglePosition.y += direction;
           if (rectanglePosition.y > ScreenHeight || rectanglePosition.y < 0){
               direction = -direction;  
           }
   
           DrawText("Hi body", 640, 600, 20, LIGHTGRAY);
           DrawCircleV(ballPosition, circleRadius, BLUE);
           DrawRectangleV(rectanglePosition, rectangleSize, RED);
              // End game logic
        }
        EndDrawing();
    }
}

