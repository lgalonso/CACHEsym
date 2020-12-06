include <stdio.h>
include <stdlib.h>

typedef struct {
    short int ETQ;
    short int Datos[8];
} T_LINEA_CACHE

//Busca la linea de la cache y compara las etiquetas, si la etiqueta está bién, devuelve
int busqueda(T_LINEA_CACHE *cache, int palabra, int linea, int etiqueta){

    if(cache[linea].ETQ == etiqueta){
        //Llama a Imprimir acierto
        return 1
    }
    else
    //Llama a Imprimir Fallo
    //Llama a Cargar de la Ram a la Caché
    return 0
}



int main(){

}