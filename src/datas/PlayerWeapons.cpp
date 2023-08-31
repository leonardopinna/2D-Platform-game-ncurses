#include "PlayerWeapons.hpp"

Bullet fionda =     Bullet("Fionda",     'o', 1, 10, true, 0, true);
Bullet pistolina =  Bullet("Pistolina",  '-', 2, 5, false, 10, false);
Bullet pistola =    Bullet("Pistola",    '-', 5, 6, false, 50, false);
Bullet mitra =      Bullet("Mitra",      '=', 10, 8, false, 100, false);
Bullet cannone =    Bullet("Cannone",    'O', 20, 6, false, 200, false);
Bullet laser =      Bullet("Laser",      '*', 40, 10, false, 500, false);
Bullet ultraLaser = Bullet("Ultra Laser",'S', 100, 10000, false, 1000, false); 

vector<Bullet> playerWeapons = {
    fionda,
    pistolina,
    pistola,
    mitra,
    cannone,
    laser,
    ultraLaser
};
