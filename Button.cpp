#include "Button.h"

Button::Button()
{
}

void Button::drawButton(bool selected)
{
    DrawRectangle(pos.x - backgroundBorder / 2, pos.y - backgroundBorder / 2, size.x + backgroundBorder, size.y + backgroundBorder, backgroundColor);
    if (selected == true)
    {
        DrawRectangle(pos.x, pos.y, size.x, size.y, selectedColor);
    }
    else
    {
        DrawRectangle(pos.x, pos.y, size.x, size.y, unselectedColor);
    }
    DrawText(text, pos.x + size.x / 2 - MeasureText(text, fontSize) / 2, pos.y + size.y / 2 - fontSize / 2, fontSize, RED);
}
