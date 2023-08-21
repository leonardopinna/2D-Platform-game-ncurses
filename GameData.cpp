#include "GameData.hpp"

// Name = Bullet(int id, string name, char character, double damage, int maxDist, int speed, bool bought, int cost)
Bullet fionda =     Bullet(0, "Fionda",     'o', 1, 3, 50, true, 0);
Bullet pistolina =  Bullet(1, "Pistolina",  '-', 2, 5, 50, false, 10);
Bullet pistola =    Bullet(2, "Pistola",    '-', 5, 6, 50, false, 50);
Bullet mitra =      Bullet(3, "Mitra",      '=', 10, 8, 50, false, 100);
Bullet cannone =    Bullet(4, "Cannone",    'O', 20, 6, 50, false, 200);
Bullet laser =      Bullet(5, "Laser",      '*', 40, 10, 50, false, 500);
Bullet ultraLaser = Bullet(6, "Ultra Laser",'S', 100, 15, 500, false, 1000);

Bullet playerWeapons[7] = {fionda, pistolina, pistola, mitra, cannone, laser, ultraLaser}; 

Bullet rock = Bullet(0, "Roccia", 'o', 2, 4, 50, true, 0);

Enemy goblin = Enemy('x', 1, rock);
