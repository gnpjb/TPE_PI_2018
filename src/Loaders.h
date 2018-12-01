#ifndef _TPE_PI_LOADERS_H
#define _TPE_PI_LOADERS_H

#include <stdio.h>
#include "TAD.h"


//se salte una linea
void skipLine(FILE* file);
//carga el vuelo que esta en la linea en la que este el archivo al vuelo que se le paso
//devuelve 1 si se pudo cargar y 0 sino
int cargarVuelo(FILE* file,VueloADT vuelo);
//carga la lista de aeropuertos que se le paso a la aerolista que se le paso
void cargarAerolista(FILE*file,AeroListaADT aerolista);

#endif //_TPE_PI_LOADERS_H
