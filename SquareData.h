// header for Square class
#include "raylib.h"

class SquareData
{
public:
    SquareData();
    void drawSquare(bool changeColor, float tick);
    Vector2 pos;
    Color mainColor;
    Color secondaryColor;
    bool buttonPushed = false;
    Sound clickSound;
    // not using, could be usefull?
    // string nameSquare; // not working here, need a library?
    int keyValue;    

private:
    int size{180};
    float colorBackTime{0.5f};
    float runningTime{};
};