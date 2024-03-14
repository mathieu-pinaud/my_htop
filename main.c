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
    free(dirList);
    return (start);
}

int error(int ac, char **av) {
    if (ac != 1 && ac != 2 && ac  != 3) {
        return 1;
    }
    else if (ac >= 2 && strcmp(av[1], "name") != 0 && strcmp(av[1], "pid") != 0 && strcmp(av[1], "cpu_time") != 0 && strcmp(av[1], "v_mem") != 0 && strcmp(av[1], "p_mem") != 0 && strcmp(av[1], "run_time") != 0) {
        return 2;
    }
    if (ac == 3 && strcmp(av[2], "reverse") != 0) {
        return 3;
    }
    return 0;
}

int main(int ac , char **av) {

    int err = error(ac, av);

    if (err != 0) {
        write(1, "Usage: my_htop [name/pid/cpu_time/v_mem/p_mem/run_time] [reverse]\n", 65);
        return 1;
    }

    initscr();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    timeout(100);

    WINDOW *header_win = newwin(1, COLS, 0, 0);
    wprintw(header_win, "%-40s %-10s %-20s %-20s %-20s\n", "Name", "Pid", "Cpu time",/*"Run Time",*/ "Virtual memory", "Physical memory");
    wrefresh(header_win);

    WINDOW *data_pad = newpad(1000, COLS);
    scrollok(data_pad, TRUE);
    keypad(data_pad, TRUE);
    nodelay(data_pad, TRUE);

    int ch = ' ';
    int pad_pos = 0;

    int reverse = ac == 3 && strcmp(av[2], "reverse") == 0 ? 1 : 0;
    t_active_process *data;
    
    while (ch != 'q'){
        data = get_data();
        int total_processes = count_processes(data);
        werase(data_pad);
        //if (ac > 1) {
        //    data = sort_menu(data, av[1]);
        //}
        print_processes(data, data_pad, reverse);
        prefresh(data_pad, pad_pos, 0, 1, 0, LINES - 1, COLS - 1);
        ch = wgetch(data_pad);
        switch(ch) {
            case KEY_UP: if (pad_pos > 0) pad_pos -= 1; break;
            case KEY_DOWN: if (pad_pos < total_processes - LINES + 1) pad_pos += 1; break;
            default: break;
        }
        free_processes(data);
    }
    delwin(data_pad);
    delwin(header_win);
    endwin();
    return 0;
}