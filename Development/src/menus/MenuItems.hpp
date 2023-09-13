#ifndef MENU_ITEMS_HPP
#define MENU_ITEMS_HPP

#include <vector>
#include <string>

using namespace std; 

#include "../enums/GameState.hpp"

// Titles
extern string titleMainMenu; 
extern string titleHome;
extern string titleGameOver;
extern string titleMarket;

// Messages
extern string messageMainMenu;
extern string messageHomeMenu;
extern string errorMarket;

// Links to Gamestates of Menu Items
extern vector<GameState> mainMenuLinks;
extern vector<GameState> homeLinks;
extern vector<GameState> gameOverLinks;

// Menu Items
extern vector<string> mainMenuItems;
extern vector<string> gameOverItems;
extern vector<string> homeItems;
extern vector<string> marketItems; 

// Number of menu items
extern int numMainMenuItems;
extern int numGameOverItems;
extern int numHomeItems;
extern int numMarketItems; 

extern int numWeapons;

extern int weaponsCostDistance;


#endif