// header for Square class
#include "raylib.h"

class SquareData
{
public:
    SquareData();
    void drawSquare(bool changeColor, float deltaTime);
    int getSize();
    Vector2 pos;
    Color mainColor;
    Color secondaryColor;
    bool buttonPushed = false;
    Sound clickSound;
    int keyCodeValue;
    char const *keyValue;

private:
    int squareSize{250};
    float colorBackTime{0.3f};
    float runningTime{};
};