#include "Wall.hpp"

Wall::Wall(int l, char ch) : Element(ch), Destructible(l) {};

Wall::Wall(int l, char ch, int x, int y) : Element(ch), Destructible(l)  {
    setX(x); 
    setY(y); 
};