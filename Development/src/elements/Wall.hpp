#ifndef WALL_HPP
#define WALL_HPP

#include "Element.hpp"
#include "Destructible.hpp"

class Wall : public Element, public Destructible {
    public: 
        Wall(int l, char ch);
        Wall(int l, char ch, int x, int y);
};

#endif