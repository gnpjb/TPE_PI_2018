#ifndef TPE_PI_TAD_H
#define TPE_PI_TAD_H

#define LONG_OACI 4

#define ENUM_CLASE_AMOUNT 3
#define ENUM_CLASIFICACION_AMOUNT 3
enum Clase {V_REG=0,V_NREG,V_PRIV};
enum Clasificacion {V_CAB=0,V_INT,V_NA};

//devuelve -1 si oaci1<oaci2
//0 si oaci1==oaci2
//1 si oaci1>oaci2
int oaciCompare(const char oaci1[],const char oaci2[]);
char *cloneDenominacion(const char* denominacion);
void oaciCopy(char oaciDest[],const char oaciSrc[]);


typedef struct AeropuertoCDT* AeropuertoADT;

AeropuertoADT newAeropuerto();//crea un nuevo aeropuerto
void setOaciAeropuerto(AeropuertoADT aeropuerto, const char *oaci);//setea el oaci
void setDenominacionAeropuerto(AeropuertoADT aeropuerto, char *denominacion);//setea la denominacion del aeropuerto(no crea un nuevo string)
char *getOaciAeropuerto(AeropuertoADT aeropuerto);//devuelve el oaci del aeropuerto
char *getDenominacionAeropuerto(AeropuertoADT aeropuerto);//devuelve la denominacion del aeropuerto
void freeAeropuerto(AeropuertoADT aeropuerto);




typedef struct AeroListaCDT *AeroListaADT;
AeroListaADT newAeroLista();//crea un aerolista vacia
//agrega un aeropuerto a la aerolista(aeropuerto es consumido y ya no es utilizable)
void addAeropuerto(AeroListaADT aerolista,AeropuertoADT aeropuerto);
char *getDenominacionAerolista(AeroListaADT aerolista,const char* oaci);//devuelve la denominacion o NULL
//un simple iterador sobre la lista
void initIteratorAerolista(AeroListaADT aeroLista);
AeropuertoADT getNextAerolista(AeroListaADT aeroLista);
int hasNextAerolista(AeroListaADT aeroLista);
// devuelve el tamaño de la lista(la cantidad de aeropuertos)
int getSizeAerolista(AeroListaADT aerolista);
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
