#include "SquareData.h"

SquareData::SquareData()
{
}

SquareData::SquareData(int _posX, int _posY, int _squareSize, Color _mainColor, Color _secondaryColor, bool _buttonPushed, Sound _clickSound, int _keyCodeValue, char const *_keyValue)
{
    pos.x = _posX;
    pos.y = _posY;
    squareSize = _squareSize;
    mainColor = _mainColor;
    secondaryColor = _secondaryColor;
    buttonPushed = _buttonPushed;
    clickSound = _clickSound;
    keyCodeValue = _keyCodeValue;
    keyValue = _keyValue;    
}

SquareData::SquareData(int _squareSize)
{
    squareSize = _squareSize;
}

// teste
SquareData::SquareData(Color _mainColor, Color _secondaryColor, bool _buttonPushed, Sound _clickSound, int _keyCodeValue, char const *_keyValue)
{
    mainColor = _mainColor;
    secondaryColor = _secondaryColor;
    buttonPushed = _buttonPushed;
    clickSound = _clickSound;
    keyCodeValue = _keyCodeValue;
    keyValue = _keyValue;
}

int SquareData::getSize()
{
    return squareSize;
}

char SquareData::getKeyValue()
{
    return *keyValue;
}

void SquareData::drawSquare(bool changeColor, float deltaTime)
{
    if (changeColor)
    {
        PlaySound(clickSound);
        buttonPushed = true;
    }
    if (buttonPushed == true)
    {
        DrawRectangle(pos.x, pos.y, squareSize, squareSize, secondaryColor);
        runningTime += deltaTime;
        if (runningTime > colorBackTime)
        {
            buttonPushed = false;
            runningTime = 0.0;
        }
    }
    else
    {
        DrawRectangle(pos.x, pos.y, squareSize, squareSize, mainColor);
    }

    int fontSize = 100;
    DrawText(TextFormat(keyValue), pos.x + squareSize / 2 - MeasureText(keyValue, fontSize) / 2, pos.y + squareSize / 2 - fontSize / 2, fontSize, secondaryColor);
};