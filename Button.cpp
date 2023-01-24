#include "Button.h"

Button::Button()
{
}
Button::Button(int posX, int posY, int _buttonSizeX, int _buttonSizeY, Color _selectedColor, Color _unselectedColor)
{
    pos.x = posX;
    pos.y = posY;
    buttonSize.x = _buttonSizeX;
    buttonSize.y = _buttonSizeY;
    selectedColor = _selectedColor;
    unselectedColor = _unselectedColor;
}

Button::Button(int posX,
       int posY,
       int _buttonSizeX,
       int _buttonSizeY,
       Color _selectedColor,
       Color _unselectedColor,
       char const *_text,
       int _fontSize)
{
    pos.x = posX;
    pos.y = posY;
    buttonSize.x = _buttonSizeX;
    buttonSize.y = _buttonSizeY;
    selectedColor = _selectedColor;
    unselectedColor = _unselectedColor;
    text = _text;
    fontSize = _fontSize;
}

Button::Button(int _buttonSizeX, int _buttonSizeY)
{
    buttonSize.x = _buttonSizeX;
    buttonSize.y = _buttonSizeY;
}

void Button::drawButton(bool selected)
{
    DrawRectangle(pos.x - backgroundBorder / 2, pos.y - backgroundBorder / 2, buttonSize.x + backgroundBorder, buttonSize.y + backgroundBorder, backgroundColor);
    if (selected == true)
    {
        DrawRectangle(pos.x, pos.y, buttonSize.x, buttonSize.y, selectedColor);
    }
    else
    {
        DrawRectangle(pos.x, pos.y, buttonSize.x, buttonSize.y, unselectedColor);
    }
    DrawText(text, pos.x + buttonSize.x / 2 - MeasureText(text, fontSize) / 2, pos.y + buttonSize.y / 2 - fontSize / 2, fontSize, RED);
}
