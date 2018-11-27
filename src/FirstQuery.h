#ifndef TPE_PI_FIRSTQUERY_H
#define TPE_PI_FIRSTQUERY_H
#include <stdio.h>
#include "TAD.h"


typedef struct FirstQueryCDT* FirstQuery;

FirstQuery newFirstQuery();
void queryFirstQuery(FirstQuery query,VueloADT vuelo, AeroListaADT aeroLista);
void printFirstQuery(FirstQuery query,FILE* file);
void freeFirstQuery(FirstQuery query);

#endif //TPE_PI_FIRSTQUERY_H
