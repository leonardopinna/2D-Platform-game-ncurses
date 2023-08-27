#include "Data.hpp"

// Name = Bullet(int id, string name, char character, double damage, int maxDist, int speed, bool bought, int cost, bool equipped)
Bullet fionda =     Bullet(0, "Fionda",     'o', 1, 10, true, 0, true);
Bullet pistolina =  Bullet(1, "Pistolina",  '-', 2, 5, false, 10, false);
Bullet pistola =    Bullet(2, "Pistola",    '-', 5, 6, false, 50, false);
Bullet mitra =      Bullet(3, "Mitra",      '=', 10, 8, false, 100, false);
Bullet cannone =    Bullet(4, "Cannone",    'O', 20, 6, false, 200, false);
Bullet laser =      Bullet(5, "Laser",      '*', 40, 10, false, 500, false);
Bullet ultraLaser = Bullet(6, "Ultra Laser",'S', 100, 10000, false, 1000, false);

vector<Bullet> playerWeapons = {
    fionda,
    pistolina,
    pistola,
    mitra,
    cannone,
    laser,
    ultraLaser
}; 

Bullet rock = Bullet(0, "Roccia", 'o', 2, 4, false, 0, false);
Bullet bigRock = Bullet(1, "Grande Roccia", 'o', 5, 4, false, 0, false);
Bullet axe = Bullet(2, "Ascia", '-', 10, 6, false, 0, false);
Bullet superAxe = Bullet(3, "Super Ascia", '-', 20, 6, false, 0, false);
Bullet fireball = Bullet(4, "Ascia", '*', 50, 10, false, 0, false);
Bullet greatFireball = Bullet(5, "Super Ascia", '%', 100, 15, false, 0, false);

Enemy goblin = Enemy('x', 1, 1, &rock);
Enemy greatGoblin = Enemy('X', 5, 3, &bigRock);
Enemy ogre = Enemy('O', 20, 10, &axe);
Enemy greatOgre = Enemy('G', 50, 25, &superAxe);
Enemy dragoon = Enemy('D', 200, 50, &fireball);
Enemy greatDragoon = Enemy('Y', 1000, 100, &greatFireball);

vector<Enemy> enemies = {
    goblin,
    greatGoblin,
    ogre,
    greatOgre,
    dragoon,
    greatDragoon
};

Wall baseWall = Wall(1, 'H');
Wall hardWall = Wall(100, 'W');

vector<Wall> walls = {
    baseWall, 
    hardWall,
};

Wall moneyWall = Wall(1, '$');

Door door = Door('@');
