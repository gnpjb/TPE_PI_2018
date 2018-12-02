#include <stdio.h>
#include "src/TAD.h"
#include "src/Loaders.h"
#include "src/FirstQuery.h"
#include "src/SecondQuery.h"

int main(int argc,char* argv[]) {
    if(argc!=3){
        printf("Incorrecta cantidad de argumentos. Deben ser 2(el archivo de aeropuertos seguido del de movimientos)\n");
        return 1;
    }
    const char *aeropuertos_filename=argv[1];
    const char *vuelos_filename=argv[2];
    const char query1_filename[]="movimientos_aeropuertos.csv";
    const char query2_filename[]="dia_semana.csv";
    const char query3_filename[]="composicion.csv";

    //Carga los aeropuertos a memoria
    FILE* faeropuertos=fopen(aeropuertos_filename,"rt");
    if(faeropuertos==NULL){
        printf("no se pudo abrir %s\n",aeropuertos_filename);
        return 1;
    }
    AeroListaADT aeroLista=newAeroLista();
    cargarAerolista(faeropuertos,aeroLista);
    fclose(faeropuertos);

    //inicializo los queries
    FirstQuery firstQuery=newFirstQuery(aeroLista);
    SecondQuery secondQuery=newSecondQuery();

    //crea un vuelo auxiliar
    VueloADT vuelo=newVuelo();
    FILE* fvuelos=fopen(vuelos_filename,"rt");
    if(fvuelos==NULL){
        printf("no se pudo abrir %s\n",vuelos_filename);
        freeFirstQuery(firstQuery);
        freeSecondQuery(secondQuery);
        freeVuelo(vuelo);
        freeAeroLista(aeroLista);
        return 1;
    }
    //carga los vuelos y los procesa
    skipLine(fvuelos);
    while(cargarVuelo(fvuelos,vuelo)){
        queryFirstQuery(firstQuery,vuelo);
        querySecondQuery(secondQuery,vuelo);
    }
    //libera el vuelo auxiliar
    freeVuelo(vuelo);




    //crea el archivo de salida del first query y lo manda a imprimir. luego cierra el archivo y libera firstquery
    FILE* ffirstquery=fopen(query1_filename,"wt");
    if(ffirstquery==NULL){
        printf("no se pudo abrir %s\n",query1_filename);
        freeFirstQuery(firstQuery);
        freeSecondQuery(secondQuery);
        freeAeroLista(aeroLista);
        return 1;
    }
    closeFirstQuery(firstQuery);
    printFirstQuery(firstQuery,ffirstquery);
    fclose(ffirstquery);
    freeFirstQuery(firstQuery);

    //libera la aerolista ya que ya no se necesita
    freeAeroLista(aeroLista);

    //crea los archivos de salida del secondquery y lo manda a imprimir. luego cierra los archivos y libera secondquery
    FILE* fsecondquery1=fopen(query2_filename,"wt");
    if(fsecondquery1==NULL){
        printf("no se pudo abrir %s\n",query2_filename);
        freeSecondQuery(secondQuery);
        freeAeroLista(aeroLista);
        return 1;
    }
    FILE* fsecondquery2=fopen(query3_filename,"wt");
    if(fsecondquery2==NULL){
        printf("no se pudo abrir %s\n",query3_filename);
        freeSecondQuery(secondQuery);
        freeAeroLista(aeroLista);
        return 1;
    }printSecondQuery(secondQuery,fsecondquery1,fsecondquery2);
    fclose(fsecondquery1);
    fclose(fsecondquery2);
    freeSecondQuery(secondQuery);

}