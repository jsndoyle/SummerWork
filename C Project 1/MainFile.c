#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

//Linked List Node Structure
struct _node {
    node* next;
    int data;
};
typedef struct _node node;

//Two Way Linked List Node Structure
struct _nodeAlt {
    nodeAlt* next;
    int data;
    nodeAlt* prev;
};
typedef struct _nodeAlt nodeAlt;

//Note: Consider simply making all node structures include a 'prev' but not declare it except when writing methods for two way linked lists.
//Note: Consider when nodes with 3+ references to other nodes could exist and be functional.


/**
 *  CreateNode() functions
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
 *  Equivalent for Doubly Linked Lists is identical.
 * 
 */

static node* createNode(int datum) {
    node* ret = malloc(sizeof(node));
    ret->data = datum;
    return ret;
}
static nodeAlt* createTwoWayNode(int datum) {
    nodeAlt* ret = malloc(sizeof(nodeAlt));
    ret->data = datum;
    return ret;
}

/**
 *  insertAtPos() functions
 * 
 *  Variables:  node* head points to head of Linked List. Assumed not NULL and to contain data.
 *              node* new points to new node to be inserted in list. Assumed not NULL and to contain data.
 *              int   pos gives position of new node in list.
 * 
 *  Insertion position follows array starts at 0 rules.                                                             <------NEEDS TESTING
 *  Inserting at 0 effectively replaces head with it. (costly feature as implemented. Reconsider with time)
 *  If pos is out of bounds of list, will simply insert at end (costly feature, alt is to crash in this case)
 *  If pos is negative, is equivalent to 0. (zero cost to implement feature as coded)
 *  
 *  Optimized for random insertion in unordered Linked List.
 *  Do not even include this function in code for ordered Linked Lists, because then you might make mistakes, future me.
 *  Using this function rather than manually inserting at 0 costs very little relative to 
 * 
 *  Returns head. Always use new head in case of cases that pos = 0.
 * 
 *  
 *  Doubly Linked List comparison:
 *  Scales better, and fixed cost is similar due to references at start. Needs testing in comparison.
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

static nodeAlt* insertAtPosAlt(nodeAlt* head, nodeAlt* new, int pos) {
    nodeAlt* curr = head;
    while(pos > 0 && curr->next != NULL) {
        pos--;
        curr = curr->next;
    }
    if(curr->prev == NULL) {
        new->next = head;
        head->prev = new;
        return new;
    } else {
        new->prev = curr->prev;
        curr->prev->next = new;
        new->next = curr;
        curr->prev = new;
        return head;
    }
}

/** 
 *  insertAtPosR() functions
 * 
 *  Effectively equivalent to insertAtPos function in every way,
 *  except programmed recursively rather than using a loop.
 * 
 *  NOTE : compare relative efficiencies in all cases between insertAtPos() and insertAtPosR()
 *  Due to lack of variable creation, I expect this will be a little faster in most cases.
 *  But recursion might be costly.
 * 
 *  This implementation appears, at first glance, to be functionally identical, but is much shorter, 
 *  and relies on much more difficult to follow logic (in my opinion, but that is likely lack
 *  of experience with recursion).
 *  Upon further inspection, many more references are modified in this. Effectively,
 *  every reference in the whole list is touched.
 */
static node* insertAtPosR(node* head, node* new, int pos) {
    if(pos == 0 || head->next == NULL) {
        new->next = head;
        return new;
    } else {
        head->next = insertAtPosR(head->next, new, pos - 1);
        return head;
    }
}

static nodeAlt* insertAtPosAltR(nodeAlt* head, nodeAlt* new, int pos) {
    if(pos == 0 || head->next == NULL) {
        new->next = head;
        head->prev = new;
        return new;
    } else {
        nodeAlt* ref = insertAtPosAltR(head->next, new, pos - 1);
        head->next = ref;
        ref->prev = head;//Does this work the way I think it does?
        return head;
    }
}


/**
 *  insertInSequence() function
 * 
 *  Variables:  node* head: head of LinkedList. Assumed to not be NULL and to contain data.
 *              node* new: new Node to be inserted. Assumed to not be NULL and to contain data.
 * 
 *  Assumes Linked List is in sequence, sort in ascending order.
 *  
 */
static int insertInSequence(node* head, node* new) {
    while(head->next != NULL && head->next->data < new->data) {
        head = head->next;
    }
    node* nexter = head->next;
    head->next = new;
    new-> next = nexter;
    return 0;
}

/**
 *  insertInSequenceR() function
 * 
 *  Recursive equivalent to insertInSequence()
 *  
 *  NOTE : compare relative efficiency of both functions.
 */
static int insertInSequenceR(node* head, node* new) {
    //WIP
    if(head->data < new->data) {
        return insertInSequenceR(head->next, new);
    } else {
        new->next = head->next;
        head->next = new;
        return 0;
    }
}


int main(int argc, char* argv[]) {
    return 0;
}