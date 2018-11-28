#ifndef TPE_PI_SECONDQUERY_H
#define TPE_PI_SECONDQUERY_H

#include <stdio.h>
#include "TAD.h"


typedef struct SecondQueryCDT* SecondQuery;

SecondQuery newSecondQuery();// crea un query
void querySecondQuery(SecondQuery query,VueloADT vuelo);// procesa un vuelo en el query
void printSecondQuery(SecondQuery query,FILE* file);//TODO imprime el query al file
void freeSecondQuery(SecondQuery query);//libera el query


#endif //TPE_PI_SECONDQUERY_H
