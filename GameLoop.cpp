#include <ncurses.h>
#include "Player.cpp"

class GameLoop {
    public:
        GameLoop() {};

        void executeGameLoop() {
            
        }
    
        void updateBulletPosition(vector<Bullet> bulletVect) {
            for (int i = 0; i < bulletVect.size(); i++) {
                bulletVect[i].move();
            }
        }

        void updateEnemiesPosition(vector<Enemy> enemyVect) {
            for (int i = 0; i < enemyVect.size(); i++) {
                enemyVect[i].move();
            }
        }
        void updateBulletLife() {

        }

        void checkCollisions() {

        }
};
