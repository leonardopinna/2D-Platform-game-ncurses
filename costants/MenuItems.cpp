#include "MenuItems.hpp"

const char* mainMenuItems[] = {
    "Nuovo Gioco",
    "Carica Partita",
    "Esci"
};
const char* gameOverItems[] = {
    "Nuova Partita",
    "Mercato", 
    "Esci"
};
const char* marketItems[] = {
    "Nuova Partita",
    "Negozio", 
    "Salva Partita",
    "Esci"
};

int numMainMenuItems = sizeof(mainMenuItems) / sizeof(mainMenuItems[0]);
int numGameOverItems = sizeof(gameOverItems) / sizeof(gameOverItems[0]);
int numMarketItems = sizeof(marketItems) / sizeof(marketItems[0]);

