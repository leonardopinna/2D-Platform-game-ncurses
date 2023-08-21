#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Bullet.hpp"

class Enemy {
    private: 
        int x; 
        int y; 
        char symbol;
        int level;
        int atk;
        int def; 
        int direction;
        int size;
        Bullet bullet;

    public: 
        Enemy(char symb, int sz, Bullet b);

        // Getters
        int getX();        
        int getY();             
        char getSymbol();        
        int getLevel();        
        int getAtk();        
        int getDef();

        // setters
        void setX(int xPos);        
        void setY(int yPos);            
        void setSymbol(char s);        
        void setLevel(int l);        
        void setAtk(int a);        
        void setDef(int d);       

        // actions
        Bullet shoot();

        void moveUp();        
        void moveLeft();        
        void moveRight();        
        void moveDown();

        void move();

};

#endif