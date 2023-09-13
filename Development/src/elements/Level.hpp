#ifndef LEVEL_HPP
#define LEVEL_HPP 

#include "../datas/EnemyList.hpp"
#include "../datas/Walls.hpp"
#include "../datas/Doors.hpp"
#include "../datas/Bonuses.hpp"

class Level {
    public:
        vector<Bullet> playerBulletVector; 
        vector<Bullet> enemyBulletVector; 
        vector<Enemy> enemyVector;
        vector<vector<int>> structure;
        vector<Wall> wallVector;
        vector<Element> doorVector;
        vector<MoneyBonus> moneyVector;
        Shooter * player;
        
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