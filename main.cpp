#include "raylib.h"
#include <cstdio>

struct SquareData
{
    Vector2 pos;
    int size;
    Color mainColor;
    Color secondaryColor;
    float runningTime;
    bool buttonPushed;
    Sound clickSound;
};

SquareData ChangeColor(SquareData square, float updateTime, float deltaTime, KeyboardKey keyValue)
{
    
    if (IsKeyPressed(keyValue) && square.buttonPushed == false)
    {
        PlaySound(square.clickSound);
        square.buttonPushed = true;
    }
    if (square.buttonPushed == true)
    {
        square.runningTime += deltaTime;        
        if (square.runningTime > updateTime)
        {            
            square.buttonPushed = false;
            square.runningTime = 0.0;
        }
        DrawRectangle(square.pos.x, square.pos.y, square.size, square.size, square.secondaryColor);
    }
    else
    {
        DrawRectangle(square.pos.x, square.pos.y, square.size, square.size, square.mainColor);
    }
    return square;
}

int main()
{

    int windowDimensions[2]{640, 480};

    float updateTime{0.2};
   
    int gameRounds{};

    InitWindow(windowDimensions[0], windowDimensions[1], "Simon");
    InitAudioDevice();

    Sound clickSound1 = LoadSound("Assets/Sound/Randomize1.wav");
    Sound clickSound2 = LoadSound("Assets/Sound/Randomize2.wav");
    Sound clickSound3 = LoadSound("Assets/Sound/Randomize3.wav");
    Sound clickSound4 = LoadSound("Assets/Sound/Randomize4.wav");

    SetSoundVolume(clickSound1, 1);
    
    int squareSize = 200;
    int gap = 20;
    int xMargin = (windowDimensions[0] - squareSize * 2 - gap) / 2;
    int yMargin = (windowDimensions[1] - squareSize * 2 - gap) / 2;

    SquareData yellowSquare;
    yellowSquare.mainColor = YELLOW;
    yellowSquare.secondaryColor = GOLD;
    yellowSquare.pos.x = xMargin;
    yellowSquare.pos.y = yMargin + squareSize + gap;
    yellowSquare.size = squareSize;    
    yellowSquare.buttonPushed = false;
    yellowSquare.clickSound = clickSound1;

    SquareData blueSquare;
    blueSquare.mainColor = BLUE;
    blueSquare.secondaryColor = SKYBLUE;
    blueSquare.pos.x = xMargin + squareSize + gap;
    blueSquare.pos.y = yMargin + squareSize + gap;
    blueSquare.size = squareSize;    
    blueSquare.buttonPushed = false;
    blueSquare.clickSound = clickSound2;

    SquareData greenSquare;
    greenSquare.mainColor = GREEN;
    greenSquare.secondaryColor = LIME;
    greenSquare.pos.x = xMargin + squareSize + gap;
    greenSquare.pos.y = yMargin;
    greenSquare.size = squareSize;    
    greenSquare.buttonPushed = false;
    greenSquare.clickSound = clickSound3;

    SquareData redSquare;
    redSquare.mainColor = RED;
    redSquare.secondaryColor = MAROON;
    redSquare.pos.x = xMargin;
    redSquare.pos.y = yMargin;
    redSquare.size = squareSize;    
    redSquare.buttonPushed = false;
    redSquare.clickSound = clickSound4;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float dT{GetFrameTime()};

        ClearBackground(DARKGRAY);
        BeginDrawing();

        // Change yellow square
        yellowSquare = ChangeColor(yellowSquare, updateTime, dT, KEY_KP_1);

        // Change blue square
        blueSquare = ChangeColor(blueSquare, updateTime, dT, KEY_KP_2);

        // Change red square
        redSquare = ChangeColor(redSquare, updateTime, dT, KEY_KP_4);

        // Change green square
        greenSquare = ChangeColor(greenSquare, updateTime, dT, KEY_KP_5);

        EndDrawing();
    }

    UnloadSound(clickSound1);
    UnloadSound(clickSound2);
    UnloadSound(clickSound3);
    UnloadSound(clickSound4);
    CloseAudioDevice();
    CloseWindow();
}
