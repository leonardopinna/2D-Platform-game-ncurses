#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Movable.hpp"
#include "Destructible.hpp"
#include "../Data.hpp"
#include "../Parameters.hpp"

class Player : public Shooter {
    public: 
        Player(char ch, int l, Direction d, Bullet * b);
};

#endif