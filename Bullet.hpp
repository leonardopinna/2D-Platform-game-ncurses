#ifndef BULLET_HPP
#define BULLET_HPP

class Bullet {
    private:
        int id;
        char symbol; 
        int x; 
        int y; 
        double damage;
        const char* name;
        int direction;
        int maxDistance;
        int cost;
        bool bought;
        int speed;
        bool equipped; 

    public:
        Bullet(); 
        Bullet(int id, const char* n, char s, double d, int m, bool b, int c, bool eq);

        // getters
        int getId();        
        const char* getName();        
        char getSymbol();
        int getX();        
        int getY(); 
        int getCost();              
        int getDamage();        
        int getSpeed();
        bool isBought();         
        int getMaxDistance();
        int getDirection();
        bool isEquipped(); 

        // setters            
        void setCost(int c);              
        void setAtk(int a);        
        void setSpeed(int s);
        void setIsBought(bool b); 
        void setX(int xPos);        
        void setY(int yPos);
        void setDirection(int dir);
        void setEquipped(bool b);    

        // Actions
        void move();
};

#endif