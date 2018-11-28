#ifndef TPE_PI_FIRSTQUERY_H
#define TPE_PI_FIRSTQUERY_H
#include <stdio.h>
#include "TAD.h"


typedef struct FirstQueryCDT* FirstQuery;

FirstQuery newFirstQuery(AeroListaADT aerolistaAsociada);//crea un query con la aerolista asociada
void queryFirstQuery(FirstQuery query,VueloADT vuelo);//procesa un vuelo
void printFirstQuery(FirstQuery query,FILE* file);//imprime el query al archivo
void freeFirstQuery(FirstQuery query);//libera el query(pero no la aerolista asociada)

#endif //TPE_PI_FIRSTQUERY_H
