#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>
#include <fstream>
#include <string>
#include <vector>

#include "Level.hpp"
#include "costants/MenuItems.hpp"
#include "costants/Parameters.hpp"

using namespace std;

enum class GameState {
    MainMenu,
    Market,
    WeaponMenu,
    Playing,
    GameOver
};

class Game {
    public: 
        GameState currentState = GameState::MainMenu;
        Player player = Player(1000, '&');

        int saveMessageTimer = 0;
        int loadMessageTimer = 0;

        bool gameStarted = false;
        bool running; 

        vector<Level*> levelVector;
        Level* currentLevel;
        int currLevelInt;

        int selectedItem;
        
        double timeSinceLastBulletUpdate;
        chrono::time_point<chrono::steady_clock> currentTime;
        chrono::time_point<chrono::steady_clock> startTime;
        chrono::duration<double> elapsedTime;

        WINDOW *win = newwin(HEIGHT, WIDTH, 0, 0);

        Game();

        void loadGame();
        void saveGame();

        void stopGame(); 

        void initializeGame();

        void gameOver();

        void createLevel();

        void run();

        void initilizeScreen();

        void handleInput();

        void update();

        void render();

        void drawPrompt();

        void drawStats(); 

};

#endif
