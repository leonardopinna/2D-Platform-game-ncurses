#include "Movable.hpp"

Movable::Movable(char ch, Direction d) : Element(ch), direction(d) {};

// getters                
Direction Movable::getDirection() {
    return this->direction;
};

// setters
void Movable::setDirection(Direction d) {
    this->direction = d; 
};        

// actions
void Movable::moveUp() {
    this->setY(this->getY()-1);
    this->direction = Direction::UP;
};        
void Movable::moveLeft() {
    this->setX(this->getX()-1);
    this->direction = Direction::LEFT;
};        
void Movable::moveRight() {
    this->setX(this->getX()+1);
    this->direction = Direction::RIGHT;
};        
void Movable::moveDown() {
    this->setY(this->getY()+1);
    this->direction = Direction::DOWN;
};  

