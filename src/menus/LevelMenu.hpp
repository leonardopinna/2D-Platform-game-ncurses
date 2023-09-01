#ifndef LEVEL_MENU_HPP
#define LEVEL_MENU_HPP 

#include "../elements/Level.hpp"
#include "../datas/LevelList.hpp"

#include "Menu.hpp"

class LevelMenu : public Menu {
    private:
        double deltaTime;
        chrono::time_point<chrono::steady_clock> currentTime;
        chrono::time_point<chrono::steady_clock> startTime;
        chrono::duration<double> elapsedTime;

    public:

        vector<Level*> levelVector;
        Level* currentLevel;
        int level;
        int startingLevel; 
        
        Shooter * player; 

        bool gameStarted;  

        LevelMenu(PlayerManager * playerManager);

        void initializeGame();

        GameState run(GameState gs, WINDOW * wdw); 

        void gameOver();

        void handleInput();
        
        void update();

        void draw(WINDOW * wdw);

};

#endif