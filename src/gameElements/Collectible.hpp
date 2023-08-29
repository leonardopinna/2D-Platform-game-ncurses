#ifndef Collectible_HPP
#define Collectible_HPP

#include "Element.hpp"

class Collectible {
    private: 
        int value;

    public: 
        Collectible(int v);  

        int getValue();

        void setValue(int amount);           

};

#endif