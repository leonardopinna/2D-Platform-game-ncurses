#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "../datas/Parameters.hpp"

class Element {
    private: 
        int x; 
        int y; 
        char symbol;

    public: 
        Element(char s);

        // Getters
        int getX() const;
        int getY() const;
        char getSymbol();        

        // setters
        void setX(int xPos);        
        void setY(int yPos);        
        void setSymbol(char s);   

        // bool 
        bool outOfBounds();

        bool collision(Element e);
};

#endif