#include <ncurses.h>
#include "Player.hpp"
#include "Bullet.hpp"
#include "Market.hpp"
#include <vector>

using namespace std;

const int HEIGHT = 10;
const int WIDTH = 50;

enum class GameState {
    MainMenu,
    Market,
    Playing,
    Paused,
    GameOver
};

const char* menuItems[] = {
    "Nuovo Gioco",
    "Carica Partita",
    "Exit"
};
int selectedItem = 0;
int numItems = sizeof(menuItems) / sizeof(menuItems[0]);
bool gameStarted = false;

GameState currentState = GameState::Playing; // Initial game state

int main() {
        // Initialize ncurses
        initscr();
        cbreak();
        noecho();
        curs_set(0);
        keypad(stdscr, true);
        nodelay(stdscr, true);

        // initialize player
        Player player = Player(0, '&');
        vector<Bullet> bulletvector; 

        // Create a 30x30 window
        refresh();
        WINDOW *win = newwin(HEIGHT, WIDTH, 0, 0);
        keypad(win, TRUE);
        box( win, 'X', 'X' );
        wrefresh(win);

        auto startTime = std::chrono::steady_clock::now();
        const double bulletUpdateTime = 0.1; // Bullet update interval in seconds
        double timeSinceLastBulletUpdate = 0.0;

        // Game loop
        while (true) {

            // Game Logic && DRAW
            int center_y;
            int center_x;

            // Calculate time elapsed since last iteration
            auto currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsedTime = currentTime - startTime;
            startTime = currentTime;

            // Update bullet movement based on time elapsed
            timeSinceLastBulletUpdate += elapsedTime.count();
            while (timeSinceLastBulletUpdate >= bulletUpdateTime) {
                for (auto it = bulletvector.begin() ; it != bulletvector.end(); ) {
                    it->move();
                    if (it->getMaxDistance()==0) {
                        it = bulletvector.erase(it);
                    } else {
                        ++it;
                    }
                }
                timeSinceLastBulletUpdate -= bulletUpdateTime;
            }


            switch (currentState) {
            case GameState::MainMenu:

                clear();
                
                // Print menu items
                for (int i = 0; i < numItems; ++i) {
                    if (i == selectedItem) {
                        attron(A_REVERSE); // Highlight the selected item
                    }
                    mvprintw(i + 1, 1, menuItems[i]);
                    attroff(A_REVERSE);
                }
                
                // Get user input
                switch (getch()) {
                    case 'w':
                        selectedItem = (selectedItem - 1 + numItems) % numItems;
                        break;
                    case 's':
                        selectedItem = (selectedItem + 1) % numItems;
                        break;
                    case 10: // Enter key
                        // Handle menu item selection
                        if (selectedItem == 0) {
                            // Nuova Partita
                            currentState = GameState::Market;
                        } else if (selectedItem == 1) {
                            // Carica Partita
                            Market::loadGame(); 
                            currentState = GameState::Market;
                        } else if (selectedItem == 2) {
                            // Esci
                            endwin(); // Cleanup ncurses
                            return 0;
                        }
                        break;
                }

                refresh();
                wrefresh(win);
                
                break;

            case GameState::Playing:

                if (!gameStarted) {
                    clear();
                    wclear(win);


                    box(win, 0, 0);

                    int win_height, win_width;
                    getmaxyx(win, win_height, win_width);

                    // Calculate the center position
                    center_y = win_height / 2;
                    center_x = win_width / 2;

                    // Draw the '&' in the center of the window
                    mvwaddch(win, player.getY(), player.getX(), '&');

                    // Refresh the window to display the changes
                    refresh();
                    wrefresh(win);

                    gameStarted = true;
                }

                

                // Handle user input
                switch (getch()) {
                    case 'w':
                        if (player.getY() > 1) player.moveUp();
                        break;

                    case 's':
                        if (player.getY() < HEIGHT - 2) player.moveDown();
                        break;

                    case 'a':
                        if (player.getX() > 1) player.moveLeft();
                        break;

                    case 'd':
                        if (player.getX() < WIDTH - 2) player.moveRight();
                        break;

                    case 'l':
                        bulletvector.push_back(player.shoot());
                        break;

                    case 'q':
                    case 'Q':
                        currentState = GameState::MainMenu;
                        gameStarted = false;
                        break;

                    default:
                        // Handle other keys or do nothing
                        break;
                }


                // Game LOGIC
                // for (auto it = bulletvector.begin() ; it != bulletvector.end(); ) {
                //     it->move();
                //     if (it->getMaxDistance()==0) {
                //         it = bulletvector.erase(it);
                //     } else {
                //         ++it;
                //     }
                // }
                
                clear();
                wclear(win);


                box(win, 0, 0);

                int win_height, win_width;
                getmaxyx(win, win_height, win_width);

                // Calculate the center position
                center_y = win_height / 2;
                center_x = win_width / 2;

                // Draw the '&' in the center of the window
                mvwaddch(win, player.getY(), player.getX(), '&');
                for (Bullet b : bulletvector) {
                    mvwaddch(win, b.getY(), b.getX(), b.getSymbol());
                }

                break;

            case GameState::Paused:
                // Handle game paused logic
                break;
            case GameState::GameOver:
                // Handle game over logic
                break;
            }
                       
            refresh();
            wrefresh(win);
            // Add a delay to control the loop speed
            napms(1000/60); 

        }

        // Clean up ncurses
        endwin();
        return 0;
    }
