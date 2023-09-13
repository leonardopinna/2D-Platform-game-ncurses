#ifndef Movable_HPP
#define Movable_HPP

#include "Element.hpp"
#include "../enums/Direction.hpp"

class Movable : public Element {
    private: 
        Direction direction;

    public: 
        Movable(char ch, Direction d);

        // getters        
        Direction getDirection(); 
        
        // setters
        void setDirection(Direction d);

        // actions
        void moveUp();        
        void moveLeft();        
        void moveRight();        
        void moveDown();
};

#endif