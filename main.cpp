#include "raylib.h"
#include <cstdio>
#include <iostream>
#include <random>
#include <list>
#include <thread>

#include "SquareData.h"
#include "Menu.h"

using namespace std;

void DrawTextHorizontal(char const *text, float centerPosPixels, float verticalPos, int fontSize, Color color)
{
    DrawText(TextFormat(text), centerPosPixels - MeasureText(text, fontSize) / 2, verticalPos, fontSize, color);
}

int main()
{

    int totalWindowDimensions[2]{800, 600};

    InitWindow(totalWindowDimensions[0], totalWindowDimensions[1], "Simon");
    InitAudioDevice();

    Sound clickSound1 = LoadSound("Assets/Sound/Randomize1.wav");
    Sound clickSound2 = LoadSound("Assets/Sound/Randomize2.wav");
    Sound clickSound3 = LoadSound("Assets/Sound/Randomize3.wav");
    Sound clickSound4 = LoadSound("Assets/Sound/Randomize4.wav");
    Sound soundSquareList[] =
        {
            clickSound1,
            clickSound2,
            clickSound3,
            clickSound4};

    Sound menuNavSound = LoadSound("Assets/Sound/MenuNavigation.wav");

    // set all sounds volume
    SetSoundVolume(menuNavSound, 1);
    for (Sound sound : soundSquareList)
    {
        SetSoundVolume(sound, 1);
    }

    // UI
    Color clearBackgroundColor = GRAY;

    int gap{10};
    int leftMargin{250};
    int upMargin{50};
    int squareSize{250};

    // SQUARES DATA
    SquareData yellowSquare(
        leftMargin + gap,
        upMargin + squareSize + 2 * gap,
        squareSize,
        YELLOW,
        GOLD,
        false,
        clickSound1,
        49,
        "1");

    SquareData blueSquare(
        leftMargin + squareSize + 2 * gap,
        upMargin + squareSize + 2 * gap,
        squareSize,
        BLUE,
        SKYBLUE,
        false,
        clickSound2,
        50,
        "2");

    SquareData redSquare(
        leftMargin + gap,
        upMargin + gap,
        squareSize,
        RED,
        MAROON,
        false,
        clickSound4,
        52,
        "4");

    SquareData greenSquare(
        leftMargin + squareSize + 2 * gap,
        upMargin + gap,
        squareSize,
        GREEN,
        LIME,
        false,
        clickSound3,
        53,
        "5");

    SquareData squareList[] = {
        yellowSquare,
        blueSquare,
        redSquare,
        greenSquare};

    // Gamemenu
    Menu gameMenu;

    int maxChances{4};
    int playerChances = maxChances;
    int score{0};
    bool gameMenuRun = true;
    bool gameOver = false;
    bool simonSortNumber = false;
    bool playerTurn = false;
    bool simonPlaySequence = false;
    list<int> simonListInt{};

    float simonTimeCount{0.f};
    float simonSpeed{0.6f};
    int playerPushBtnCount{0};
    float changeStateDelay{0.f};
    int animCount{};

    int numberSquares = sizeof(squareList) / sizeof(SquareData);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float dT{GetFrameTime()};

        ClearBackground(clearBackgroundColor);
        BeginDrawing();

        // Draw Borders
        int lineThickness{5};
        // UI Lines
        // up, down, left, right
        DrawRectangle(0,
                      0,
                      totalWindowDimensions[0],
                      lineThickness,
                      BLACK);
        DrawRectangle(0,
                      totalWindowDimensions[1] - lineThickness,
                      totalWindowDimensions[0],
                      lineThickness,
                      BLACK);
        DrawRectangle(0,
                      0,
                      lineThickness,
                      totalWindowDimensions[1],
                      BLACK);
        DrawRectangle(totalWindowDimensions[0] - lineThickness,
                      lineThickness,
                      lineThickness,
                      totalWindowDimensions[1],
                      BLACK);

        // Game Menu
        if (gameMenuRun)
        {
            gameMenu.drawMenu();

            if (IsKeyPressed(KEY_ENTER) && gameMenuRun == true)
            {
                auto i = time(0);
                srand(i);

                simonSpeed = gameMenu.difficultyLevelParameters();
                simonSortNumber = true;
                gameMenuRun = false;
                gameOver = false;
                changeStateDelay = 0;
                score = 0;
            }
        }

        // game started
        else
        {
            DrawRectangle(250,
                          0,
                          lineThickness,
                          totalWindowDimensions[1],
                          BLACK);

            /// Left block UI
            DrawTextHorizontal("Push \"q\" to", 125.f, 50.f, 20, RED);
            DrawTextHorizontal("go back to menu", 125.f, 75.f, 20, RED);
            DrawTextHorizontal("Push \"esc\" to", 125.f, 125.f, 20, RED);
            DrawTextHorizontal("exit game", 125.f, 150.f, 20, RED);

            DrawTextHorizontal("Score:", 125.f, 230.f, 25, RED);
            DrawTextHorizontal(TextFormat("%d", score), 125.f, 265.f, 30, RED);

            DrawTextHorizontal("Player Chances:", 125.f, 330.f, 25, RED);
            DrawTextHorizontal(TextFormat("%d", playerChances), 125.f, 365.f, 30, RED);

            /// End Left block UI

            /// Right block UI and gameplay logic

            yellowSquare.drawSquare(false, dT);
            blueSquare.drawSquare(false, dT);
            redSquare.drawSquare(false, dT);
            greenSquare.drawSquare(false, dT);

            // simon sort a new number, no visual feedback here
            if (simonSortNumber)
            {

                playerTurn = false;

                int randomValue{};

                randomValue = rand() % (numberSquares);

                simonListInt.push_back(randomValue);

                simonSortNumber = false;
                simonPlaySequence = true;
            }

            if (simonPlaySequence)
            {
                DrawTextHorizontal("Simon Turn", 525.f, 10.f, 40, RED);

                simonTimeCount += dT;
                if (animCount == (int)simonListInt.size())
                {
                    simonPlaySequence = false;
                    playerTurn = true;
                    animCount = 0;
                }
                else
                {
                    if (simonTimeCount > simonSpeed)
                    {
                        list<int>::iterator it = simonListInt.begin();
                        advance(it, animCount);

                        switch (*it)
                        {
                        case 0:
                            yellowSquare.drawSquare(true, dT);
                            break;
                        case 1:
                            blueSquare.drawSquare(true, dT);
                            break;
                        case 2:
                            redSquare.drawSquare(true, dT);
                            break;
                        case 3:
                            greenSquare.drawSquare(true, dT);
                            break;
                        }

                        simonTimeCount = 0;
                        animCount++;
                    }
                }
            }

            if (playerTurn)
            {
                DrawTextHorizontal("Player Turn", 525.f, 10.f, 40, RED);
                int keyPressed{};

                if (GetKeyPressed())
                {
                    keyPressed = GetCharPressed();
                    if (!gameOver)
                    {
                        // num1 = 49, num2 = 50, num4 = 52, num5 = 53, numerical key
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
                        if (keyPressed == yellowSquare.keyCodeValue ||
                            keyPressed == blueSquare.keyCodeValue ||
                            keyPressed == greenSquare.keyCodeValue ||
                            keyPressed == redSquare.keyCodeValue)
                        {
                            list<int>::iterator it = simonListInt.begin();
                            advance(it, playerPushBtnCount);

                            if (squareList[*it].keyCodeValue == keyPressed)
                            {
                                playerPushBtnCount++;
                                // printf("Right sequence! \n");

                                // "win" path (add extra value to sequence)
                                if (playerPushBtnCount == (int)simonListInt.size())
                                {
                                    playerTurn = false;
                                    simonSortNumber = true;
                                    playerPushBtnCount = 0;
                                    score++;
                                }
                            }
                            else
                            {
                                // printf("Wrong sequence! \n");
                                playerChances--;

                                playerTurn = false;
                                simonPlaySequence = true;
                                playerPushBtnCount = 0;

                                if (playerChances == 0)
                                {
                                    gameOver = true;
                                    DrawTextHorizontal("Game Over!", 525.f, 20.f, 40, RED);
                                    changeStateDelay += dT;
                                    playerTurn = false;
                                    gameMenuRun = true;
                                    changeStateDelay = 0.f;
                                    playerChances = maxChances;
                                    simonListInt.clear();
                                    playerPushBtnCount = 0;
                                }
                            }
                        }
                        // exit game
                        else if (keyPressed == 113)
                        {
                            playerTurn = false;
                            gameMenuRun = true;
                            playerChances = maxChances;
                            simonListInt.clear();
                            playerPushBtnCount = 0;
                        }

                        else
                        {
                            // printf("Invalid key!\n");
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