/*
    cdlist.c
*/
#include <stdlib.h>
#include <string.h>

#include "cdlist.h"

/*
    Initialize the cdlist
*/
void cdlist_init (CDList *list, void (*destroy)(void *data)) {
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;    
}

/*
    Destroying the cdlist
*/
void cdlist_destroy (CDList *list) {
    void *data;

    while(cdlist_size(list) > 0) {
        if (cdlist_remove(list, cdlist_tail(list), (void **)&data) == 0 && list->destroy != NULL) {
            list->destroy(data);
        }
    }    
    memset(list, 0, sizeof(CDList));
    return;
}

/*
    Insert next node at the cdlist
*/
int cdlist_ins_next (CDList *list, CDListNode *node, const void *data ) {
    CDListNode    *new_node;

    // Do not allow a NULL node unless the list is empty
    if (node == NULL && cdlist_size(list) != 0)
        return -1;

    if ((new_node = (CDListNode *)malloc(sizeof(CDListNode))) == NULL)
        return -1;

    new_node->data = (void *)data;

    // The list is empty, insert at the head
    if (cdlist_size(list) == 0){
        list->head = new_node;
        list->head->prev = new_node;
        list->head->next = new_node;
        list->tail = new_node;
        
    } else {
        new_node->next = node->next;
        new_node->prev = node;
		node->next->prev= new_node;
		node->next=new_node;
		
        if (node == list->tail) {
            list->tail = new_node;
	    }
	}
    list->size++;

    return 0;

}

/*
    Insert next node at the List
*/
int cdlist_ins_prev (CDList *list, CDListNode *node, const void *data ) {
    CDListNode    *new_node;

    // Do not allow a NULL node unless the list is empty
    if (node == NULL && cdlist_size(list) != 0)
        return -1;

    if ((new_node = (CDListNode *)malloc(sizeof(CDListNode))) == NULL)
        return -1;

    new_node->data = (void *)data;

    // The list is empty, insert at the head
    if (cdlist_size(list) == 0){
        list->head = new_node;
        list->head->prev = new_node;
        list->head->next = new_node;
        list->tail = new_node;
        
    } else {
        new_node->next = node;
        new_node->prev = node->prev;
		node->prev->next=new_node;
		node->prev=new_node;
        if (node == list->head) {
            list->head = new_node;
        }
    }

    list->size++;

    return 0;
}

/*
    Remove node at the List
*/
int cdlist_remove (CDList *list, CDListNode *old_node, void **data) {

    // Check if is not empty the list or head-tail node
    if (old_node == NULL && cdlist_size(list) == 0)
        return -1;
    
    *data = old_node->data;

	if(list->size==1){
		list->head=NULL;
		list->tail=NULL;
	}else{
		if (old_node == list->head) {
        	list->head = old_node->next;
        	list->tail->next = list->head; 
        	list->head->prev = list->tail;
		}
   		if (old_node == list->tail){
            list->tail = old_node->prev;
            list->tail->next = list->head;
            list->head->prev = list->tail;
        }else {
        	old_node->prev->next = old_node->next;
        	old_node->next->prev = old_node->prev;
		}  
	}

       
/*
        if (old_node->next == NULL)
            list->tail = node->prev;
        else
            old_node->next->prev = node->prev;
*/
    free(old_node);
    list->size--;

    return 0;
}


