#include "TAD.h"
#include <string.h>
#include <stdlib.h>

//------------------------------------------------------------------
//AEROLISTA

typedef struct NodeCDT* NodeADT;

struct NodeCDT {
    char oaci[LONG_OACI] ;
    char* denominacion;
    NodeADT next;
};

struct AeroListaCDT{
    NodeADT first;
};

AeroListaADT newAeroLista(){
    AeroListaADT list=malloc(sizeof(struct AeroListaCDT));
    list->first=NULL;
    return list;
}
//FUNCION AUXILIAR
//devuelve -1 si oaci1<oaci2
//0 si oaci1==oaci2
//1 si oaci1>oaci2
int oaciCompare(const char oaci1[],const char oaci2[]){
    for(int i=0; i<LONG_OACI; i++){
        if(oaci1[i]!=oaci2[i]){
             if(oaci1[i]<oaci2[i]){
                 return -1;
             }
             return 1;
        }
    }
    return 0;
}

//copia el oaci
void oaciCopy(char oaciDest[],const char oaciSrc[]){
    for(int i=0; i<LONG_OACI; i++){
        oaciDest[i]=oaciSrc[i];
    }
}

//devuelve una copia de la denominacion
char *cloneDenominacion(const char* denominacion){
    char* clone = malloc(strlen(denominacion)+1);
    strcpy(clone,denominacion);
    return clone;
}

//FUNCION AUXILIAR

void addAeropuerto(AeroListaADT aerolista,const char oaci[], const char* denominacion){
    NodeADT aux=NULL;
    if(aerolista->first==NULL||oaciCompare(aerolista->first->oaci,oaci)==1){
        aux=aerolista->first;
        aerolista->first=malloc(sizeof(struct NodeCDT));
        aerolista->first->next=aux;
        oaciCopy(aerolista->first->oaci,oaci);
        aerolista->first->denominacion=cloneDenominacion(denominacion);
    }
    else if(oaciCompare(aerolista->first->oaci,oaci)==0){
        return;
    }
    else{
        aux=aerolista->first;
        int c;
        if(aux->next!=NULL){
            c=oaciCompare(aux->next->oaci,oaci);
        }
        while(aux->next!=NULL &&  c<0) {
            aux = aux->next;
        }
        if(c!=0){
            NodeADT aux2=aux->next;
            aux->next=malloc(sizeof(struct NodeCDT));
            oaciCopy(aux->next->oaci,oaci);
            aux->next->denominacion=cloneDenominacion(denominacion);
            aux->next->next=aux2;
        }
    }
}

char * getDenominacion(AeroListaADT aerolista, const char* oaci){
    NodeADT aux=aerolista->first;
    int c=0;
    while(aux!=NULL && c!=1){
        c=oaciCompare(aux->oaci,oaci);
        if(c==0){
            return aux->denominacion;
        }
    }
    return NULL;
}
void freeAeroLista(AeroListaADT aerolista){
    NodeADT aux=aerolista->first;
    NodeADT aux2;
    while(aux!=NULL){
        aux2=aux->next;
        free(aux->denominacion);
        free(aux);
        aux=aux2;
    }
    free(aerolista);
}

//------------------------------------------------------------------
//VUELOS
struct VueloCDT{
    char oaciObj[LONG_OACI];
    FechaT fecha;
    int clase;
    int clasificacion;
};
VueloADT newVuelo(){
    return malloc(sizeof(struct VueloCDT));
}

//setea el oaciobj(oaci de origen si es un despegue u oaci de destino si es un aterrizaje )
void setOaciObjVuelo(VueloADT vuelo,const char* oaci){
    oaciCopy(vuelo->oaciObj,oaci);
}
void setFechaVuelo(VueloADT vuelo,FechaT fecha){
    vuelo->fecha.dia=fecha.dia;
    vuelo->fecha.mes=fecha.mes;
    vuelo->fecha.anio=fecha.anio;
}
void setClaseVuelo(VueloADT vuelo,enum Clase clase){
    vuelo->clase=clase;
}
void setClasificacionVuelo(VueloADT vuelo, enum Clasificacion clasificacion){
    vuelo->clasificacion=clasificacion;
}

char* getOaciObjVuelo(VueloADT vuelo){
    return vuelo->oaciObj;
}
FechaT getFechaVuelo(VueloADT vuelo){
    return vuelo->fecha;
}
int getClaseVuelo(VueloADT vuelo){
    return vuelo->clase;
}
int getClasificacionVuelo(VueloADT vuelo){
    return vuelo->clasificacion;
}

void freeVuelo(VueloADT vuelo){
    free(vuelo);
}

