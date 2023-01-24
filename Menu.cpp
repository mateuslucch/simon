#include "Menu.h"
#include <iostream>

Menu::Menu()
{
    Button menuButtonsList[]{
        easyButton,
        mediumButton,
        hardButton};

    menuBtnListSize = sizeof(menuButtonsList) / sizeof(Button);
}

void Menu::centerTextHorizontal(char const *text, float centerPosPixels, float verticalPos, int fontSize, Color color)
{
    DrawText(TextFormat(text), centerPosPixels - MeasureText(text, fontSize) / 2, verticalPos, fontSize, color);
}

float Menu::difficultyLevel()
{
    switch (menuNavigation)
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
}