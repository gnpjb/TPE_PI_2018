#include "TAD.h"
#include <string.h>
#include <stdlib.h>


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



//------------------------------------------------------------------
//AEROPUERTO
struct AeropuertoCDT{
    char oaci[LONG_OACI];
    char* denominacion;
};
AeropuertoADT newAeropuerto(){
    AeropuertoADT ret=calloc(1,sizeof(struct AeropuertoCDT));
    return ret;
}
void setOaciAeropuerto(AeropuertoADT aeropuerto, const char *oaci){
    oaciCopy(aeropuerto->oaci,oaci);
}
void setDenominacionAeropuerto(AeropuertoADT aeropuerto, char *denominacion) {
    free(aeropuerto->denominacion);
    aeropuerto->denominacion=cloneDenominacion(denominacion);
}
char *getOaciAeropuerto(AeropuertoADT aeropuerto) {
    return aeropuerto->oaci;
}
char *getDenominacionAeropuerto(AeropuertoADT aeropuerto) {
    return aeropuerto->denominacion;
}
void freeAeropuerto(AeropuertoADT aeropuerto) {
    free(aeropuerto->denominacion);
    free(aeropuerto);
}




//------------------------------------------------------------------
//AEROLISTA

typedef struct NodeCDT* NodeADT;

struct NodeCDT {
    AeropuertoADT aeropuerto;
    NodeADT next;
};

struct AeroListaCDT{
    NodeADT first;
    NodeADT it;
    int size;
};

AeroListaADT newAeroLista(){
    AeroListaADT list=malloc(sizeof(struct AeroListaCDT));
    list->first=NULL;
    return list;
}

void addAeropuerto(AeroListaADT aerolista,AeropuertoADT aeropuerto){
    NodeADT aux=NULL;
    if(aerolista->first==NULL||oaciCompare(aerolista->first->aeropuerto->oaci,aeropuerto->oaci)==1){
        aux=aerolista->first;
        aerolista->first=malloc(sizeof(struct NodeCDT));
        aerolista->first->next=aux;
        aerolista->first->aeropuerto=aeropuerto;
        aerolista->size++;
    }
    else if(oaciCompare(aerolista->first->aeropuerto->oaci,aeropuerto->oaci)==0){
        freeAeropuerto(aeropuerto);
        return;
    }
    else{
        aux=aerolista->first;
        int c=-1;
        while(aux->next!=NULL &&  (c=oaciCompare(aux->aeropuerto->oaci,aeropuerto->oaci))<0) {
            aux = aux->next;
        }
        if(c!=0){
            NodeADT aux2=aux->next;
            aux->next=malloc(sizeof(struct NodeCDT));
            aux->next->aeropuerto=aeropuerto;
            aux->next->next=aux2;
            aerolista->size++;
        }else{
            freeAeropuerto(aeropuerto);
        }
    }
}

char *getDenominacionAerolista(AeroListaADT aerolista, const char* oaci){
    NodeADT aux=aerolista->first;
    int c=0;
    while(aux!=NULL && c!=1){
        c=oaciCompare(aux->aeropuerto->oaci,oaci);
        if(c==0){
            return aux->aeropuerto->denominacion;
        }
        aux=aux->next;
    }
    return NULL;
}

void initIteratorAerolista(AeroListaADT aeroLista){
    aeroLista->it=aeroLista->first;
}

AeropuertoADT getNextAerolista(AeroListaADT aeroLista){
    AeropuertoADT ret=aeroLista->it->aeropuerto;
    aeroLista->it=aeroLista->it->next;
    return ret;
}

int hasNextAerolista(AeroListaADT aeroLista){
    return aeroLista->it!=NULL;
}

int getSizeAerolista(AeroListaADT aerolista){
    return aerolista->size;
}


void freeAeroLista(AeroListaADT aerolista){
    NodeADT aux=aerolista->first;
    NodeADT aux2;
    while(aux!=NULL){
        aux2=aux->next;
        freeAeropuerto(aux->aeropuerto);
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

