#ifndef GAME_HPP
#define GAME_HPP

#include <fstream>

#include "controllers/PlayerManager.hpp"

#include "menus/Menu.hpp"
#include "menus/MarketMenu.hpp"
#include "menus/LevelMenu.hpp"
#include "menus/MenuItems.hpp"

#include "datas/Parameters.hpp"

class Game {

    private: 
        PlayerManager * playerManager;

        Menu * mainMenu;
        Menu * homeMenu;
        Menu * gameOverMenu;

        MarketMenu * marketMenu;
        LevelMenu * levelMenu; 
        
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
