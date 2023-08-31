#ifndef MONEY_BONUS_HPP
#define MONEY_BONUS_HPP

#include "Element.hpp"
#include "Collectible.hpp"

class MoneyBonus : public Collectible, public Element {
    private: 
        int value;

    public: 
        MoneyBonus(int v, char ch);  

        int getValue();

        void setValue(int amount);           

};

#endif