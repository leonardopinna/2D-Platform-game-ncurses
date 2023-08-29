#ifndef BULLET_HPP
#define BULLET_HPP

#include "Movable.hpp"

class Bullet : public Movable {
    private: 
        char * name;
        double damage;
        int maxDistance;
        int cost;
        bool bought;
        bool equipped; 

    public:
        Bullet(char* n, char s, double d, int m, bool b, int c, bool eq);

        // getters
        char * getName();                
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