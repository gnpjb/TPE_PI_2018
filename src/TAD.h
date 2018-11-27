#ifndef TPE_PI_TAD_H
#define TPE_PI_TAD_H

#define LONG_OACI 4

enum {V_REG,V_NREG,V_PRIV};
enum {V_CAB,V_INT};

typedef struct AeroListaCDT *AeroListaADT;
AeroListaADT newAeroLista();//crea un aerolista vacia
void addAeropuerto(AeroListaADT aerolista,const char oaci[], const char* denominacion);
char * getDenominacion(AeroListaADT aerolista, char* oaci);//devuelve la denominacion o NULL
void freeAeroLista(AeroListaADT aerolista);//libera una aerolista






typedef struct VueloCDT* VueloADT;
typedef struct FechaDataType{
    int dia;
    int mes;
    int anio;
}FechaT;

VueloADT newVuelo();// crea un vuelo

//setea el oaciobj(oaci de origen si es un despegue u oaci de destino si es un aterrizaje )
void setOaciObjVuelo(VueloADT vuelo, char* oaci);
void setFechaVuelo(VueloADT vuelo,FechaT fecha);//setea la fecha
void setClaseVuelo(VueloADT vuelo,int clase);
void setClasificacionVuelo(VueloADT vuelo,int clasificacion);

void getOaciObjVuelo(VueloADT vuelo);
void getFechaVuelo(VueloADT vuelo);
void getClaseVuelo(VueloADT vuelo);
void getClasificacionVuelo(VueloADT vuelo);

void freeVuelo(VueloADT vuelo);//libera un vuelo

#endif //TPE_PI_TAD_H
