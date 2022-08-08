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
 * Priority implemenetation that uses a linked list of task structs.
 */
struct node *head = NULL;  //head of linked list

//method that compares two strings
bool comesBefore(char *a, char *b) {
    return strcmp(a, b) < 0;
}
/*
 * Method call that executes processes in a linked list in priority order. Goes through the linked list
 * of processes for the one with the highest priority, which is run and removed from the linked list.
 * Tasks with the same priority are compared lexicographically to determine which is run first.
 */
void schedule() {
    struct node *current_node = head;  //for searching
    struct node *priority_node = head;  //for highest priority task

    while (head != NULL) { //search through list

        current_node = head;
        priority_node = head;

        while (current_node != NULL) {
            if (current_node->task->priority > priority_node->task->priority) {
                priority_node = current_node;
            } else if (current_node->task->priority == priority_node->task->priority) {
                if (comesBefore(current_node->task->name, priority_node->task->name)) {
                    priority_node = current_node;
                }
            }
            current_node = current_node->next;
        }

        run(priority_node->task, priority_node->task->burst); //runs the highest priority task
        delete(&head, priority_node->task);
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
    while (currentNode->next != NULL) {  //search through list until next equals NULL
        currentNode = currentNode->next;
    }

    insert(&currentNode->next, new_task);

    return;
}