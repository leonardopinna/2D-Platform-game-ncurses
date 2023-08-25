#ifndef DOOR_HPP
#define DOOR_HPP

class Door {
    private: 
        int x; 
        int y; 
        char symbol;

    public: 
        Door(char s);

        // Getters
        int getX() const;
        int getY() const;
        char getSymbol();        

        // setters
        void setX(int xPos);        
        void setY(int yPos);        
        void setSymbol(char s);          

};

#endif