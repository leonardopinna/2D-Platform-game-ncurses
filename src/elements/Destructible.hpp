#ifndef DESTRUCTIBLE_HPP
#define DESTRUCTIBLE_HPP

class Destructible {
    private:  
        int life;

    public: 
        Destructible(int l);

        // Getters       
        int getLife(); 

        // setters        
        void setLife(int amount); 

        // actions
        void reduceLife(int amount);       

};

#endif