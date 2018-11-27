#ifndef TPE_PI_TAD_H
#define TPE_PI_TAD_H

#define LONG_OACI 4

enum Clase {V_REG,V_NREG,V_PRIV};
enum Clasificacion {V_CAB,V_INT};

typedef struct AeroListaCDT *AeroListaADT;
AeroListaADT newAeroLista();//crea un aerolista vacia
void addAeropuerto(AeroListaADT aerolista,const char oaci[], const char* denominacion);
char * getDenominacion(AeroListaADT aerolista,const char* oaci);//devuelve la denominacion o NULL
void freeAeroLista(AeroListaADT aerolista);//libera una aerolista






typedef struct VueloCDT* VueloADT;
typedef struct FechaDataType{
    int dia;
    int mes;
    int anio;
}FechaT;

VueloADT newVuelo();// crea un vuelo

//setea el oaciobj(oaci de origen si es un despegue u oaci de destino si es un aterrizaje )
void setOaciObjVuelo(VueloADT vuelo,const char* oaci);
void setFechaVuelo(VueloADT vuelo,FechaT fecha);//setea la fecha
void setClaseVuelo(VueloADT vuelo,enum Clase clase);
void setClasificacionVuelo(VueloADT vuelo,enum Clasificacion clasificacion);

char* getOaciObjVuelo(VueloADT vuelo);
FechaT getFechaVuelo(VueloADT vuelo);
int getClaseVuelo(VueloADT vuelo);
int getClasificacionVuelo(VueloADT vuelo);

void freeVuelo(VueloADT vuelo);//libera un vuelo

#endif //TPE_PI_TAD_H
