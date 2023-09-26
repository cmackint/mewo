#include <ncurses.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>

#include "mewo.h"

void run_frame_validation();
WINDOW *create_win(int startx, int starty, int lines, int columns);
void draw_mewo(WINDOW *win, mewo *m, int board_startx, int board_starty);

int main() {	
	initscr();
    raw(); // Disable user input buffering
    noecho(); // Prevents user input from echoing to output
    setlocale(LC_ALL, "");

    // Enable color
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);

    run_frame_validation();

	endwin(); // End curses mode
	
    return EXIT_SUCCESS;
}

void run_frame_validation() {
    WINDOW *win = create_win(0, 0, LINES, COLS);
    int board_startx = 1;
    int board_starty = 1;
    int board_width = COLS - 2;
    int board_height = LINES - 4;

    mewo_config m_conf = {
        .name = "Mewo",
        .wakeup_time_ms = 0,
        .sleep_time_ms = 0
    };
    mewo m = {};

    mewo_init(&m, &m_conf, 0);

    mewo_set_body_frame(&m, MEWO_BODY_FRAME_SIT);
    mewo_set_head_frame(&m, MEWO_HEAD_FRAME_FORWARD);
    mewo_refresh(&m);

    draw_mewo(win, &m, board_startx, board_starty);
    wrefresh(win);

    wgetch(win);
}

void draw_mewo(WINDOW *win, mewo *m, int board_startx, int board_starty) {
    wattron(win, COLOR_PAIR(1));

    for (int row_index = 0; row_index < MEWO_DISPLAY_ROWS; row_index++) {
        for (int col_index = 0; col_index < MEWO_DISPLAY_COLS; col_index++) {
            bool pixel = mewo_get_pixel(m, row_index, col_index);

            if (pixel) {
                mvwaddch(win, board_starty + row_index, board_startx + col_index, ACS_CKBOARD);
            } else {
                mvwaddch(win, board_starty + row_index, board_startx + col_index, '_');
            }
        }
    }

    wattroff(win, COLOR_PAIR(1));
}

WINDOW *create_win(int startx, int starty, int lines, int columns) {
    WINDOW *win = newwin(lines, columns, starty, startx);
    box(win, 0, 0);
    keypad(win, TRUE);
    wrefresh(win);
    return win;
}

