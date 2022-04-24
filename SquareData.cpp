#include "SquareData.h"

SquareData::SquareData()
{
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