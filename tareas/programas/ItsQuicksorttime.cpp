#include<stdio.h>
#include<stdlib.h>

static void itsQuicksorttime(int *lista,int iMi,int iMa){
	int i=iMi;
	int j=iMa;
	int mid=lista[iMi+(iMa-iMi)/2];
	
	while(i<=j){
		while(lista[i]<mid){
			i++;
		}
		while(lista[j]>mid){
			j--;	
		}
		if(i<=j){
			int aux = lista[i];
			lista[i]=lista[j];
			lista[j]=aux;
			i++;
			j--;
		}
	}
	
	if(iMi<j){
		itsQuicksorttime(lista,iMi,j);
	}
	if(i<iMa){
		itsQuicksorttime(lista,i,iMa);
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
	itsQuicksorttime(array,0,11);
	implist(array,12);
	
	
}





