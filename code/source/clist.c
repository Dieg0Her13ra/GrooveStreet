/*
    clist.c
*/
#include <stdlib.h>
#include <string.h>

#include "clist.h"

/*
    Initialize the clist
*/
void clist_init (CList *clist, void (*destroy)(void *data)) {
    clist->size = 0;
    clist->destroy = destroy;
    clist->head = NULL;
    clist->tail = NULL;

    return;    
}

/*
    Destroying the clist
*/
void clist_destroy (CList *list) {
    void *data;

    while(clist_size(list) > 0) {
        if (clist_rem_next(list, clist_tail(list), (void **)&data) == 0 && list->destroy != NULL) {
            list->destroy(data);
        }
    }    
    memset(list, 0, sizeof(CList));
    return;
}

/*
    Insert next node at the clist
*/
int clist_ins_next(CList *list, CListNode *node, const void *data) {
    CListNode *new_node;

    // No se permite un nodo NULL a menos que la lista esté vacía
    if (node == NULL && clist_size(list) != 0)
        return -1;

    // Asignar memoria para el nuevo nodo
    if ((new_node = (CListNode *)malloc(sizeof(CListNode))) == NULL)
        return -1;

    new_node->data = (void *)data;

    // Si la lista está vacía, insertar en la cabeza y hacer circular
    if (clist_size(list) == 0) {
        list->head = new_node;
        new_node->next = new_node; // La lista es circular, apunta a sí mismo
        list->tail = new_node;
    } else {
        // Insertar después del nodo actual
        new_node->next = node->next;
        node->next = new_node;

        // Si el nodo era el último, actualizar la cola
        if (node == list->tail)
        	list->tail = new_node;
    }

    // Incrementar el tamaño de la lista
    list->size++;

    return 0;
}

/*
    Remove node from the list
*/
int clist_rem_next (CList *list, CListNode *node, void **data) {

    CListNode *old_node;

    // Verificar que la lista no esté vacía
    if (clist_size(list) == 0)
        return -1;

    // Si la lista solo tiene un nodo
    if (node->next == node) {
        old_node = node;
        *data = old_node->data;
        list->head = NULL;
        list->tail = NULL;
    } else {
        // Remover el nodo siguiente al dado
        old_node = node->next;
        *data = old_node->data;
        node->next = old_node->next;

        // Si se eliminó la cabeza, actualizarla
        if (old_node == list->head) {
            list->head = old_node->next;
        }

        // Si se eliminó la cola, actualizarla
        if (old_node == list->tail) {
            list->tail = node;
        }
    }

    free(old_node);  // Liberar la memoria del nodo eliminado
    list->size--;

    return 0;
}

