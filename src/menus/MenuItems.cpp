#include "MenuItems.hpp"

// Main menu
string titleMainMenu = "nWARRIOR GAME";
string messageMainMenu = "NESSUNA PARTITA SALVATA!"; 

vector<string> mainMenuItems = {
    "Nuovo Gioco",
    "Carica Partita",
    "Esci"
};

vector<GameState> mainMenuLinks = {
    GameState::Home,
    GameState::LoadGame, 
    GameState::ExitGame
};

// Home menu
string titleHome = "BENVENUTO! INIZIA UNA PARTITA O VAI AL NEGOZIO!";
string messageHomeMenu = "PARTITA SALVATA!";
vector<string> homeItems = {
    "Nuova Partita",
    "Negozio", 
    "Salva Partita",
    "Esci"
};

vector<GameState> homeLinks = {
    GameState::Playing,
    GameState::Market,
    GameState::SaveGame, 
    GameState::MainMenu
};

// GameOver menu
string titleGameOver = "GAME OVER: HAI PERSO!";
vector<string> gameOverItems = {
    "Nuova Partita",
    "Menu principale", 
};

vector<GameState> gameOverLinks = {
    GameState::Playing,
    GameState::Home, 
};

// Market menu
string titleMarket = "COMPRA ARMI O VITA";
string errorMarket = "SOLDI INSUFFICIENTI!";



