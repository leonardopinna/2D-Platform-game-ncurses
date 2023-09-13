#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "Menu.hpp"

class MainMenu : public Menu {
    private: 
        int loadMessageTimer;

    public:  
        MainMenu(char* menu[], int n);

        int getLoadMessageTimer();

        void setLoadMessageTimer(int time);

        void handleInput() override;

        void update() override;

        void render(int dist, int money, int life, char* name) override;

};

#endif
