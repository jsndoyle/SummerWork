#include <stdio.h>
#include <stdlib.h>

//Linked List Node Structure
struct _node {
    node* next;
    int data;
};
typedef struct _node node;


/**
 *  CreateNode() function
 * 
 *  Variable: int datum. Data to store in the created node.
 *  
 *  Effective merge of create and append-helper functions for linked list.
 *  Allocates data for new node and stores data in it.
 *  Does not modify nextNode, simply returns pointer to new node.
 * 
 *  Due to how this is allocated, many free()s required at end of session to deallocate.
 *  This function is optimized for code when each node is created independently of each other
 *  If all nodes were created at once or in a predictable and known pattern, this function would
 *  not be the optimal choice.
 * 
 */
static node* createNode(int datum) {
    node* ret = malloc(sizeof(node));
    ret->data = datum;
}
/**
 *  insertAtPos() function
 * 
 *  Variables:  node* head points to head of Linked List.
 *              node* new points to new node to be inserted in list.
 *              int   pos gives position of new node in list.
 * 
 *  Insertion position follows array starts at 0 rules.
 *  Inserting at 0 effectively replaces head with it. (costly feature as implemented. Reconsider with time)
 *  If pos is out of bounds of list, will simply insert at end (costly feature, alt is to crash in this case)
 *  
 *  Optimized for random insertion in unordered Linked List.
 *  Do not even include this function in code for ordered Linked Lists, because then you might make mistakes, future me.
 *  Using this function rather than manually inserting at 0 costs very little relative to 
 * 
 *  Returns head. Always use new head in case of cases that pos = 0.
 */
static node* insertAtPos(node* head, node* new, int pos) {
    node* prev = NULL;
    node* curr = head;
    while(pos > 0 && curr->next != NULL) {
        prev = curr;
        curr = curr->next;
        pos--;
    }
    if(prev == NULL) {
        new->next = curr;
        return new;
    } else {
        new->next = curr;
        prev->next = new;
        return head;
    }
}

static int insertInSequence(node* head, node* new) {
    while(head->next != NULL && head->data < new->data) {
        head = head->next;
    }
    node* nexter = head->next;
    head->next = new;
    new-> next = nexter;
    return head->data;
}

int main(int argc, char* argv[]) {
    return 0;
}