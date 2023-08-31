#include <cstdlib>

#include "Shooter.hpp"

Shooter::Shooter(char ch, int l, Direction d, Bullet * b) : Destructible(l), Movable(ch, d), bullet(b) {};

// getters
Bullet * Shooter::getBullet() {
    return this->bullet;
}

// setters
void Shooter::setBullet(Bullet * b) {
    this->bullet = b;
}     

// actions
Bullet Shooter::shoot() {
    this->bullet->setDirection(this->getDirection());
    this->bullet->setX(this->getX());
    this->bullet->setY(this->getY());
    return *this->bullet;
};
