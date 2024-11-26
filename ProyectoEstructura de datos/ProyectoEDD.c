
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"


#define tamax 100

int i;

void AniquilarDato(void *data) {
    free(data);
}



char *strrev(char *str) {
    int longi = strlen(str);
    char *rev = (char *)malloc(sizeof(char) * (longi + 1));
    for (i = 0; i < longi; i++) {
        rev[i] = str[longi - (i+1)];
    }
    rev[longi] = '\0';
    return rev;
}

void esPal(char *str) {
    char *rev = strrev(str);
    if (strcmp(str, rev) == 0)
            printf("\"%s\" simn  es palindromo.\n",str);
    else
        printf("\"%s\" nel no es  palindromo.\n",str);
}

void process_file(FILE *file, List *lista) {
    char pala[tamax];
    int pos = 0;
    char ch;
    int linea = 0;


    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) || ch == ',') {
            if (pos > 0) {
                pala[pos] = '\0';
                printf("Palabra encontrada: %s ", pala);
                char *data = strdup(pala);
                list_ins_next(lista, data, NULL);
                pos = 0;
                esPal(pala);
            }
        } else {
            pala[pos++] = ch;

            if (pos >= tamax - 1) {
                pala[tamax - 1] = '\0';
                printf("Palabra demasiado larga: %s ", pala);
                char *data = strdup(pala);
                list_ins_next(lista, data,NULL);
                pos = 0;
            }
        }
    }
    printf("Total de lineas del archivo: %d\n", linea+1);
}

void BusPalinLista(List *lista) {
    ListNode *nodo = list_head(lista);
    while (nodo != NULL) {
        char *palabra = (char *)list_data(nodo);
        printf("Palabra encontrada: %s\n", palabra);
        esPal(palabra);
        nodo = list_next(nodo);
    }
}


int main() {
    FILE *file = fopen("archivo.txt", "r");
    if (file == NULL) {
        printf("Ps que le hiciste al archivo, nomas ni abre.\n");
        return 1;
    }

    List lista;
    list_init(&lista, AniquilarDato);

    process_file(file, &lista);
    fclose(file);

    BusPalinLista(&lista);

    list_destroy(&lista);


    return 0;
}

