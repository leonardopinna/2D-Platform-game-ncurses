#ifndef MARKET_MENU_HPP
#define MARKET_MENU_HPP

#include "Menu.hpp"

class MarketMenu : public Menu {
    private: 
         
    public:  
        MarketMenu(string title, string msg, PlayerManager * p);

        void handleInput();

        void render();

        GameState run(GameState gs); 
};

#endif
