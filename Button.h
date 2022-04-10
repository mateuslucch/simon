#include "raylib.h"

class Button
{
public:
    Button();
    void drawButton(bool selected);
    char const *text;
    int fontSize{10};
    Vector2 pos;
    Vector2 size;
    Color unselectedColor;
    Color selectedColor;
    Color backgroundColor = GRAY;

private:
    float backgroundBorder{10};
};