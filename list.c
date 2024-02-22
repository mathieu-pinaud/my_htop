#include "htop.h"

void get_stat(t_active_process *process, char *pid) {
    char *stat_path;
    unsigned long utime;
    unsigned long stime;
    unsigned long vsize;
    unsigned long starttime;
    unsigned long uptime;
    long rss;

    asprintf(&stat_path, "/proc/%s/stat", pid);
    FILE *file = fopen(stat_path, "r");
    if (file == NULL) {
        printw("Error opening %s", stat_path);
        free(stat_path);
        return;
    } else {
        if (fscanf(file, "%*d (%*[^)]) %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu %*d %*d %*d %*d %*d %*d %*u %lu %ld %*d %*d %*d %*d %*d %*d %*u %*u %*d %lu", &utime, &stime, &vsize, &rss, &starttime) == 5) {
            process->cpu_time = (utime + stime) / (double)sysconf(_SC_CLK_TCK);
            process->v_mem = vsize / 1024;
            process->p_mem = rss * (sysconf(_SC_PAGESIZE) / 1024);
            FILE *uptime_file = fopen("/proc/uptime", "r");
            if (uptime_file != NULL) {
                if (fscanf(uptime_file, "%lu", &uptime) == 1) {
                    process->run_time = uptime - ((double)starttime / sysconf(_SC_CLK_TCK));
                }
            fclose(uptime_file);
            }
        }
        fclose(file);
        free(stat_path);
    }
}

t_active_process *create_process(char *name, char *pid) {
    t_active_process *new = malloc(sizeof(t_active_process));
    new->name = strdup(name);
    new->pid =  strdup(pid);
    new->next = NULL;
    new->prev = NULL;
    get_stat(new, pid);  
    return new;
}

int count_processes(t_active_process *head) {
    t_active_process *tmp = head;
    int count = 0;
    while (tmp != NULL) {
        count += 1;
        tmp = tmp->next;
    }
    return count;
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

void swap(t_active_process *a, t_active_process *b) {
    // If a is the first node in the list, update the prev of b to NULL.
    if (a->prev == NULL) {
        b->prev = NULL;
    }
    // If b is the first node in the list, update the prev of a to NULL.
    else if (b->prev == NULL) {
        a->prev = NULL;
    }

    // Swap a and b. For this, we need to update the next of a's previous, the prev of b's next,
    // the prev and next of a, and the prev and next of b.
    if (a->prev != NULL) {
        a->prev->next = b;
    }
    if (b->next != NULL) {
        b->next->prev = a;
    }
    if (a->next == b) {
        a->next = b->next;
        b->prev = a->prev;
        a->prev = b;
        b->next = a;
    } else {
        t_active_process *a_next = a->next;
        t_active_process *b_prev = b->prev;
        a->next = b->next;
        b->prev = a->prev;
        a->prev = b_prev;
        b->next = a_next;
    }

    // If a was the last node, update the next of b (which is now the second last node) to NULL.
    if (a->next == NULL) {
        b->next = NULL;
    }
    // If b was the last node, update the next of a (which is now the second last node) to NULL.
    if (b->next == NULL) {
        a->next = NULL;
    }
}

void print_processes(t_active_process *head, WINDOW *data_win, int reverse) {
    t_active_process *data = head;
    if (reverse) {
        while (data->next != NULL) {
            data = data->next;
        }
    }
    while (data != NULL) {
        wprintw(data_win, "%-40s %-10s %-20f %-20f %-20f\n", data->name, data->pid, data->cpu_time,/* data->run_time,*/ data->v_mem, data->p_mem);
        data = reverse ? data->prev : data->next;
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