#include <ncurses.h>
#include "Player.cpp"

class GameLoop {
    
    int main() {
        // Initialize ncurses
        initscr();
        cbreak();
        noecho();
        curs_set(0);


        // initialize player
        Player player = Player(0, '&');

        // Create a 30x30 window
        WINDOW *win = newwin(30, 30, 0, 0);


        // Game loop
        while (true) {
            // Update object positions based on velocities

            // Check for collisions

            // Resolve collisions and handle consequences

            // Clear the screen
            clear();
            werase(win);

            int win_height, win_width;
            getmaxyx(win, win_height, win_width);

            // Calculate the center position
            int center_y = win_height / 2;
            int center_x = win_width / 2;

            // Draw the '&' in the center of the window
            mvwaddch(win, center_y, center_x, '&');

            // Refresh the window to display the changes
            wrefresh(win);

            // Add a delay to control the loop speed
            napms(100); // 100 milliseconds delay
            // Render the updated scene

            // Refresh the screen
            refresh();

            // Delay to control the game loop speed
            // e.g., napms(100); for 100 milliseconds delay
        }

        // Clean up ncurses
        endwin();
        return 0;
    }
};
