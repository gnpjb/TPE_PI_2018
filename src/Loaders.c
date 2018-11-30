#include "Loaders.h"
#include <stdlib.h>
#include <string.h>
#define INIT_BLOCK 10
#define CHAR_DIG(c) ((c)-'0')

//FUNCION AUXILIAR


char* getComaSepField(FILE* file, char* field,int* size){
    int c=fgetc(file);
    if(*size==0){
        field=malloc(INIT_BLOCK);
        *size=INIT_BLOCK;
    }
    if(c!=';'&&c!='\n'){
        field[0]=c;
        int charsRead=1;
        while((c=fgetc(file))!=';'&&c!='\n'&&c!=EOF){
            if((charsRead+1)==*size){
                field=realloc(field,*size+INIT_BLOCK);
                *size=*size+INIT_BLOCK;
            }
            field[charsRead++]=c;
        }
        field[charsRead]=0;
    }
    else if(c==';'){
        field[0]=0;
    }
    return field;
}


//avanza la posicion del archivo un field
void skipField(FILE* file){
    int c=fgetc(file);
    while(c!=';'&&c!='\n'&&c!=EOF){
        c=fgetc(file);
    }
}
void skipLine(FILE* file){
    int c=fgetc(file);
    while(c!='\n'&&c!=EOF){
        c=fgetc(file);
    }
}


//Transforma un strng con una fecha en formato dd/mm/aaaa a un FechaT
FechaT stringToFecha(const char* fecha){
    FechaT ret;
    ret.dia=CHAR_DIG(fecha[0])*10+CHAR_DIG(fecha[1]);
    ret.mes=CHAR_DIG(fecha[3])*10+CHAR_DIG(fecha[4]);
    ret.anio=CHAR_DIG(fecha[6])*1000+CHAR_DIG(fecha[7])*100+CHAR_DIG(fecha[8])*10+CHAR_DIG(fecha[9]);
    return ret;
}


//devuelve la clase en base a un string
//debera ser cambiado si cambian las clases
enum Clase stringToClase(const char * clase){
    if(clase[0]=='V'){
        return V_PRIV;
    }
    if(clase[0]=='R'){
        return V_REG;
    }
    return V_NREG;
}

//devuelve la clasificacion en base a un string
//debera ser cambiado si cambian las clasificacion
enum Clasificacion stringToClasificacion(const char * clasificacion){

    if(clasificacion[0]=='I'){
        return V_INT;
    }
    if(clasificacion[0]=='C'){
        return V_CAB;
    }
    return V_NA;
}


//FUNCION AUXILIAR

int cargarVuelo(FILE* file,VueloADT vuelo){
    if(feof(file)){
        return 0;
    }
    int size=INIT_BLOCK*2;
    char *field=malloc(size);

    getComaSepField(file,field,&size);//obtiene la fecha como string
    setFechaVuelo(vuelo,stringToFecha(field));

    skipField(file);//se saltea la hora

    getComaSepField(file, field,&size);//obtiene la clase
    setClaseVuelo(vuelo,stringToClase(field));

    getComaSepField(file, field, &size);//obtiene la clasificacion
    setClasificacionVuelo(vuelo,stringToClasificacion(field));

    getComaSepField(file,field,&size);//obtiene el tipo de mov
    if(field[0]=='A'){
        //si es un aterrizaje me salteo el de origen y seteo como obj el de destino
        skipField(file);
        getComaSepField(file,field,&size);
        setOaciObjVuelo(vuelo,field);
    }else{
        //seteo el de origen como obj
        setOaciObjVuelo(vuelo,field);
    }

    skipLine(file);
    free(field);

    return 1;

}

void cargarAerolista(FILE*file,AeroListaADT aerolista){

}