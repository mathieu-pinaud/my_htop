#include "htop.h"

bool is_number(const char *str) {
    int i = 0;

    while (str[i] != '\0') {
        if (!isdigit(str[i])) {
            return false;
        }
        i += 1;
    }
    return true;
}

int select_dirs(const struct dirent *entry) {
    return entry->d_type == DT_DIR && is_number(entry->d_name);
}

t_active_process *get_data() {
    struct dirent **dirList;
    int dirNb = scandir("/proc", &dirList, select_dirs, NULL);
    t_active_process *start = NULL;
    if (dirNb == -1) {
        printw("Error opening /proc");
        return NULL;
    }
    for (int i = 0; i < dirNb; i++) {
        char *procfile;
        char *procname = NULL;
        size_t len = 0;

        asprintf(&procfile, "/proc/%s/comm", dirList[i]->d_name);
        FILE *file = fopen(procfile, "r");
        if (file == NULL) {
            printw("Error opening %s", procfile);
            free(procfile);
            free(dirList[i]);
            continue;
        }
        getline(&procname, &len, file);
        procname[strcspn(procname, "\n")] = '\0';
        t_active_process *new = create_process(procname, dirList[i]->d_name);
        add_process(&start, new);
        free(procfile);
        free(procname);
        free(dirList[i]);
        fclose(file);
    }
    print_processes(start);
    free(dirList);
    return (start);
}

int main(void) {

    int ch = ' ';
    initscr();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    timeout(100);
    int y = 0;
    int x = 0;
    t_active_process *data = get_data();

    while (data != NULL && ch != 'q'){
        move(y, x);
        ch = getch();
        switch(ch) {
            case KEY_UP: y-= 1; break;
            case KEY_DOWN: y+= 1; break;
            case KEY_LEFT: x -= 1; break;
            case KEY_RIGHT: x += 1; break;
            default: break;
        }
        print_processes(data);
        refresh();
        erase();
        data = get_data();
     }
    endwin();
    return 0;
}