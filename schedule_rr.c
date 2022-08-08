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
 * Round robin implemenetation that uses a linked list of task structs.
 */
struct node *head = NULL; //head of linked list

//method that compares two strings
bool comesBefore(char *a, char *b) {
    return strcmp(a, b) < 0;
}
/*
 * Method call that executes processes in a linked list in round robin order. Goes through the linked list
 * of processes and runs each for 1 time quantum until the process runs out of burst time and is deleted from
 * the linked list until the list is empty.
 */
void schedule() {
    struct node *current_node = head;

    while (head != NULL) { //going through the list
        //runs the nodes before the end with leftover burst time equaling greater than time quantum
        while ((current_node->task->burst > QUANTUM) && (current_node->next != NULL)) {

            run(current_node->task, QUANTUM);
            current_node->task->burst = current_node->task->burst - QUANTUM;
            current_node = current_node->next;
        }
        //runs the nodes at the end of the linked list with leftover burst time equaling greater than time quantum
        if ((current_node->task->burst > QUANTUM) && current_node->next == NULL) {

            run(current_node->task, QUANTUM);
            current_node->task->burst = current_node->task->burst - QUANTUM;
            current_node = head;
        }
        //runs the nodes at the end with less burst time left than the quantum time
        else if ((current_node->task->burst <= QUANTUM) && (current_node->next == NULL)) {

            run(current_node->task, current_node->task->burst);
            delete(&head, current_node->task);
            current_node = head;
        }
        //runs the nodes before the end of the list with less burst time left than the time quantum
        else if (current_node->task->burst <= QUANTUM) {

            run(current_node->task, current_node->task->burst);
            delete(&head, current_node->task);
            current_node = current_node->next;
        }
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

    struct node *currentNode = head;
    while (currentNode->next != NULL) { //search through list until next equals NULL
        currentNode = currentNode->next;
    }

    insert(&currentNode->next, new_task);

    return;
}