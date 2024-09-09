#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){
    int i, j;
    char *num = argv[1];

    for(j=0; j <= argc; j++){
        fprintf(stdout,"arg[%d] = %s \n", j, argv[j]);
    }
    for (i = 0; i < strlen(argv[1]); i++){
        fprintf(stdout,"num[%d] = %c \n", i, num[i]);
    }
        return 0;

}

