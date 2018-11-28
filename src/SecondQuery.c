#include "SecondQuery.h"
#include <stdlib.h>
#define LONG_SEMANA 7
#define PRIMER_DIA "lunes"
#define SEGUNDO_DIA "martes"
#define TERCER_DIA "miercoles"
#define CUARTO_DIA "jueves"
#define QUINTO_DIA "viernes"
#define SEXTO_DIA "sabado"
#define SEPTIMO_DIA "domingo"

struct SecondQueryCDT{
    int cabotaje[LONG_SEMANA];
    int internacional[LONG_SEMANA];
    int comp_mov[ENUM_CLASIFICACION_AMOUNT-1][ENUM_CLASE_AMOUNT];
};

SecondQuery newSecondQuery(){
    SecondQuery query= calloc(1,sizeof(struct SecondQueryCDT));
    return query;
}
//FUNCION AUXILIAR

int getDiaDeLaSemana(FechaT fecha) {
    int f,k,m,d,c;

    k=fecha.dia;

    m=fecha.mes;
    m-=2;
    m=m>0?m:m+12;

    d=m>=11?( fecha.anio % 100)-1:fecha.anio%100;

    c=fecha.anio/100;

    f = k + ((13*m - 1)/5) + d + (d/4) + (c/4) - 2*c;//la regla de zeller
    f=f%7;

    return (f==0?7:f)-1;
}

//FUNCION AUXILIAR

void querySecondQuery(SecondQuery query,VueloADT vuelo){
    enum Clasificacion clasificacion=getClasificacionVuelo(vuelo);
    if(clasificacion!=V_NA){
        enum Clase clase=getClaseVuelo(vuelo);
        int diaDeLaSemana=getDiaDeLaSemana(getFechaVuelo(vuelo));
        switch (clasificacion) {
            case V_CAB:
                query->cabotaje[diaDeLaSemana] += 1;
                break;
            case V_INT:
                query->internacional[diaDeLaSemana] += 1;
                break;
        }
        query->comp_mov[clasificacion][clase]+=1;
    }
}

void printSecondQuery(SecondQuery query,FILE* file){
    //TODO
}
void freeSecondQuery(SecondQuery query){
    free(query);
}
