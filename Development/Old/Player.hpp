#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Shooter.hpp"

class Player : public Shooter {
    public: 
        Player(char ch, int l, Direction d, Bullet * b);
};

#endif