#include <stdio.h>
#include <stdlib.h>

#include "clist.h"

/*
   Print CList
*/
static void print_clist(const CList *clist) {
    CListNode *node;
    float *data;
    int i;

    fprintf(stdout, "\nEl tamaño de la lista es %d\n", clist_size(clist));

    i = 0;
    node = clist_head(clist);

    if (node == NULL) {
        printf("La lista está vacía. Nada que imprimir.\n"); // Depuración
        return;
    }

    // Ciclo para recorrer la lista circular
    do {
        data = (float *)clist_data(node);
        fprintf(stdout, "list.node[%03d]=%03.2f, %p -> %p \n", i, *data, node, node->next);

        i++;
        node = clist_next(node);  // Avanzar al siguiente nodo

    } while (node != clist_head(clist));  // Detenerse cuando vuelves a la cabeza
	
	   if (clist_tail(clist) != NULL) {
        data = (float *)clist_data(clist_tail(clist)->next);  // Obtener los datos del siguiente nodo del tail
        fprintf(stdout, "La cola apunta a la cabeza: list.tail.next=%03.2f, %p -> %p\n", *data, clist_tail(clist), clist_head(clist));
    }
    return;
}


int main (float argc, char **argv) {
    CList clist;
    CListNode *node;
    float *data;
    int i;

    // Inicializa la lista
    clist_init(&clist, free);

    // Llena la lista con un nodo
    node = clist_head(&clist);

    // Insertar manualmente tres valores flotantes
    float valores[] = {5.7f, 12.3f, 8.9f};  // Tres valores de ejemplo

    for (int i = 0; i < 3; i++) {
        data = (float *)malloc(sizeof(float));
        if (data == NULL) {
            printf("Error: fallo al asignar memoria para el dato\n");
            return 1;
        }

        *data = valores[i];  // Asignar el valor flotante

        // Insertar el nodo en la lista
        if (clist_ins_next(&clist, clist_tail(&clist), data) != 0) {
            printf("Error: fallo al insertar el nodo\n");
            return 1;
        }

        node = clist_tail(&clist);  // Actualizar el nodo
    }
    // Imprimir la lista
    data = (float *)malloc(sizeof(float));
        if (data == NULL) {
            printf("Error: fallo al asignar memoria para el dato\n");
            return 1;
        }
    print_clist(&clist);
	*data =13.30f;
    for(int i=0;i<4;i++){
    	node = clist_next(node);	
	}
    if (clist_ins_next(&clist, clist_tail(&clist), data) != 0) {
            printf("Error: fallo al insertar el nodo\n");
            return 1;
        }
    fprintf(stdout,"\nInsertando un nuevo dato 13.30");
	print_clist(&clist);
	for(int i=0;i<3;i++){
    	node = clist_next(node);	
	}

    clist_rem_next(&clist,node,(void**)&data);
    print_clist(&clist);
    // Destruir la lista
    fprintf(stdout, "\nDestroying the list\n");
    clist_destroy(&clist);

    return 0;
}

