#include "FirstQuery.h"
#include <stdlib.h>


typedef struct NodeCDT* Node;
struct NodeCDT{
    char oaci[LONG_OACI];
    char* denominacion;
    long movs;
    Node next;
};

struct FirstQueryCDT{
    Node first;
    AeroListaADT aeroLista;
};

FirstQuery newFirstQuery(AeroListaADT aerolistaAsociada){
    FirstQuery query = malloc(sizeof(struct FirstQueryCDT));
    query->first=NULL;
    query->aeroLista=aerolistaAsociada;
    return query;
}

void queryFirstQuery(FirstQuery query,VueloADT vuelo){
    char *oaci=getOaciObjVuelo(vuelo);
    char *denominacion=getDenominacionAerolista(query->aeroLista,oaci);
    if(denominacion!=NULL){
        int c;
        if(query->first==NULL||(c=oaciCompare(oaci,query->first->oaci))>0){
            Node aux=query->first;
            query->first=malloc(sizeof(struct NodeCDT));
            oaciCopy(query->first->oaci,oaci);
            query->first->denominacion=denominacion;
            query->first->next=aux;
            query->first->movs=1;
        }
        else if(c==0){
            query->first->movs+=1;
        }
        else{
            Node aux=query->first;
            while(aux->next!=NULL||c<0){
                aux=aux->next;
                c=oaciCompare(oaci,aux->next->oaci);
            }
            if(c==0){
                aux->next->movs+=1;
            }
            else{
                Node aux2=aux->next;
                aux->next=malloc(sizeof(struct NodeCDT));
                aux->next->next=aux2;
                oaciCopy(aux->next->oaci,oaci);
                aux->next->denominacion=denominacion;
                aux->next->movs=1;
            }
        }
    }
}
void printFirstQuery(FirstQuery query,FILE* file){
    //TODO
}
void freeFirstQuery(FirstQuery query){
    if(query->first!=NULL){
        Node aux=query->first;
        Node aux2;
        while(aux!=NULL){
            aux2=aux->next;
            free(aux);
            aux=aux2;
        }
    }
    free(query);
}
