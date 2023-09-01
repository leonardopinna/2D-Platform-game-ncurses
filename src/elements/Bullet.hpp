#ifndef BULLET_HPP
#define BULLET_HPP

#include "Movable.hpp"
#include <string>

using namespace std; 

class Bullet : public Movable {
    private: 
        string name;
        int damage;
        int maxDistance;
        int cost;
        bool bought;
        bool equipped; 

    public:
        Bullet(string n, char s, int d, int m, bool b, int c, bool eq);

        // getters
        string getName();                
        int getCost();              
        int getDamage();
        int getMaxDistance();        
        bool isBought();         
        bool isEquipped(); 

        // setters
        void setCost(int c);              
        void setDamage(int a);
        void setIsBought(bool b); 
        void setEquipped(bool b);
        void reduceDistance();

        // Actions
        void move();
};

#endif