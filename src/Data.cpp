#include "Data.hpp"

// Name = Bullet(int id, string name, char character, double damage, int maxDist, int speed, bool bought, int cost, bool equipped)
Bullet fionda =     Bullet("Fionda",     'o', 1, 10, true, 0, true);
Bullet pistolina =  Bullet("Pistolina",  '-', 2, 5, false, 10, false);
Bullet pistola =    Bullet("Pistola",    '-', 5, 6, false, 50, false);
Bullet mitra =      Bullet("Mitra",      '=', 10, 8, false, 100, false);
Bullet cannone =    Bullet("Cannone",    'O', 20, 6, false, 200, false);
Bullet laser =      Bullet("Laser",      '*', 40, 10, false, 500, false);
Bullet ultraLaser = Bullet("Ultra Laser",'S', 100, 10000, false, 1000, false); 

Bullet rock =           Bullet("Roccia", 'o', 2, 4, false, 0, false);
Bullet bigRock =        Bullet("Grande Roccia", 'o', 5, 4, false, 0, false);
Bullet axe =            Bullet("Ascia", '-', 10, 6, false, 0, false);
Bullet superAxe =       Bullet("Super Ascia", '-', 20, 6, false, 0, false);
Bullet fireball =       Bullet("Ascia", '*', 50, 10, false, 0, false);
Bullet greatFireball =  Bullet("Super Ascia", '%', 100, 15, false, 0, false);

Enemy goblin =          Enemy('x', 1, 1, &rock, 15, 10);
Enemy greatGoblin =     Enemy('X', 5, 3, &bigRock, 15, 10);
Enemy ogre =            Enemy('O', 20, 10, &axe, 15, 10);
Enemy greatOgre =       Enemy('G', 50, 25, &superAxe, 15, 10);
Enemy dragoon =         Enemy('D', 200, 50, &fireball, 15, 10);
Enemy greatDragoon =    Enemy('Y', 1000, 100, &greatFireball, 15, 10);

Wall baseWall = Wall(1, 'H');
Wall hardWall = Wall(100, 'W');

Wall moneyWall = Wall(1, '$');

Door door = Door('@');

vector<Bullet> playerWeapons = {
    fionda,
    pistolina,
    pistola,
    mitra,
    cannone,
    laser,
    ultraLaser
};

vector<Enemy> enemies = {
    goblin,
    greatGoblin,
    ogre,
    greatOgre,
    dragoon,
    greatDragoon
};

vector<Wall> walls = {
    baseWall, 
    hardWall,
};
