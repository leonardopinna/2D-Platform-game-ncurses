#include "Level.hpp"

Level::Level(int level, vector<vector<int>> s): structure(s) {

    vector<int> enemyQ(enemies.size(), 0);

    // Generate prev door
    this->doorVector.push_back(door);
    this->doorVector[0].setX(1);
    this->doorVector[0].setY(rand() % (HEIGHT - 2) + 1);
    
    // Generate next door
    this->doorVector.push_back(door);
    this->doorVector[1].setX(WIDTH - 2);
    this->doorVector[1].setY(rand() % (HEIGHT - 2) + 1);

    // Generates walls 
    for (int i = 0; i < structure.size(); i++) {
        wallVector.push_back(baseWall);
        wallVector[i].setX(structure[i][0]);
        wallVector[i].setY(structure[i][1]);
    }  

    // Generate money icon '$'
    for (int i = 0; i < maxMoneyBonusElementsPerLevel; i++) {
        
        vector<int> coords = findFreePosition(1, WIDTH - 2, 1, HEIGHT - 2);

        this->moneyVector.push_back(moneyWall);
        this->moneyVector[i].setX(coords[0]);
        this->moneyVector[i].setY(coords[1]);
    }

    // Generates enemies
    enemyQ[0] = max(0, min(maxEnemiesPerType, level));
    enemyQ[1] = max(0, min(maxEnemiesPerType, level - 5));
    enemyQ[2] = max(0, min(maxEnemiesPerType, (level-10))/2 + 1);
    enemyQ[3] = max(0, min(maxEnemiesPerType, (level-20))/2 + 1);
    enemyQ[4] = max(0, min(maxEnemiesPerType, (level-30))/2 + 1);
    enemyQ[5] = max(0, min(maxEnemiesPerType, (level-40))/2 + 1);
    enemyQ[6] = max(0, min(maxEnemiesPerType, (level-50))/2 + 1);

    for (int i = 0; i < enemies.size(); i++){
        for (int j = 0; j < enemyQ[i]; j++) {

            vector<int> coords = findFreePosition(4, WIDTH - 5, 1, HEIGHT - 2);

            this->enemyVector.push_back(enemies[i]);
            this->enemyVector[enemyVector.size()-1].setX(coords[0]);
            this->enemyVector[enemyVector.size()-1].setY(coords[1]);
        }
    }
}

bool Level::isFreePositionToDraw(int x, int y) {
    for (Wall w : wallVector) {
        if (w.getX() == x && w.getY() == y) return false; 
    }
    for (Door w : doorVector) {
        if (w.getX() == x && w.getY() == y) return false; 
    }
    return isValidPosition(x, y);
}

bool Level::isValidPosition(int x, int y) {
    return (x > 0 && x < WIDTH - 1 && y > 0 && y < HEIGHT - 1);
}

bool Level::isFreePositionToGo(int x, int y) {
    for (Wall w : wallVector) {
        if (w.getX() == x && w.getY() == y) return false; 
    }
    return isValidPosition(x,y);
}

vector<int> Level::findFreePosition(int wStart, int wEnd, int hStart, int hEnd) {
    int XX, YY;
    do {
        XX = rand() % wEnd + wStart ;
        YY = rand() % hEnd + hStart;
    } while (!isFreePositionToDraw(XX, YY));
    return vector<int> {XX, YY};
}