#include "htop.h"

void sort_name(t_active_process *head) {
    t_active_process *tmp = head;
    while (tmp != NULL) {
        t_active_process *min = tmp;
        t_active_process *tmp2 = tmp->next;
        while (tmp2 != NULL) {
            if (strcmp(tmp2->name, min->name) < 0) {
                min = tmp2;
            }
            tmp2 = tmp2->next;
        }
        if (min != tmp) {
            swap(tmp, min);
        }
        tmp = tmp->next;
    }
}

void sort_pid(t_active_process *head) {
    t_active_process *tmp = head;
    while (tmp != NULL) {
        t_active_process *min = tmp;
        t_active_process *tmp2 = tmp->next;
        while (tmp2 != NULL) {
            if (atoi(tmp2->pid) < atoi(min->pid)) {
                min = tmp2;
            }
            tmp2 = tmp2->next;
        }
        if (min != tmp) {
            swap(tmp, min);
        }
        tmp = tmp->next;
    }
}

void sort_cpu_time(t_active_process *head) {
    t_active_process *tmp = head;
    while (tmp != NULL) {
        t_active_process *min = tmp;
        t_active_process *tmp2 = tmp->next;
        while (tmp2 != NULL) {
            if (tmp2->cpu_time < min->cpu_time) {
                min = tmp2;
            }
            tmp2 = tmp2->next;
        }
        if (min != tmp) {
            swap(tmp, min);
        }
        tmp = tmp->next;
    }
}

void sort_v_mem(t_active_process *head) {
    t_active_process *tmp = head;
    while (tmp != NULL) {
        t_active_process *min = tmp;
        t_active_process *tmp2 = tmp->next;
        while (tmp2 != NULL) {
            if (tmp2->v_mem < min->v_mem) {
                min = tmp2;
            }
            tmp2 = tmp2->next;
        }
        if (min != tmp) {
            swap(tmp, min);
        }
        tmp = tmp->next;
    }
}

void sort_p_mem(t_active_process *head) {
    t_active_process *tmp = head;
    while (tmp != NULL) {
        t_active_process *min = tmp;
        t_active_process *tmp2 = tmp->next;
        while (tmp2 != NULL) {
            if (tmp2->p_mem < min->p_mem) {
                min = tmp2;
            }
            tmp2 = tmp2->next;
        }
        if (min != tmp) {
            swap(tmp, min);
        }
        tmp = tmp->next;
    }
}

void sort_run_time(t_active_process *head) {
    t_active_process *tmp = head;
    while (tmp != NULL) {
        t_active_process *min = tmp;
        t_active_process *tmp2 = tmp->next;
        while (tmp2 != NULL) {
            if (tmp2->run_time < min->run_time) {
                min = tmp2;
            }
            tmp2 = tmp2->next;
        }
        if (min != tmp) {
            swap(tmp, min);
        }
        tmp = tmp->next;
    }
}


void sort_menu(t_active_process *head, char *sort_type) {
    if (strcmp(sort_type, "name") == 0) {
        sort_name(head);
    } else if (strcmp(sort_type, "pid") == 0) {
        sort_pid(head);
    } else if (strcmp(sort_type, "cpu_time") == 0) {
        sort_cpu_time(head);
    } else if (strcmp(sort_type, "v_mem") == 0) {
        sort_v_mem(head);
    } else if (strcmp(sort_type, "p_mem") == 0) {
        sort_p_mem(head);
    } else if (strcmp(sort_type, "run_time") == 0) {
        sort_run_time(head);
    }
}