#include "PlayerWeapons.hpp"

Bullet sasso =      Bullet("Sasso",      '"', 1, 3, true, 0, true);
Bullet fionda =     Bullet("Fionda",     'o', 1, 5, false, 5, false);
Bullet pistolina =  Bullet("Pistolina",  '-', 2, 6, false, 10, false);
Bullet pistola =    Bullet("Pistola",    '-', 5, 7, false, 50, false);
Bullet mitra =      Bullet("Mitra",      '=', 10, 8, false, 100, false);
Bullet cannone =    Bullet("Cannone",    'O', 20, 6, false, 200, false);
Bullet laser =      Bullet("Laser",      '*', 40, 10, false, 500, false);
Bullet ultraLaser = Bullet("Ultra Laser",'S', 100, 10000, false, 1000, false); 

vector<Bullet> playerWeapons = {
    sasso,
    fionda,
    pistolina,
    pistola,
    mitra,
    cannone,
    laser,
    ultraLaser
};
