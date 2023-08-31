#include "EnemyList.hpp"

Enemy goblin =          Enemy('x', 1, 1, &rock, 15, 10);
Enemy greatGoblin =     Enemy('X', 5, 3, &bigRock, 15, 10);
Enemy ogre =            Enemy('O', 20, 10, &axe, 15, 10);
Enemy greatOgre =       Enemy('G', 50, 25, &superAxe, 15, 10);
Enemy dragoon =         Enemy('D', 200, 50, &fireball, 15, 10);
Enemy greatDragoon =    Enemy('Y', 1000, 100, &greatFireball, 15, 10);

vector<Enemy> enemies = {
    goblin,
    greatGoblin,
    ogre,
    greatOgre,
    dragoon,
    greatDragoon
};