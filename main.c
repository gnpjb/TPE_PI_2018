#include <stdio.h>
#include "src/TAD.h"
#include "src/Loaders.h"
#include "src/FirstQuery.h"
#include "src/SecondQuery.h"

int main(int argc,char* argv[]) {
    if(argc!=3){
        printf("Incorrecta cantidad de argumentos. Deben ser 2(el archivo de aeropuertos seguido del de movimientos)");
        return 1;
    }

    //Carga los aeropuertos a memoria
    FILE* faeropuertos=fopen(argv[1],"rt");
    AeroListaADT aeroLista=newAeroLista();
    cargarAerolista(faeropuertos,aeroLista);
    fclose(faeropuertos);

    //inicializo los queries
    FirstQuery firstQuery=newFirstQuery(aeroLista);
    SecondQuery secondQuery=newSecondQuery();

    //crea un vuelo auxiliar
    VueloADT vuelo=newVuelo();
    FILE* fvuelos=fopen(argv[2],"rt");

    //carga los vuelos y los procesa
    while(cargarVuelo(fvuelos,vuelo)){
        queryFirstQuery(firstQuery,vuelo);
        querySecondQuery(secondQuery,vuelo);
    }
    //libera el vuelo auxiliar
    freeVuelo(vuelo);

    //cierra el query 1
    closeFirstQuery(firstQuery);


    //crea el archivo de salida del first query y lo manda a imprimir. luego cierra el archivo y libera firstquery
    FILE* ffirstquery=fopen("movimientos_aeropuertos.csv","wt");
    printFirstQuery(firstQuery,ffirstquery);
    fclose(ffirstquery);
    freeFirstQuery(firstQuery);

    //libera la aerolista ya que ya no se necesita
    freeAeroLista(aeroLista);
    
    //crea los archivos de salida del secondquery y lo manda a imprimir. luego cierra los archivos y libera secondquery
    FILE* fsecondquery1=fopen("dia_semana.csv","wt");
    FILE* fsecondquery2=fopen("composicion.csv","wt");
    printSecondQuery(secondQuery,fsecondquery1,fsecondquery2);
    fclose(fsecondquery1);
    fclose(fsecondquery2);
    freeSecondQuery(secondQuery);
    
}