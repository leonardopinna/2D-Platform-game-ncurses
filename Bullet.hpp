#ifndef BULLET_HPP
#define BULLET_HPP

#include <string>
using namespace std;

class Bullet {
    private:
        int id;
        char symbol; 
        int x; 
        int y; 
        double damage;
        string name;
        int direction;
        int maxDistance;
        int cost;
        bool bought;
        int speed;

    public: 
        Bullet();
        Bullet(int id, string n, char s, double d, int m, int sp, bool b, int c);

        // getters
        int getId();        
        string getName();        
        char getSymbol();
        int getX();        
        int getY(); 
        int getCost();              
        int getDamage();        
        int getSpeed();
        bool isBought();         
        int getMaxDistance();
        int getDirection();

        // setters            
        void setCost(int c);              
        void setAtk(int a);        
        void setSpeed(int s);
        void setIsBought(bool b); 
        void setX(int xPos);        
        void setY(int yPos);
        void setDirection(int dir);     

        // Actions
        void move();
};

#endif // BULLET_HPP