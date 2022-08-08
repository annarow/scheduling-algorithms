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
 * First come first serve implemenetation that uses a linked list of task structs.
 */
struct node *head = NULL; //head of linked list

bool comesBefore(char *a, char *b) {
    return strcmp(a, b) < 0;
}
/*
 * Method call that executes a linked list of tasks in first come first serve order.Method that is called to execute a
 * linked list of processes by searching through the list for the first node in lexicographical order for each instruction.
 * Uses while loops to search through the list to run tasks and delete them.
 */
void schedule() {
    struct node *current_node = head; //pointers for searching

    struct node *last_node = head;  //pointers for searching

    while (head != NULL) {  //search through list

        current_node = head;
        last_node = head;

        while (current_node != NULL) { //check for lexicographical order
            if (comesBefore(current_node->task->name, last_node->task->name)) {
                last_node = current_node;
            }
            current_node = current_node->next;
        }

        run(last_node->task, last_node->task->burst); //run the task
        delete(&head, last_node->task);    //delete
    }
}
/*
 * Method that adds a node to the linked list where the current node's next is NULL. Takes in a pointer to
 * task name, and two integers task priority and task burst.
 */
void add(char *task_name, int task_priority, int task_burst) {
    Task *new_task = malloc(sizeof(Task));

    new_task->name = task_name;
    new_task->priority = task_priority;
    new_task->burst = task_burst;

    if (head == NULL) { //if its the start of the list or empty list, insert node
        insert(&head, new_task);
        return;
    }

    struct node *current_node = head;

    while (current_node->next != NULL) { //if not null keep searching
        current_node = current_node->next;
    }

    insert(&current_node->next, new_task); //puts a new task
    return;

}