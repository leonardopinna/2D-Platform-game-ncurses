# include <ncurses.h>
#include "Player.cpp"
using namespace std;

const int HEIGHT = 10;
const int WIDTH = 50;
int main() {
        // Initialize ncurses
        initscr();
        cbreak();
        noecho();
        curs_set(0);


        // initialize player
        Player player = Player(0, '&');


        // Create a 30x30 window
        refresh();
        WINDOW *win = newwin(HEIGHT, WIDTH, 0, 0);
        keypad(win, TRUE);
        box( win, 'X', 'X' );
        wrefresh(win);


        // Game loop
        while (true) {

            char ch = getch();

            // Handle user input
            switch (ch) {
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
                case 'q':
                case 'Q':
                    break;

                // Handle other keys as needed

                default:
                    // Handle other keys or do nothing
                    break;
            }
            // Update object positions based on velocities

            // Check for collisions

            // Resolve collisions and handle consequences

            // Clear the screen
            clear();
            wclear(win);


            box(win, 0, 0);

            int win_height, win_width;
            getmaxyx(win, win_height, win_width);

            // Calculate the center position
            int center_y = win_height / 2;
            int center_x = win_width / 2;

            // Draw the '&' in the center of the window
            mvwaddch(win, player.getY(), player.getX(), '&');

            // Refresh the window to display the changes
            refresh();
            wrefresh(win);

            // Add a delay to control the loop speed
            napms(200); // 100 milliseconds delay
            // Render the updated scene

            // Refresh the screen
            // refresh();

            // Delay to control the game loop speed
            // e.g., napms(100); for 100 milliseconds delay
        }

        // Clean up ncurses
        endwin();
        return 0;
    }
