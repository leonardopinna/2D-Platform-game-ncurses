#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>

#include "../enums/GameState.hpp"

#include "../controllers/PlayerManager.hpp"

#include "../datas/Parameters.hpp"

#include "MenuItems.hpp"

class Menu {
    private:
        PlayerManager * playerManager;

        int selectedItem;

        vector<string> menu;
        vector<GameState> link;

        int timer; 
        string message; 
        string title; 

        GameState state;  

    public:
        Menu(
            string title,
            vector<string> menu,
            vector<GameState> link,
            string msg,
            PlayerManager * p
        );

        // getters
        string getTitle();
        string getMessage();  
        int getTimer(); 
        int getSelectedItem();
        GameState getState();
        PlayerManager * getPlayerManager();

        // setters
        void setTimer(int x); 
        void setSelectedItem(int x);
        void setState(GameState g);
        void setPlayerManager(PlayerManager * p);
        void decreaseTimer(); 
        
        // actions
        void selectUp();
        void selectDown();
        void selectButton(); 

        GameState run(GameState gs);

        void handleInput();

        void render();

        void renderMenu();
        void renderPrompt(int y, int x);

        virtual ~Menu() {};

};

#endif
