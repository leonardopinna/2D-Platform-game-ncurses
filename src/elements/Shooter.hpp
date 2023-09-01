#ifndef Shooter_HPP
#define Shooter_HPP

#include "Movable.hpp"
#include "Destructible.hpp"
#include "Bullet.hpp"

class Shooter : public Destructible, public Movable {
    private: 
        Bullet * bullet;

    public:
        Shooter(char ch, int l, Direction d, Bullet * b);

        // getters
        Bullet * getBullet();

        // setters 
        void setBullet(Bullet * b);

        // actions
        Bullet shoot();
};

#endif