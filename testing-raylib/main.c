#include <raylib.h>

void MoveBall(Texture2D ball, int* x, int* y);

int main(){
  const int WINDOW_HEIGHT = 480;
  const int WINDOW_WIDTH = 720;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib testing");
  SetTargetFPS(60);
  int x = 100;
  int y = 50;

  while(!WindowShouldClose()){
    Texture2D ball1 = LoadTexture("ball1.png");
    BeginDrawing();

    ClearBackground(BLACK);

    MoveBall(ball1, &x, &y);

    EndDrawing();
  }

  CloseWindow();
}

void MoveBall(Texture2D ball, int* x, int* y){
  *x += 1;
  *y += 1;
  DrawTexture(ball, *x, *y, WHITE);
}
