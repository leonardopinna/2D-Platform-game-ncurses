#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>
#include <fstream>

#include "controllers/PlayerManager.hpp"

#include "menus/Menu.hpp"
#include "menus/MarketMenu.hpp"
#include "menus/LevelsManager.hpp"
#include "menus/MenuItems.hpp"

#include "datas/Parameters.hpp"

class Game {

    private: 

        PlayerManager * playerManager;
        
        LevelManager * levelManager;

        Menu * mainMenu;
        Menu * homeMenu;
        Menu * gameOverMenu;

        MarketMenu * marketMenu; 
        
        WINDOW * win;

    public: 

        GameState currentState; 

        bool running; 

        Game();

        void loadGame();
        void saveGame();

        void stopGame(); 

        void run();

        void initilizeScreen(); 

};

#endif
