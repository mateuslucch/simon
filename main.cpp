#include "raylib.h"
#include <cstdio>
#include <iostream>
#include <random>
#include <list>
#include <thread>

// my classes
#include "SquareData.h"
#include "Button.h"

using namespace std;

// void StatusText(char const *text)
// {
//     DrawText(text, 55.f, 20.f, 40, RED);
// }

void CenterTextHorizontal(char const *text, float centerPosPixels, float verticalPos, int fontSize, Color color)
{
    DrawText(TextFormat(text), centerPosPixels - MeasureText(text, fontSize) / 2, verticalPos, fontSize, color);
}

int main()
{

    int totalWindowDimensions[2]{800, 600};
    // int totalWindowDimensions[2]{1024, 768};

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

    // squares common values
    int gap = 10;

    // fixed margins for squares area
    int leftMargin = 250;
    // int rightMargin = 10; // not usefull
    int upMargin = 50;
    // int downMargin = 10; // not usefull

    // SQUARES DATA
    SquareData yellowSquare;
    yellowSquare.mainColor = YELLOW;
    yellowSquare.secondaryColor = GOLD;
    yellowSquare.pos.x = leftMargin + gap;
    yellowSquare.pos.y = upMargin + yellowSquare.getSize() + 2 * gap;
    yellowSquare.buttonPushed = false;
    yellowSquare.clickSound = clickSound1;
    yellowSquare.keyCodeValue = 49; // num1
    yellowSquare.keyValue = "1";

    SquareData blueSquare;
    blueSquare.mainColor = BLUE;
    blueSquare.secondaryColor = SKYBLUE;
    blueSquare.pos.x = leftMargin + blueSquare.getSize() + 2 * gap;
    blueSquare.pos.y = upMargin + blueSquare.getSize() + 2 * gap;
    blueSquare.buttonPushed = false;
    blueSquare.clickSound = clickSound2;
    blueSquare.keyCodeValue = 50; // num2
    blueSquare.keyValue = "2";

    SquareData redSquare;
    redSquare.mainColor = RED;
    redSquare.secondaryColor = MAROON;
    // Note!! use CLITERAL(Color) late for more rgb colors!
    // redSquare.secondaryColor = CLITERAL(Color){50,20,33,200};
    redSquare.pos.x = leftMargin + gap;
    redSquare.pos.y = upMargin + gap;
    redSquare.buttonPushed = false;
    redSquare.clickSound = clickSound4;
    redSquare.keyCodeValue = 52; // num4
    redSquare.keyValue = "4";

    SquareData greenSquare;
    greenSquare.mainColor = GREEN;
    greenSquare.secondaryColor = LIME;
    greenSquare.pos.x = leftMargin + greenSquare.getSize() + 2 * gap;
    greenSquare.pos.y = upMargin + gap;
    greenSquare.buttonPushed = false;
    greenSquare.clickSound = clickSound3;
    greenSquare.keyCodeValue = 53; // num5
    greenSquare.keyValue = "5";

    SquareData squareList[] = {
        yellowSquare,
        blueSquare,
        redSquare,
        greenSquare};

    // MENU BUTTONS
    int buttonsXSize = 200;
    int buttonsYSize = 60;
    int buttonsFontSize = 50;

    Button easyButton;
    easyButton.size.x = buttonsXSize;
    easyButton.size.y = buttonsYSize;
    easyButton.pos.x = 400.f - easyButton.size.x / 2;
    easyButton.pos.y = 200 - easyButton.size.y / 2;
    easyButton.unselectedColor = GREEN;
    easyButton.selectedColor = BLUE;
    easyButton.text = "Easy";
    easyButton.fontSize = buttonsFontSize;

    Button mediumButton;
    mediumButton.size.x = buttonsXSize;
    mediumButton.size.y = buttonsYSize;
    mediumButton.pos.x = 400.f - mediumButton.size.x / 2;
    mediumButton.pos.y = 300 - mediumButton.size.y / 2;
    mediumButton.unselectedColor = GREEN;
    mediumButton.selectedColor = BLUE;
    mediumButton.text = "Medium";
    mediumButton.fontSize = buttonsFontSize;

    Button hardButton;
    hardButton.size.x = buttonsXSize;
    hardButton.size.y = buttonsYSize;
    hardButton.pos.x = 400.f - hardButton.size.x / 2;
    hardButton.pos.y = 400 - hardButton.size.y / 2;
    hardButton.unselectedColor = GREEN;
    hardButton.selectedColor = BLUE;
    hardButton.text = "Hard";
    hardButton.fontSize = buttonsFontSize;

    Button menuButtonsList[]{
        easyButton,
        mediumButton,
        hardButton};

    int menuBtnListSize = sizeof(menuButtonsList) / sizeof(Button);
    int menuNavigation{};

    int maxChances = 6;
    int playerChances = maxChances;
    bool gameMenu = true;
    bool gameOver = false;
    bool simonSort = false;
    bool playerTurn = false;
    bool simonTurn = false;
    list<int> simonListInt{};

    float simonTimeCount = 0.f;
    const float simonSpeed = 0.6f;
    int playerPushBtnCount = 0;
    float changeStateDelay = 0.f;
    int animCount{};

    int sizeArray = sizeof(squareList) / sizeof(SquareData);
    default_random_engine simon_random; // default engine
    uniform_int_distribution<int> int_distribution(0, sizeArray - 1);

    // example pushing list use as reference for something
    list<int> testListInt{};
    for (int i = 0; i < 10; i++)
    {
        testListInt.push_back(i);
    }
    for (int listValue : testListInt)
    {
        //printf("%d \n", listValue);
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
            CenterTextHorizontal("Push enter to start!", 400.f, 50.f - 50.f / 2, 50, RED);

            if (IsKeyPressed(KEY_UP))
            {
                PlaySound(menuNavSound);
                menuNavigation--;
                if (menuNavigation < 0)
                {
                    menuNavigation = menuBtnListSize - 1;
                }
            }
            if (IsKeyPressed(KEY_DOWN))
            {
                PlaySound(menuNavSound);
                menuNavigation++;
                if (menuNavigation > menuBtnListSize - 1)
                {
                    menuNavigation = 0;
                }
            }

            switch (menuNavigation)
            {
            case 0:
                easyButton.drawButton(true);
                mediumButton.drawButton(false);
                hardButton.drawButton(false);
                break;
            case 1:
                easyButton.drawButton(false);
                mediumButton.drawButton(true);
                hardButton.drawButton(false);
                break;
            case 2:
                easyButton.drawButton(false);
                mediumButton.drawButton(false);
                hardButton.drawButton(true);
                break;

            default:
                break;
            }

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
            // Left block UI
            CenterTextHorizontal("Player Chances", 125.f, totalWindowDimensions[1] / 2 - 10.f, 20, RED);
            CenterTextHorizontal(TextFormat("%d", playerChances), 125.f, totalWindowDimensions[1] / 2 + 20.f, 30, RED);

            // Draw Squares
            yellowSquare.drawSquare(false, dT);
            blueSquare.drawSquare(false, dT);
            redSquare.drawSquare(false, dT);
            greenSquare.drawSquare(false, dT);

            // simon sort a new number
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

            // simon play the sequence of numbers
            if (simonTurn)
            {
                CenterTextHorizontal("Simon Turn", 525.f, 10.f, 40, RED);

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
                        list<int>::iterator it = simonListInt.begin();
                        advance(it, animCount);
                        squareList[*it].drawSquare(true, dT);
                        simonTimeCount = 0;
                        animCount++;
                    }
                }
            }

            // DrawText(TextFormat("Time:"), 5.f, totalWindowDimensions[1] / 2 + 50.f, 15, RED);
            // DrawText(TextFormat("%d", (int)simonTimeCount), 40.f, totalWindowDimensions[1] / 2 + 60.f, 30, RED);

            if (playerTurn)
            {
                CenterTextHorizontal("Player Turn", 525.f, 10.f, 40, RED);
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
                                    // _sleep lock things, not good
                                    //_sleep(3000);
                                    gameOver = true;
                                    CenterTextHorizontal("Game Over!", 525.f, 20.f, 40, RED);
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