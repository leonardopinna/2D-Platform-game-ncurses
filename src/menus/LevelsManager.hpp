#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP 

#include "../elements/Player.hpp"
#include "../elements/Level.hpp"

#include "../datas/LevelList.hpp"

#include "Menu.hpp"

class LevelManager : public Menu {
    private:
        double timeSinceLastBulletUpdate;
        chrono::time_point<chrono::steady_clock> currentTime;
        chrono::time_point<chrono::steady_clock> startTime;
        chrono::duration<double> elapsedTime;

    public:
        
        bool outOfBounds(Element t) {
            return t.getX() < 1 || t.getY() < 1 || t.getX() > WIDTH - 2 || t.getY() > HEIGHT - 2;
        }

        bool collision(Element a, Element b) {
            return a.getX() == b.getX() && a.getY() == b.getY();
        }

        vector<Level*> levelVector;
        Level* currentLevel;
        int level;
        
        Player * player; 

        bool gameStarted;  

    LevelManager(PlayerManager * playerManager);

    void initializeGame();

    GameState run(GameState gs, WINDOW * wdw); 

    void gameOver();

    void handleInput();
    
    void update();

    void draw(WINDOW * wdw);

    void render();
    
};

#endif