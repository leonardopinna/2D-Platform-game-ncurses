#ifndef GAME_OVER_MENU_HPP
#define GAME_OVER_MENU_HPP

#include "Menu.hpp"

class GameOverMenu : public Menu {

    public:
        GameOverMenu(char* menu[], int n);

        void handleInput();

        void update() override;

        void render(int dist, int money, int life, char* name) override;
};

#endif
