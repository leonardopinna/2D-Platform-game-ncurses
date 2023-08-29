#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Shooter.hpp"
#include "Collectible.hpp"

#include "Bullet.hpp"
#include "../Parameters.hpp"

class Enemy : public Shooter, public Collectible {
    private: 
        int shootProb;
        int moveProb;
    public: 
        Enemy(char ch, int life, int value, Bullet * bullet, int shootProb, int moveProb);
};

#endif