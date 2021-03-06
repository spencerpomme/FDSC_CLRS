/* 4-17 invert linked list */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node *Linked;
struct Node {
    int val;
    Linked next;
};

Linked invert(linked list)
{
    Linked prev, curr;
    curr = NULL;
    while (list)
    {
        prev = curr;
        curr = list;
        list = list->next;
        curr->next = prev;
    }
    return curr;
}