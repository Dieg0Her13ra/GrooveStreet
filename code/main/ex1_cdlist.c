#include <stdio.h>
#include <stdlib.h>

#include "cdlist.h"

/*
   Print CDList
*/
static void print_cdlist(const CDList *cdlist) {
    CDListNode *node;
    float *data;
    int i;

    fprintf(stdout, "\nTamaño de la lista: %d\n", cdlist_size(cdlist));

    i = 0;
    node = cdlist_head(cdlist);

    if (node == NULL) {
        printf("La lista está vacía. Nada que imprimir.\n"); // Depuración
        return;
    }

    // Ciclo para recorrer la lista circular
    do {
        data = (float *)cdlist_data(node);
        fprintf(stdout, "\nlist.node[%03d]=%03.2f, %p -> %p \n", i, *data, node, node->next);

        i++;
        node = cdlist_next(node);  // Avanzar al siguiente nodo

    } while (node != cdlist_head(cdlist));  // Detenerse cuando vuelves a la cabeza
	
	   if (cdlist_tail(cdlist) != NULL) {
        data = (float *)cdlist_data(cdlist_tail(cdlist)->next);  // Obtener los datos del siguiente nodo del tail
        fprintf(stdout, "\nLa cola apunta a la cabeza: list.tail.next=%03.2f, %p -> %p\n", *data, cdlist_tail(cdlist), cdlist_head(cdlist));
    	data = (float *)cdlist_data(cdlist_head(cdlist)->prev);
    	fprintf(stdout, "\nLa cabeza apunta a la cola: list.head.prev=%03.2f, %p -> %p\n", *data, cdlist_head(cdlist), cdlist_tail(cdlist));
	}
    return;
}


int main (int argc, char **argv) {
    CDList cdlist;
    CDListNode *node;
    float *data;
    int i;

    // Initialize the linked list
    cdlist_init(&cdlist, free);

    // Fill the linked list
    node = cdlist_head(&cdlist);

    // Insertar manualmente tres valores flotantes
    float valores[] = {5.7f, 12.3f, 8.9f,78.56f};  // Tres valores de ejemplo

    for (int i = 0; i < 4; i++) {
        data = (float *)malloc(sizeof(float));
        if (data == NULL) {
            printf("Error: fallo al asignar memoria para el dato\n");
            return 1;
        }

        *data = valores[i];  // Asignar el valor flotante

        // Insertar el nodo en la lista
        if (cdlist_ins_next(&cdlist, cdlist_tail(&cdlist), data) != 0) {
            printf("Error: fallo al insertar el nodo\n");
            return 1;
        }

        node = cdlist_tail(&cdlist);  // Actualizar el nodo
    }
    // Imprimir la lista
    print_cdlist(&cdlist);
    node = cdlist_next(node);
    //Insertaremos un nodo de valor 19.93
    data = (float *)malloc(sizeof(float));
    *data = 19.93f;
    fprintf(stdout, "\nInsertaremos un nodo enseguida del primer nodo");
    if(cdlist_ins_next(&cdlist,node,data)!=0){
    	return -1;	
	}
	print_cdlist(&cdlist);
	//Insertaremos un nodo de valor 20.05
    data = (float *)malloc(sizeof(float));
    *data = 20.05f;
    fprintf(stdout, "\nInsertaremos un nodo antes del primer nodo");
    if(cdlist_ins_prev(&cdlist,node,data)!=0){
    	return -1;	
	}
	print_cdlist(&cdlist);
    //Insertaremos un nodo de valor 20.05
	node = cdlist_next(node);
	data = (float *)malloc(sizeof(float));
    *data = 19.93f;
    node = cdlist_next(node);
    node = cdlist_next(node);
    fprintf(stdout, "\nEliminaremos el nodo con el dato 8.9");
    if(cdlist_remove(&cdlist,node,(void**)&data)!=0){
    	return -1;	
	}
	print_cdlist(&cdlist);
	// Destruir la lista
    fprintf(stdout, "\nDestroying the list\n");
    cdlist_destroy(&cdlist);
    
    return 0;
}
