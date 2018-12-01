#ifndef TPE_PI_SECONDQUERY_H
#define TPE_PI_SECONDQUERY_H

#include <stdio.h>
#include "TAD.h"


typedef struct SecondQueryCDT* SecondQuery;

SecondQuery newSecondQuery();// crea un query
void querySecondQuery(SecondQuery query,VueloADT vuelo);// procesa un vuelo en el query
//imprime el query a los files (query2 a file1 query3 a file2)
void printSecondQuery(SecondQuery query,FILE* file1,FILE* file2);
void freeSecondQuery(SecondQuery query);//libera el query


#endif //TPE_PI_SECONDQUERY_H
