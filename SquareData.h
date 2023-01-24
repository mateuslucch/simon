// header for Square class
#include "raylib.h"

class SquareData
{
public:
    SquareData();
    SquareData(int posX, int posY, int squareSize, Color mainColor, Color secondaryColor, bool buttonPushed, Sound clickSound, int keyCodeValue, char const *keyValue);
    SquareData(Color mainColor, Color secondaryColor, bool buttonPushed, Sound clickSound, int keyCodeValue, char const *keyValue); // teste
    SquareData(int _squareSize);

    void drawSquare(bool changeColor, float deltaTime);
    int getSize();
    char getKeyValue();
    
    Vector2 pos;    
    Color mainColor;
    Color secondaryColor;
    bool buttonPushed = false;
    Sound clickSound;
    int keyCodeValue;
    char const *keyValue;
    int squareSize;

private:
    float colorBackTime{0.3f};
    float runningTime{};        
};