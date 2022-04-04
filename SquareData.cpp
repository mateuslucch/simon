#include "SquareData.h"

SquareData::SquareData()
{
}

void SquareData::setPosition()
{

}

int SquareData::getSize()
{
    return size;
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
        DrawRectangle(pos.x, pos.y, size, size, secondaryColor);
        runningTime += deltaTime;
        if (runningTime > colorBackTime)
        {
            buttonPushed = false;
            runningTime = 0.0;
        }
    }
    else
    {
        DrawRectangle(pos.x, pos.y, size, size, mainColor);
    }
};