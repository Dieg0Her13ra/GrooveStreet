#include<stdio.h>
#include<stdlib.h>

static void insertionsort(int *lista,int tam){
	for (int i = 1; i < tam; ++i) {
        int tem = lista[i];
        int j = i - 1;
        while (j >= 0 && lista[j] > tem) {
            lista[j + 1] = lista[j];
            j = j - 1;
        }
        lista[j + 1] = tem;
    }
}



void implist(int *lista,int tam){
	printf("\n");
	for(int i=0;i<tam;i++){
		printf("[%d]",lista[i]);
	}
}

int main(){
	int array[12]={2,3,5,-7,6,2,12,23,45,23,90,100};
	implist(array,12);
	insertionsort(array,11);
	implist(array,12);
	
}
