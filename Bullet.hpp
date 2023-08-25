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

    public:
        Bullet(); 
        Bullet(int id, const char* n, char s, double d, int m, int sp, bool b, int c);

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

#endif