#include <cstdlib>

#include "Enemy.hpp"

Enemy::Enemy(char ch, int life, int value, Bullet * bullet, int shootProb, int moveProb) : Collectible(value), Shooter(ch, life, Direction::LEFT, bullet), shootProb(shootProb), moveProb(moveProb) {};

int Enemy::getShootProb() {
    return this->shootProb;
};
int Enemy::getMoveProb() {
    return this->moveProb;
};
