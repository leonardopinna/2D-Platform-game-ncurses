#ifndef LEVEL_HPP
#define LEVEL_HPP 

#include <vector>
#include <ncurses.h>
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Wall.hpp"
#include "Door.hpp"
#include "Player.hpp"
#include "../Parameters.hpp"

using namespace std;

class Level {
    public:
        int numEnemies;
        int numWalls;
        int numDollars;
        vector<Bullet> playerBulletVector; 
        vector<Bullet> enemyBulletVector; 
        vector<Enemy> enemyVector;
        vector<Wall> wallVector;
        vector<Door> doorVector;
        vector<Wall> moneyVector;
        int center_y;
        int center_x;
        Player * player = new Player('&', 10, Direction::RIGHT, &fionda);
    
    template <typename T>
    bool outOfBounds(T& t) {
        return t.getX() < 1 || t.getY() < 1 || t.getX() > WIDTH - 2 || t.getY() > HEIGHT - 2;
    }

    template <typename T1, typename T2>
    bool collision(T1& a, T2& b) {
        return a.getX() == b.getX() && a.getY() == b.getY();
    }

    Level() {};
    Level(int level) { 
        vector<int> enemyQ(enemies.size(), 0);

        level = level;

        // Generate prev door
        this->doorVector.push_back(door);
        this->doorVector[0].setX(1);
        this->doorVector[0].setY(rand() % (HEIGHT - 2) + 1);
        
        // Generate next door
        this->doorVector.push_back(door);
        this->doorVector[1].setX(WIDTH - 2);
        this->doorVector[1].setY(rand() % (HEIGHT - 2) + 1);

        // Generates walls        
        for (int i = 0; i < walls.size(); i++) {
            for (int j = 0; j < 5; j++) {
                int XX, YY;
                do {
                    XX = rand() % (WIDTH - 2) + 1;
                    YY = rand() % (HEIGHT - 2) + 1;
                } while (!isFreePositionToDraw(XX, YY));

                this->wallVector.push_back(walls[i]);
                this->wallVector[i*j + j].setX(XX);
                this->wallVector[i*j + j].setY(YY);
            }
        }

        // Generate money icon '$'
        for (int i = 0; i < 3 - level / 10; i++) {
            int XX, YY;
                do {
                    XX = rand() % (WIDTH - 2) + 1;
                    YY = rand() % (HEIGHT - 2) + 1;
                } while (!isFreePositionToDraw(XX, YY));

                this->moneyVector.push_back(moneyWall);
                this->moneyVector[i].setX(XX);
                this->moneyVector[i].setY(YY);
        }
    
        // Generates enemies
        if (level / 10 + 1 < enemies.size()) {
            enemyQ[level / 10] = level / 10 + level % 10 + 1;
            enemyQ[level / 10 + 1] = (level - (level % 10) * 10) % 5;
        } else {
            enemyQ[enemies.size() - 1] = level - 25 + 1;
        }

        for (int i = 0; i < enemies.size(); i++){
            for (int j = 0; j < enemyQ[i]; j++) {
                int XX, YY;
                do {
                    XX = rand() % (WIDTH - 2) + 1;
                    YY = rand() % (HEIGHT - 2) + 1;
                } while (!isFreePositionToDraw(XX, YY));

                this->enemyVector.push_back(enemies[i]);
                this->enemyVector[enemyVector.size()-1].setX(XX);
                this->enemyVector[enemyVector.size()-1].setY(YY);
            }
        }
    }

    bool isFreePositionToDraw(int x, int y) {
        for (Wall w : wallVector) {
            if (w.getX() == x && w.getY() == y) return false; 
        }
        for (Door w : doorVector) {
            if (w.getX() == x && w.getY() == y) return false; 
        }
        for (Enemy w : enemyVector) {
            if (w.getX() == x && w.getY() == y) return false; 
        }
        return isValidPosition(x, y);
    }

    bool isValidPosition(int x, int y) {
        return (x > 0 && x < WIDTH - 1 && y > 0 && y < HEIGHT - 1);
    }

    bool isFreePositionToGo(int x, int y) {
        for (Wall w : wallVector) {
            if (w.getX() == x && w.getY() == y) return false; 
        }
        return isValidPosition(x,y);
    }
    
};

#endif