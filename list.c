#include "htop.h"

t_active_process *create_process(char *name, char *pid) {
    t_active_process *new = malloc(sizeof(t_active_process));
    new->name = strdup(name);
    new->pid =  strdup(pid);
    new->next = NULL;
    new->prev = NULL;
    return new;
}

void add_process(t_active_process **head, t_active_process *new) {
    if (*head == NULL) {
        *head = new;
        return;
    }
    t_active_process *tmp = *head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new;
    new->prev = tmp;
}

void print_processes(t_active_process *head) {
    t_active_process *tmp = head;
    while (tmp != NULL) {
        printw("PID: %s\tNAME:%s\n", tmp->pid, tmp->name);
        tmp = tmp->next;
    }
}

void free_processes(t_active_process *head) {
    t_active_process *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->name);
        free(tmp->pid);
        free(tmp);
    }
}