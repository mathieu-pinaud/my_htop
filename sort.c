#include "htop.h"

t_active_process *sort_name(t_active_process *head) {
    t_active_process *tmp = head;
    t_active_process *new_head = head;
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
            if (tmp == head) {
                new_head = min;
            }
        }
        tmp = tmp->next;
    }
    return new_head;
}

t_active_process *sort_pid(t_active_process *head) {
    t_active_process *tmp = head;
    t_active_process *new_head = head;
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
            if (tmp == head) {
                new_head = min;
            }
        }
        tmp = tmp->next;
    }
    return new_head;
}

t_active_process *sort_cpu_time(t_active_process *head) {
    t_active_process *tmp = head;
    t_active_process *new_head = head;
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
            if (tmp == head) {
                new_head = min;
            }
        }
        tmp = tmp->next;
    }
    return new_head;
}

t_active_process *sort_v_mem(t_active_process *head) {
    t_active_process *tmp = head;
    t_active_process *new_head = head;
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
            if (tmp == head) {
                new_head = min;
            }
        }
        tmp = tmp->next;
    }
    return new_head;
}

t_active_process *sort_p_mem(t_active_process *head) {
    t_active_process *tmp = head;
    t_active_process *new_head = head;
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
            if (tmp == head) {
                new_head = min;
            }
        }
        tmp = tmp->next;
    }
    return new_head;
}


t_active_process *sort_menu(t_active_process *head, char *sort_type) {
    if (strcmp(sort_type, "name") == 0) {
        return(sort_name(head));
    } else if (strcmp(sort_type, "pid") == 0) {
        return(sort_pid(head));
    } else if (strcmp(sort_type, "cpu_time") == 0) {
        return(sort_cpu_time(head));
    } else if (strcmp(sort_type, "v_mem") == 0) {
        return(sort_v_mem(head));
    } else if (strcmp(sort_type, "p_mem") == 0) {
        return(sort_p_mem(head));
    }
    return head;
}