#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <signal.h>

struct lineInst {
    int posx, curry, inity;
    int len;
    bool finished;
    int totlen;
};

volatile sig_atomic_t resize_flag = 0;

void handle_resize(int sig) {
    (void)sig;
    resize_flag = 1;
}

void init_lines(struct lineInst *lines, bool *activeline, int width, int height) {
    for (int i = 0; i < width; i++) {
        activeline[i] = false;
    }
    
    for (int i = 0; i < width; i++) {
        lines[i].posx = i;
        activeline[i] = true;
        
        int starty = rand() % (height > 10 ? height - 10 : 1);
        lines[i].inity = starty;
        lines[i].curry = starty;
        lines[i].len = rand() % 15 + 5;
        lines[i].totlen = 0;
        lines[i].finished = false;
    }
}

int main() {
    int y, x;
    struct lineInst *lines = NULL;
    bool *activeline = NULL;
    int current_width = 0, current_height = 0;
    
    srand(time(NULL));
    
    signal(SIGWINCH, handle_resize);
    
    initscr();
    curs_set(0);
    nodelay(stdscr, TRUE);
    
    if (has_colors()) {
        start_color();
        assume_default_colors(-1, -1);
        init_pair(1, COLOR_GREEN, -1);
        init_pair(2, COLOR_WHITE, -1);
    }
    
    while (1) {
        if (resize_flag || lines == NULL) {
            resize_flag = 0;
            endwin();
            refresh();
            clear();
            
            getmaxyx(stdscr, y, x);
            
            if (x != current_width || y != current_height) {
                free(lines);
                free(activeline);
                
                current_width = x;
                current_height = y;
                
                lines = malloc(x * sizeof(struct lineInst));
                activeline = malloc(x * sizeof(bool));
                
                if (!lines || !activeline) {
                    endwin();
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(1);
                }
                
                init_lines(lines, activeline, x, y);
            }
        }
        
        usleep(30000);
        
        for (int i = 0; i < current_width; i++) {
            if (lines[i].curry >= current_height) {
                lines[i].finished = true;
                if (lines[i].curry > 0 && lines[i].posx < current_width) {
                    if (has_colors()) attron(COLOR_PAIR(1));
                    int ch = mvinch(lines[i].curry - 1, lines[i].posx) & A_CHARTEXT;
                    mvaddch(lines[i].curry - 1, lines[i].posx, ch);
                    if (has_colors()) attroff(COLOR_PAIR(1));
                }
            }
            
            if (lines[i].totlen >= lines[i].len && lines[i].inity < current_height) {
                mvaddch(lines[i].inity, lines[i].posx, ' ');
                lines[i].inity++;
            }
            
            if (lines[i].inity >= current_height) {
                lines[i].inity = 0;
                lines[i].curry = 0;
                lines[i].len = rand() % 15 + 5;
                lines[i].totlen = 0;
                lines[i].finished = false;
            }
            
            if (!lines[i].finished && lines[i].curry < current_height && lines[i].posx < current_width) {
                int random_char = rand() % 94 + 33;
                
                if (has_colors()) attron(COLOR_PAIR(2));
                mvaddch(lines[i].curry, lines[i].posx, random_char);
                if (has_colors()) attroff(COLOR_PAIR(2));
                
                if (lines[i].curry > 0) {
                    if (has_colors()) attron(COLOR_PAIR(1));
                    int ch = mvinch(lines[i].curry - 1, lines[i].posx) & A_CHARTEXT;
                    mvaddch(lines[i].curry - 1, lines[i].posx, ch);
                    if (has_colors()) attroff(COLOR_PAIR(1));
                }
                
                lines[i].curry++;
                lines[i].totlen++;
            }
        }
        
        refresh();
        
        int ch = getch();
        if (ch == 'q' || ch == 'Q' || ch == 27) break;
    }
    
    free(lines);
    free(activeline);
    endwin();
    return 0;
}
