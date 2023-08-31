#ifndef HOME_MENU_HPP
#define HOME_MENU_HPP

#include "Menu.hpp"

class HomeMenu : public Menu {
    private: 
        int saveMessageTimer = 0;

    public:  
        HomeMenu(char* menu[], int n, PlayerManager * playerManager);

        void handleInput() override;

        void update();

        void render(int dist, int money, int life, char* name) override;

};

#endif
