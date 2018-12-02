#include "FirstQuery.h"
#include <stdlib.h>

typedef struct Node{
    AeropuertoADT aeropuerto;
    long movs;
}Node;

struct FirstQueryCDT{
    Node *arr;
    int size;
};

FirstQuery newFirstQuery(AeroListaADT aerolistaAsociada){
    FirstQuery query=malloc(sizeof(*query));
    query->size=getSizeAerolista(aerolistaAsociada);
    query->arr=malloc(sizeof(Node)*query->size);
    int i=0;
    initIteratorAerolista(aerolistaAsociada);
    while(hasNextAerolista(aerolistaAsociada)){
        query->arr[i].aeropuerto=getNextAerolista(aerolistaAsociada);
        query->arr[i++].movs=0;
    }
    return query;
}

void queryFirstQuery(FirstQuery query,VueloADT vuelo){
    char *oaci=getOaciObjVuelo(vuelo);
    int found=0,c=0;
    for(int i=0; i<query->size&&!found;i++){
        if((c=oaciCompare(getOaciAeropuerto(query->arr[i].aeropuerto),oaci))==0){
            query->arr[i].movs++;
            found=1;
        }
        else if(c==1){
            found=1;
        }
    }
}

//FUNCION AUXILIAR
void swapNode(Node* node1,Node* node2){
    Node temp=*node1;
    *node1=*node2;
    *node2=temp;
}
//FUNCION AUXILIAR

void closeFirstQuery(FirstQuery query){
    int found,pos;
    for(int i=1; i<query->size; i++){
        found=0,pos=i;
        for(int j=i-1; j>=0&&!found;j--){
            if(query->arr[pos].movs>query->arr[j].movs){
                swapNode(query->arr+pos,query->arr+j);
                pos=j;
            }else{
                found=1;
            }
        }
    }
}

void printFirstQuery(FirstQuery query,FILE* file){
    fprintf(file,"OACI;Denominacion;Movimientos\n");
    for(int i=0;i<query->size;i++){
        fprintf(file,"%.4s;%s;%ld\n",
                getOaciAeropuerto(query->arr[i].aeropuerto),getDenominacionAeropuerto(query->arr[i].aeropuerto),
                query->arr[i].movs);
    }
}
void freeFirstQuery(FirstQuery query){
    free(query->arr);
    free(query);
}
