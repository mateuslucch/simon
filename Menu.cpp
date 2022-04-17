#include "Menu.h"
#include <iostream>

Menu::Menu()
{
    easyButton.size.x = buttonsXSize;
    easyButton.size.y = buttonsYSize;
    easyButton.pos.x = 400.f - easyButton.size.x / 2;
    easyButton.pos.y = 200 - easyButton.size.y / 2;
    easyButton.unselectedColor = GREEN;
    easyButton.selectedColor = BLUE;
    easyButton.text = "Easy";
    easyButton.fontSize = buttonsFontSize;

    mediumButton.size.x = buttonsXSize;
    mediumButton.size.y = buttonsYSize;
    mediumButton.pos.x = 400.f - mediumButton.size.x / 2;
    mediumButton.pos.y = 300 - mediumButton.size.y / 2;
    mediumButton.unselectedColor = GREEN;
    mediumButton.selectedColor = BLUE;
    mediumButton.text = "Medium";
    mediumButton.fontSize = buttonsFontSize;

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
    centerTextHorizontal("SIMON IS ASKING POLITELY...", 400.f, 50.f - 50.f / 2, 40, RED);

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