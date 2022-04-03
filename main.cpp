#include "raylib.h"
#include <cstdio>
#include <iostream>
#include <random>
#include <list>
#include <thread>

// my classes
#include "SquareData.h"

using namespace std;

void StatusText(char const *text)
{
    DrawText(text, 55.f, 20.f, 40, RED);
}

int main()
{

    int windowDimensions[2]{640, 480};
    int referenceWindowDimension[2]{640, 520};

    InitWindow(windowDimensions[0], windowDimensions[1], "Simon");
    InitAudioDevice();

    Sound clickSound1 = LoadSound("Assets/Sound/Randomize1.wav");
    Sound clickSound2 = LoadSound("Assets/Sound/Randomize2.wav");
    Sound clickSound3 = LoadSound("Assets/Sound/Randomize3.wav");
    Sound clickSound4 = LoadSound("Assets/Sound/Randomize4.wav");

    SetSoundVolume(clickSound1, 1);

    // squares common values
    int squareSize = 180;
    int gap = 20;
    int xMargin = (referenceWindowDimension[0] - squareSize * 2 - gap) / 2;
    int yMargin = (referenceWindowDimension[1] - squareSize * 2 - gap) / 2;

    SquareData yellowSquare;
    yellowSquare.mainColor = YELLOW;
    yellowSquare.secondaryColor = GOLD;
    yellowSquare.pos.x = xMargin;
    yellowSquare.pos.y = yMargin + squareSize + gap;
    yellowSquare.buttonPushed = false;
    yellowSquare.clickSound = clickSound1;
    // yellowSquare.nameSquare = "yellow";
    yellowSquare.keyValue = 49;

    SquareData blueSquare;
    blueSquare.mainColor = BLUE;
    blueSquare.secondaryColor = SKYBLUE;
    blueSquare.pos.x = xMargin + squareSize + gap;
    blueSquare.pos.y = yMargin + squareSize + gap;
    blueSquare.buttonPushed = false;
    blueSquare.clickSound = clickSound2;
    // blueSquare.nameSquare = "blue";
    blueSquare.keyValue = 50;

    SquareData redSquare;
    redSquare.mainColor = RED;
    redSquare.secondaryColor = MAROON;
    // Note!! use CLITERAL(Color) late for more rgb colors!
    // redSquare.secondaryColor = CLITERAL(Color){50,20,33,200};
    redSquare.pos.x = xMargin;
    redSquare.pos.y = yMargin;
    redSquare.buttonPushed = false;
    redSquare.clickSound = clickSound4;
    // redSquare.nameSquare = "red";
    redSquare.keyValue = 52;

    SquareData greenSquare;
    greenSquare.mainColor = GREEN;
    greenSquare.secondaryColor = LIME;
    greenSquare.pos.x = xMargin + squareSize + gap;
    greenSquare.pos.y = yMargin;
    greenSquare.buttonPushed = false;
    greenSquare.clickSound = clickSound3;
    // greenSquare.nameSquare = "green";
    greenSquare.keyValue = 53;

    list<int> simonListInt{};

    SquareData squareList[] = {
        yellowSquare,
        blueSquare,
        redSquare,
        greenSquare};

    int maxChances = 6;
    int playerChances = maxChances;
    bool gameMenu = true;
    bool gameOver = false;
    bool simonSort = false;
    bool playerTurn = false;
    bool simonTurn = false;

    float simonTimeCount = 0.f;
    const float simonSpeed = 0.6f;
    int playerPushBtnCount = 0;
    float changeStateDelay = 0.f;
    int animCount{};

    int sizeArray = sizeof(squareList) / sizeof(SquareData);
    default_random_engine simon_random; // default engine
    uniform_int_distribution<int> int_distribution(0, sizeArray - 1);

    // example pushing list
    list<int> testListInt{};
    for (int i = 0; i < 10; i++)
    {
        testListInt.push_back(i);
    }
    for (int listValue : testListInt)
    {
        printf("%d \n", listValue);
    }
    // end example

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float dT{GetFrameTime()};

        ClearBackground(DARKGRAY);
        BeginDrawing();
        if (gameMenu)
        {
            DrawText("Push enter to start!", 55.f, windowDimensions[1] / 2 + 20.f, 50, RED);
            if (IsKeyPressed(KEY_ENTER) && gameMenu == true)
            {
                simonSort = true;
                gameMenu = false;
                gameOver = false;
                changeStateDelay = 0;
            }
        }
        else
        {
            // DrawText("Here can be the score!", 55.f, 20.f, 40, RED);
            DrawText(TextFormat("Player Chances:"), 5.f, windowDimensions[1] / 2 - 10.f, 15, RED);
            DrawText(TextFormat("%d", playerChances), 40.f, windowDimensions[1] / 2 + 20.f, 30, RED);

            // Change yellow square

            // Draw Squares
            yellowSquare.drawSquare(false, dT);
            blueSquare.drawSquare(false, dT);
            redSquare.drawSquare(false, dT);
            greenSquare.drawSquare(false, dT);

            // Change squares color

            if (simonSort)
            {

                playerTurn = false;

                // sort number
                int randomValue{};
                randomValue = int_distribution(simon_random);
                // assing to list
                printf("Adding value to list \n");
                simonListInt.push_back(randomValue);
                printf("New list: \n");
                for (int listValue : simonListInt)
                {
                    printf(" %d \n", listValue);
                }
                // end number choice
                simonSort = false;
                simonTurn = true;
            }

            // play squares auto
            if (simonTurn)
            {

                StatusText("Simon Turn");
                simonTimeCount += dT;
                if (animCount == (int)simonListInt.size())
                {
                    simonTurn = false;
                    playerTurn = true;
                    animCount = 0;
                }
                else
                {
                    if (simonTimeCount > simonSpeed)
                    {
                        DrawText(TextFormat("%d", (int)simonTimeCount), 40.f, windowDimensions[1] / 2 + 60.f, 30, RED);
                        list<int>::iterator it = simonListInt.begin();
                        advance(it, animCount);
                        squareList[*it].drawSquare(true, dT);
                        simonTimeCount = 0;
                        animCount++;
                    }
                }
            }

            DrawText(TextFormat("Time:"), 5.f, windowDimensions[1] / 2 + 50.f, 15, RED);
            DrawText(TextFormat("%d", (int)simonTimeCount), 40.f, windowDimensions[1] / 2 + 60.f, 30, RED);

            if (playerTurn)
            {
                StatusText("Player Turn");
                int keyPressed{};

                if (GetKeyPressed())
                {
                    keyPressed = GetCharPressed();
                    if (!gameOver)
                    {
                        // num1 = 49, num2 = 50, num4 = 52, num5 = 53
                        switch (keyPressed)
                        {
                        case 49:
                            yellowSquare.drawSquare(true, dT);
                            break;
                        case 50:
                            blueSquare.drawSquare(true, dT);
                            break;
                        case 52:
                            redSquare.drawSquare(true, dT);
                            break;
                        case 53:
                            greenSquare.drawSquare(true, dT);
                            break;
                        }

                        // test
                        if (keyPressed == yellowSquare.keyValue ||
                            keyPressed == blueSquare.keyValue ||
                            keyPressed == greenSquare.keyValue ||
                            keyPressed == redSquare.keyValue)
                        {
                            list<int>::iterator it = simonListInt.begin();
                            advance(it, playerPushBtnCount);

                            if (squareList[*it].keyValue == keyPressed)
                            {
                                playerPushBtnCount++;
                                printf("Right key! \n");
                                if (playerPushBtnCount == (int)simonListInt.size())
                                {
                                    playerTurn = false;
                                    simonSort = true;
                                    playerPushBtnCount = 0;
                                }
                                // put a delay before next round!!
                            }
                            else
                            {
                                printf("Wrong square! \n");
                                playerChances--;
                                playerTurn = false;
                                simonTurn = true;
                                playerPushBtnCount = 0;

                                //  player loose path
                                if (playerChances == 0)
                                {
                                    // _sleep lock things
                                    //_sleep(3000);
                                    gameOver = true;
                                    StatusText("Game Over");
                                    changeStateDelay += dT;
                                    playerTurn = false;
                                    gameMenu = true;
                                    changeStateDelay = 0.f;
                                    playerChances = maxChances;
                                    simonListInt.clear();
                                    playerPushBtnCount = 0;
                                }
                                // delay again to game over
                            }

                            // reset things and "go back" to start screen
                        }
                        // exit game
                        else if (keyPressed == 113) // 113 = "q", not "Q"
                        {
                            playerTurn = false;
                            gameMenu = true;
                            playerChances = maxChances;
                            simonListInt.clear();
                            playerPushBtnCount = 0;
                        }
                        // wrong button, but continue game
                        else
                        {
                            printf("Invalid key!\n");
                        }
                    }
                }
            }
        }

        EndDrawing();
    }

    UnloadSound(clickSound1);
    UnloadSound(clickSound2);
    UnloadSound(clickSound3);
    UnloadSound(clickSound4);
    CloseAudioDevice();
    CloseWindow();
}