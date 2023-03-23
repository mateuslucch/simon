#include "Menu.h"
#include <iostream>

Menu::Menu()
{
    Button menuButtonsList[]{
        easyButton,
        mediumButton,
        hardButton};

    menuButtonListSize = sizeof(menuButtonsList) / sizeof(Button);
}

void Menu::centerTextHorizontal(char const *text, float centerPosPixels, float verticalPos, int fontSize, Color color)
{
    DrawText(TextFormat(text), centerPosPixels - MeasureText(text, fontSize) / 2, verticalPos, fontSize, color);
}

float Menu::difficultyLevelParameters()
{
    switch (menuNavigationIndex)
    {
    case 0:
        simonTime = 0.6f;
        break;
    case 1:
        simonTime = 0.4f;
        break;
    case 2:
        simonTime = 0.3f;
        break;
    }
    return simonTime;
}

void Menu::drawMenu()
{
    // Title
    centerTextHorizontal("SIMON IS ASKING POLITELY...", 400.f, 50.f - 50.f / 2, 40, RED);

    // Instructions
    centerTextHorizontal("Move arrows up and down to select the level of difficult.", 400.f, 120.f - 50.f / 2, 24, BLACK);
    centerTextHorizontal("Push \"Enter\" to start", 400.f, 154.f - 50.f / 2, 24, BLACK);

    if (IsKeyPressed(KEY_UP))
    {

        PlaySound(menuNavigationSound);
        menuNavigationIndex--;
        if (menuNavigationIndex < 0)
        {
            menuNavigationIndex = menuButtonListSize - 1;
        }
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        PlaySound(menuNavigationSound);
        menuNavigationIndex++;
        if (menuNavigationIndex > menuButtonListSize - 1)
        {
            menuNavigationIndex = 0;
        }
    }

    switch (menuNavigationIndex)
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
}
