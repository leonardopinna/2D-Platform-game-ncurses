#include "MenuItems.hpp"

char* mainMenuItems[] = {
    "Nuovo Gioco",
    "Carica Partita",
    "Esci"
};
char* gameOverItems[] = {
    "Nuova Partita",
    "Menu principale", 
    "Esci"
};
char* homeItems[] = {
    "Nuova Partita",
    "Negozio", 
    "Salva Partita",
    "Esci"
};

int numMainMenuItems = sizeof(mainMenuItems) / sizeof(mainMenuItems[0]);
int numGameOverItems = sizeof(gameOverItems) / sizeof(gameOverItems[0]);
int numHomeItems = sizeof(homeItems) / sizeof(homeItems[0]);

