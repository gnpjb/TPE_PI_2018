#ifndef TPE_PI_SECONDQUERY_H
#define TPE_PI_SECONDQUERY_H

#include <stdio.h>
#include "TAD.h"


typedef struct SecondQueryCDT* SecondQuery;

SecondQuery newSecondQuery();
void querySecondQuery(SecondQuery query,VueloADT vuelo);
void printSecondQuery(SecondQuery query,FILE* file);
void freeSecondQuery(SecondQuery query);


#endif //TPE_PI_SECONDQUERY_H
