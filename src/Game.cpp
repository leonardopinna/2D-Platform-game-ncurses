#include "Game.hpp"

Game::Game() {
    playerManager = new PlayerManager();
    
    mainMenu = new Menu(
        titleMainMenu,
        mainMenuItems,
        mainMenuLinks,
        messageMainMenu, 
        playerManager
        ); 

    homeMenu = new Menu(titleHome,
        homeItems,
        homeLinks,
        messageHomeMenu,
        playerManager
        ); 

    gameOverMenu = new Menu(
        titleGameOver,
        gameOverItems,
        gameOverLinks, 
        "", 
        playerManager); 
    
    levelMenu = new LevelMenu(playerManager);
    
    marketMenu = new MarketMenu(titleMarket, errorMarket, playerManager); 
    
    currentState = GameState::MainMenu;
};

void Game::run() {
    initilizeScreen();
    while (running) {

        erase(); 
        werase(win); 

        switch (currentState) {
            case GameState::MainMenu:
                currentState = mainMenu->run(currentState);
                break;

            case GameState::Market:
                currentState = marketMenu->run(currentState);
                break;

            case GameState::Home:
                currentState = homeMenu->run(currentState); 
                break;

            case GameState::Playing:
                currentState = levelMenu->run(currentState, win);
                break;

            case GameState::GameOver:
                levelMenu->gameStarted = false; 
                currentState = gameOverMenu->run(currentState); 
                break;
            case GameState::LoadGame:
                this->loadGame();
                break;
            case GameState::SaveGame:
                this->saveGame(); 
                break;
            case GameState::ExitGame:
                this->stopGame();
                break;

            default:
                break;
        } 
        
        // Refresh windows
        wrefresh(win);
        refresh();

        // Frame-rate
        napms(1000/20);
    }
    
    endwin();
}

void Game::loadGame(){
    ifstream inputFile;
    inputFile.open("saveFile.txt");
    if (!inputFile) {
        mainMenu->setTimer(messageTime);
        currentState = GameState::MainMenu;
    } else {
        string line;
        getline(inputFile, line);
        playerManager->setMoney(stoi(line));
        getline(inputFile, line);
        playerManager->setMaxLife(stoi(line));
        int i = 0;
        while (i < playerWeapons.size()) {
            getline(inputFile, line);
            playerWeapons[i].setIsBought(line[0] - '0');
            playerWeapons[i].setEquipped(line[2] - '0');
            if (playerWeapons[i].isEquipped()) {
                playerManager->setWeapon(&playerWeapons[i]);   
            };
            i++;
        }
        getline(inputFile, line);
        playerManager->setRecord(stoi(line));
        currentState = GameState::Home; 
    }
    inputFile.close();
};

void Game::saveGame(){
    ofstream outputFile;
    outputFile.open("saveFile.txt"); 
    outputFile << playerManager->getMoney() << endl;
    outputFile << playerManager->getMaxLife() << endl;
    for (int i = 0; i < playerWeapons.size(); i++) {
        outputFile << playerWeapons[i].isBought() << ":" << playerWeapons[i].isEquipped() << endl;
    }
    outputFile << playerManager->getRecord() << endl;
    outputFile.close();
    homeMenu->setTimer(messageTime);
    currentState = GameState::Home;
};

void Game::stopGame() {
    running = false;
}

void Game::initilizeScreen() {
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    this->win = newwin(HEIGHT, WIDTH, 0, 0);
    keypad(win, true);
    running = true;
};
