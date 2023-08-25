#ifndef LEVEL_HPP
#define LEVEL_HPP 

#include <vector>
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Wall.hpp"
#include "Door.hpp"
#include "Player.hpp"

using namespace std;

class Level {
    public:
        int numEnemies;
        int numWalls;
        vector<Bullet> playerBulletVector; 
        vector<Bullet> enemyBulletVector; 
        vector<Enemy> enemyVector;
        vector<Wall> wallVector;
        vector<Door> doorVector;
        int center_y;
        int center_x;
    
    template <typename T>
    bool outOfBounds(T& t) {
        return t.getX() < 1 || t.getY() < 1 || t.getX() > WIDTH - 2 || t.getY() > HEIGHT - 2;
    }

    template <typename T1, typename T2>
    bool collision(T1& a, T2& b) {
        return a.getX() == b.getX() && a.getY() == b.getY();
    }

    Level() {}
    Level(int numEnemies, int numWalls) {

        // Generates enemies
        for (int i = 0; i < numEnemies; i++) {
            this->enemyVector.push_back(goblin);
            this->enemyVector[i].setX(rand() % WIDTH / 2 + WIDTH / 2 - 1);
            this->enemyVector[i].setY(rand() % (HEIGHT - 2) + 1);
        }

        // Generates walls 
        for (int i = 0; i < numWalls; i++) {
            this->wallVector.push_back(baseWall);
            this->wallVector[i].setX(rand() % WIDTH / 2 + WIDTH / 2 - 1);
            this->wallVector[i].setY(rand() % (HEIGHT - 2) + 1);
        }

        // Generate prev door
        this->doorVector.push_back(door);
        this->doorVector[0].setX(1);
        this->doorVector[0].setY(rand() % (HEIGHT - 2) + 1);
        
        // Generate next door
        this->doorVector.push_back(door);
        this->doorVector[1].setX(WIDTH - 2);
        this->doorVector[1].setY(rand() % (HEIGHT - 2) + 1);
    }
};

#endif