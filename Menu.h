#include "raylib.h"
#include "Button.h"

class Menu
{
public:
    Menu();
    void drawMenu();
    void centerTextHorizontal(char const *text, float centerPosPixels, float verticalPos, int fontSize, Color color);
    float difficultyLevel();

private:
    float simonTime{1};
    int fontSize{10};
    float backgroundBorder{10};
    int buttonsXSize{200};
    int buttonsYSize = 60;
    int buttonsFontSize = 50;

    Sound menuNavSound = LoadSound("Assets/Sound/MenuNavigation.wav");

    Button easyButton;
    Button mediumButton;
    Button hardButton;

    int menuNavigation{};
    int menuBtnListSize{};
};