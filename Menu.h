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
    int buttonsYSize{60};
    int buttonsFontSize{50};

    Sound menuNavSound = LoadSound("Assets/Sound/MenuNavigation.wav");

    // Menu Buttons
    Button easyButton = Button(400.f - buttonsXSize / 2,
                               200 - buttonsYSize / 2,
                               buttonsXSize,
                               buttonsYSize,
                               BLUE,
                               GREEN,
                               "Easy",
                               buttonsFontSize);
    Button mediumButton = Button(400.f - buttonsXSize / 2,
                                 300 - buttonsYSize / 2,
                                 buttonsXSize,
                                 buttonsYSize,
                                 BLUE,
                                 GREEN,
                                 "Medium",
                                 buttonsFontSize);
    Button hardButton = Button(400.f - buttonsXSize / 2,
                               400 - buttonsYSize / 2,
                               buttonsXSize,
                               buttonsYSize,
                               BLUE,
                               GREEN,
                               "Hard",
                               buttonsFontSize);

    int menuNavigation{};
    int menuBtnListSize{};
};