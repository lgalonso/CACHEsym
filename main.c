include <stdio.h>
include <stdlib.h>

typedef struct {
    short int ETQ;
    short int Datos[8];
} T_LINEA_CACHE

void printfail(int tiempo, int palabra, int linea, int etiqueta, int bloque, int acceso, int fallos){
    printf("T:%d, Fallo de CACHE %d, ADDR %04X ETQ %X linea %02X palabra %02X bloque %02X", tiempo, fallos, acceso, etiqueta, linea, palabra, bloque);
}

void printsuccess(int tiempo, int palabra, int linea, int etiqueta, int acceso, int dato){
    printf("T:%d, Acierto de CACHE, ADDR %04X ETQ %X linea %02X palabra %02X DATO %02X", tiempo, acceso, etiqueta, linea, palabra, dato);
}

//Busca la linea de la cache y compara las etiquetas, si la etiqueta está bién, devuelve
int busqueda(T_LINEA_CACHE *cache, int palabra, int linea, int etiqueta, int *tiempo, int *fallos, int acceso, int bloque){

    if(cache[linea].ETQ == etiqueta){
        //Recoge el dato
        dato = cache[linea].Datos[palabra];
        //Llama a Imprimir Acierto
        printsuccess(*tiempo, palabra, linea, etiqueta, acceso, dato);
        return 1;
        //Modificar Tiempo
    }
    else
    //Llama a Imprimir Fallo
    printfail(*tiempo, palabra, linea, etiqueta, bloque, acceso, *fallos);
    //Llama a Cargar de la Ram a la Caché
    //Modificar Tiempo
    return 0;
}




int main(){

}