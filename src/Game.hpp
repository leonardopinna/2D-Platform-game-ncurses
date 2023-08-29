#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>
#include <fstream>
#include <vector>

#include "PlayerManager.hpp"
#include "menus/MainMenu.hpp"
#include "menus/HomeMenu.hpp"
#include "menus/MarketMenu.hpp"
#include "menus/LevelsManager.hpp"
#include "menus/GameOverMenu.hpp"
#include "gameElements/Player.hpp"
#include "gameElements/Level.hpp"
#include "menus/MenuItems.hpp"
#include "Parameters.hpp"

using namespace std;

class Game {

    public: 
        PlayerManager * playerManager;
        LevelManager * levelManager;
        MainMenu * mainMenu;
        HomeMenu * homeMenu;
        MarketMenu * marketMenu; 
        GameOverMenu * gameOverMenu; 

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
