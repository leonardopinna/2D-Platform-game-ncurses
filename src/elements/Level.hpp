#ifndef LEVEL_HPP
#define LEVEL_HPP 

#include "../datas/Parameters.hpp"

#include "../elements/Player.hpp"

#include "../datas/EnemyList.hpp"
#include "../datas/Walls.hpp"
#include "../datas/Doors.hpp"
#include "../datas/Bonuses.hpp"

class Level {
    public:
        int numEnemies;
        int numWalls;
        int numDollars;
        vector<Bullet> playerBulletVector; 
        vector<Bullet> enemyBulletVector; 
        vector<Enemy> enemyVector;
        vector<vector<int>> structure;
        vector<Wall> wallVector;
        vector<Door> doorVector;
        vector<Wall> moneyVector;
        int center_y;
        int center_x;
        Player * player;
        
        Level(int level, vector<vector<int>> s);

        void setWallStructure(vector<vector<int>> w) {
            this->structure = w; 
        }

        bool isFreePositionToDraw(int x, int y);

        bool isValidPosition(int x, int y);

        bool isFreePositionToGo(int x, int y);

        vector<int> findFreePosition(int wStart, int wEnd, int hStart, int hEnd);
};

#endif