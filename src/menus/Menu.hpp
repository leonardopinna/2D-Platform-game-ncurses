#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>
#include <fstream>
#include <vector>
#include <string>

#include "../PlayerManager.hpp"

#include "MenuItems.hpp"
#include "../Parameters.hpp"

using namespace std;

enum class GameState {
    MainMenu,
    Market,
    Purchasing,
    Home,
    Playing,
    GameOver, 
    LoadGame, 
    SaveGame,
    ExitGame
};

class Menu {

    private:
        PlayerManager * playerManager;

        int selectedItem;
        int numItems;
        char* menu[5];
        GameState state;  

    public:
        Menu(char* menu[], int n) {
            for (int i = 0; i < n; ++i) {
            this->menu[i] = menu[i];
            }
            this->selectedItem = 0; 
            this->numItems = n;  
        };

        // getters
        int getSelectedItem() {
            return this->selectedItem;
        }
        int getNumItems() {
            return this->numItems;
        }
        GameState getState() {
            return this->state; 
        }
        PlayerManager * getPlayerManager() {
            return this->playerManager; 
        }

        // setters
        void setSelectedItem(int x) {
            this->selectedItem = x;
        }
        void setState(GameState g) {
            this->selectedItem = 0; 
            this->state = g; 
        }
        void setPlayerManager(PlayerManager * p) {
            this->playerManager = p;
        }
        
        // actions
        void selectUp() {
            this->selectedItem = (this->selectedItem - 1 + this->numItems) % this->numItems; 
        }

        void selectDown() {
            this->selectedItem = (this->selectedItem + 1) % this->numItems;;
        }

        GameState run(GameState gs, int dist, int money, int life, char* name) {
            this->state = gs; 
            handleInput(); 
            update();
            render(dist, money, life, name);
             
            return this->state;  
        }

        virtual void handleInput() = 0;
        virtual void update() = 0;
        virtual void render(int dist, int money, int life, char* name) = 0;

        void renderMenu() {
            for (int i = 0; i < this->numItems; ++i) {
                if (i == this->selectedItem) {
                    attron(A_REVERSE); // Highlight the selected item
                }
                mvprintw(1 + i + 1, 1, this->menu[i]);
                attroff(A_REVERSE);
            }
        };

        void renderBasePrompt(int y, int x) {   
            mvprintw(y, x, "'w' : Muovi verso l'alto");
            mvprintw(y + 1, x, "'s' : Muovi verso il basso");
            mvprintw(y + 2, x, "'l' : Seleziona");
        };

        void renderPlayPrompt(int y, int x) {
            mvprintw(y + 0, x, "'w' : Muovi verso l'alto");
            mvprintw(y + 1, x, "'s' : Muovi verso il basso");
            mvprintw(y + 2, x, "'a' : Muovi verso sinistra");
            mvprintw(y + 3, x, "'d' : Muovi verso destra");
            mvprintw(y + 4, x, "'l' : Spara");
            mvprintw(y + 5, x, "'q' : Termina partita");
        }

        void renderStats() {};

        void renderGameStats(int dist, int money, int life, char* name) {
            mvprintw(2, dist, "MONETE    : %d", money);
            mvprintw(4, dist, "VITA      : %d", life);
            mvprintw(6, dist, "ARMA      : %s", name);
        }


        virtual ~Menu() {};

};

#endif
