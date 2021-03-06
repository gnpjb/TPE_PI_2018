#include "SecondQuery.h"
#include <stdlib.h>
#define LONG_SEMANA 7

//tiene que coincidir con la cantidad de dias de la semana
const char* const DIAS_DE_LA_SEMANA[] = {"Lunes","Martes","Miercoles","Jueves","Viernes","Sabado","Domingo"};
//debe coincidir con ENUM_CLASE_AMOUNT y con el orden de enum Clase
const char* const CLASES[] = {"Regular", "No Regular","Vuelo Privado"};
//debe coincidir con ENUM_CLASE_AMOUNT y con el orden de enum Clase
const char* const CLASIFICACIONES[] = {"Cabotaje","Internacional","Not Available"};


struct SecondQueryCDT{
    long cabotaje[LONG_SEMANA];
    long internacional[LONG_SEMANA];
    long comp_mov[ENUM_CLASIFICACION_AMOUNT-1][ENUM_CLASE_AMOUNT];
};

SecondQuery newSecondQuery(){
    SecondQuery query= calloc(1,sizeof(struct SecondQueryCDT));
    return query;
}
//FUNCION AUXILIAR
//algoritmo de zeller
int getDiaDeLaSemana(FechaT fecha) {
    int h,q,m,j,k;

    //calculo de los coeficientes
    q=fecha.dia;
    m=fecha.mes<=2?fecha.mes+12:fecha.mes;
    j=fecha.anio/100;
    k=fecha.anio%100;
    //calculo de h
    h=(q*((13*(m+1))/5)+k+k/4+j/4+5*j);
    h=h%7;
    //tranformo h en lo que necesito(0=lunes)
    h=h==0?h+7:h;
    h=h-1;

    return h;
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
            default:
                break;
        }
        query->comp_mov[clasificacion][clase]+=1;
    }
}

void printSecondQuery(SecondQuery query,FILE* file1,FILE* file2){
    fprintf(file1,"Dia;Cabotaje;Internacional;Total\n");
    for(int i=0; i<LONG_SEMANA; i++){
        fprintf(file1,"%s;%ld;%ld;%ld\n",DIAS_DE_LA_SEMANA[i],query->cabotaje[i],query->internacional[i],
                query->cabotaje[i]+query->internacional[i]);
    }
    fprintf(file2,"Clasificacion de vuelo;Clase de vuelo;Movimientos\n");
    for(int i=0; i<ENUM_CLASIFICACION_AMOUNT-1; i++){
        for(int j=0; j<ENUM_CLASE_AMOUNT; j++){
            fprintf(file2,"%s;%s;%ld\n",CLASIFICACIONES[i],CLASES[j],query->comp_mov[i][j]);
        }
    }
}
void freeSecondQuery(SecondQuery query){
    free(query);
}
