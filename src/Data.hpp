#ifndef DATA_HPP
#define DATA_HPP

#include <vector>
using namespace std;

#include "gameElements/Bullet.hpp"
#include "gameElements/Enemy.hpp"
#include "gameElements/Wall.hpp"
#include "gameElements/Door.hpp"

// Player Weapons
extern Bullet fionda;
extern Bullet pistolina;
extern Bullet pistola ;
extern Bullet mitra;  
extern Bullet cannone;
extern Bullet laser;    
extern Bullet ultraLaser;

// Enemy Weapons
extern Bullet rock;
extern Bullet bigRock;
extern Bullet axe;
extern Bullet superAxe;
extern Bullet fireball;
extern Bullet greatFireball;

// Enemies
extern Enemy goblin;
extern Enemy greatGoblin;
extern Enemy ogre;
extern Enemy greatOgre;
extern Enemy dragoon;
extern Enemy greatDragoon;

// Walls
extern Wall baseWall;
extern Wall hardWall;

// Bonus
extern Wall moneyWall;

// Doors
extern Door door;

// Arrays
extern vector<Bullet> playerWeapons;
extern vector<Enemy> enemies;
extern vector<Wall> walls;

#endif
