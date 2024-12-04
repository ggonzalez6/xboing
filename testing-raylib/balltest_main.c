#include <raylib.h>
#include "ball.h"
//#include "faketypes.h"
const int SCREEN_WIDTH = 582;
const int SCREEN_HEIGHT = 720;

void drawBoundaries();
Ball balls[];

int main(){
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "testing");
  SetTargetFPS(60);
  
  AddANewBall(balls, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, -1, -1);
  InitialiseBall(balls, 0, "ball1.png", 
      (Vector2){balls[0].position.x, balls[0].position.y}, balls[0].radius); 
  while(!WindowShouldClose()){
  BeginDrawing();
  ClearBackground(BLACK);
  drawBoundaries();
  DrawTheBall(balls,0);
  UpdateABall(balls,0);
  EndDrawing();
  }
}

void drawBoundaries(){
  Vector2 topLeftCorner, topRightCorner, bottomLeftCorner, bottomRightCorner;

  topLeftCorner = (Vector2){43.5,70};
  topRightCorner = (Vector2){538.5,70};
  bottomLeftCorner = (Vector2){43.5,650};
  bottomRightCorner = (Vector2){538.5,650};

  DrawLineV(topLeftCorner, topRightCorner, WHITE);
  DrawLineV(topRightCorner, bottomRightCorner, WHITE);
  DrawLineV(bottomRightCorner, bottomLeftCorner, WHITE);
  DrawLineV(bottomLeftCorner, topLeftCorner, WHITE);
}
