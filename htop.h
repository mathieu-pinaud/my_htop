#ifndef HTOP_H
#define HTOP_H

#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/resource.h>

typedef struct active_process {
    char *name;
    char *pid;
    double cpu_time;
    double v_mem;
    double p_mem;
    double run_time;
    struct active_process *next;
    struct active_process *prev;
} t_active_process;

t_active_process *create_process(char *name, char *pid);
void add_process(t_active_process **head, t_active_process *new);
void free_processes(t_active_process *head);
void print_processes(t_active_process *head, WINDOW *data_win, int reverse);
int count_processes(t_active_process *head);
void swap(t_active_process *a, t_active_process *b);
void sort_menu(t_active_process *head, char *sort_type);

#endif // HTOP_H
