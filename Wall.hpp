#ifndef WALL_HPP
#define WALL_HPP

class Wall {
    private: 
        int x; 
        int y; 
        int life;
        char symbol;

    public: 
        Wall(int l, char s);

        // Getters
        int getX() const;        
        int getY() const;        
        int getLife();        
        char getSymbol();        

        // setters
        void setX(int xPos);        
        void setY(int yPos);        
        void setLife(int amount);    
        void setSymbol(char s);  

        // actions
        void reduceLife(int amount);        

};

#endif