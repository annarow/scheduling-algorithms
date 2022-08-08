#include "schedulers.h"
#include "list.h"
#include "cpu.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
/*
 * Project 3 Scheduling Algorithms
 * 2/16/2022
 * By Anna Rowena Waldron
 *
 * Shortest job first implemenetation that uses a linked list of task structs.
 */
struct node *head = NULL;  //head of linked list

//method that compares two strings
bool comesBefore(char *a, char *b) {
    return strcmp(a, b) < 0;
}
/*
 * Method call that executes processes in shortest job first order by searching through the list of tasks for the task
 * with the shortest burst time. The tasks will then be compared lexicographically for ties and then run.
 */
void schedule() {
    struct node *current_node = head; //for searching
    struct node *fastest_node = head;  //task to be executed

    while (head != NULL) { //search through linked list of nodes
        current_node = head;
        fastest_node = head;
        while (current_node != NULL) {
            if (current_node->task->burst < fastest_node->task->burst) { //look for shortest burst time
                fastest_node = current_node;
            } else if (current_node->task->burst == fastest_node->task->burst) { //if equal burst times, run in
                if (comesBefore(current_node->task->name, fastest_node->task->name)) { //lexicographical order
                    fastest_node = current_node;
                }
            }
            current_node = current_node->next;
        }
        run(fastest_node->task, fastest_node->task->burst);
        delete(&head, fastest_node->task);
    }
}
/*
 * Method that takes in a pointer task name, and two integers task priority and task burst, that adds nodes to a
 * linked list. Finds a NULL location and inserts node.
 */
void add(char *task_name, int task_priority, int task_burst) {
    Task *new_task = malloc(sizeof(Task));

    new_task->name = task_name;
    new_task->priority = task_priority;
    new_task->burst = task_burst;

    if (head == NULL) { //insert into empty list
        insert(&head, new_task);
        return;
    }

    struct node *current_node = head;

    while (current_node->next != NULL) { //search through list until next equals NULL
        current_node = current_node->next;
    }

    insert(&current_node->next, new_task); //insert task node at current location
    return;
}