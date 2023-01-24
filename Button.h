// #ifndef BUTTON_H
// #define BUTTON_H

#include "raylib.h"

class Button
{
public:
    Button();

    Button(int posX,
           int posY,
           int buttonSizeX,
           int buttonSizeY,
           Color selectedColor,
           Color unselectedColor);

    Button(int posX,
           int posY,
           int buttonSizeX,
           int buttonSizeY,
           Color selectedColor,
           Color unselectedColor,
           char const *text,
           int fontSize);

    Button(int buttonSizeX, int buttonSizeY);
    void drawButton(bool selected);
    char const *text;
    int fontSize{10};
    Vector2 pos;
    Vector2 buttonSize;
    Color unselectedColor;
    Color selectedColor;
    Color backgroundColor = GRAY;

private:
    float backgroundBorder{10};
};