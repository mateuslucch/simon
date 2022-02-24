#include "raylib.h"
#include <cstdio>

int main()
{

    int windowDimensions[2]{640, 480};

    InitWindow(windowDimensions[0], windowDimensions[1], "Simon");
    int squareSize = 200;
    int gap = 20;
    int xMargin = (windowDimensions[0] - squareSize * 2 - gap) / 2;
    int yMargin = (windowDimensions[1] - squareSize * 2 - gap) / 2;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        ClearBackground(DARKGRAY);
        BeginDrawing();

        DrawRectangle(xMargin, yMargin, squareSize, squareSize, RED);
        DrawRectangle(xMargin, yMargin + squareSize + gap, squareSize, squareSize, YELLOW);
        DrawRectangle(xMargin + squareSize + gap, yMargin, squareSize, squareSize, GREEN);
        DrawRectangle(xMargin + squareSize + gap, yMargin + squareSize + gap, squareSize, squareSize, BLUE);

        if (IsKeyPressed(KEY_KP_1))
        {
            
        }
        if (IsKeyPressed(KEY_KP_2))
        {
            printf("teste");
        }
        if (IsKeyPressed(KEY_KP_4))
        {
            printf("teste");
        }
        if (IsKeyPressed(KEY_KP_5))
        {
            printf("teste");
        }

        EndDrawing();
    }
    CloseWindow();
}
