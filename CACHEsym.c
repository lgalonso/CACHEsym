#include <stdio.h>
#include <stdlib.h>

#define N 1024

typedef struct {
 short int ETQ;
 short int Datos[8];
} T_LINEA_CACHE;


int inicio(unsigned char RAM[N], T_LINEA_CACHE Cache[4]){
 FILE *LeerRAM;
 LeerRAM = fopen("RAM.bin","r");
 if(LeerRAM == NULL){
 return -1;
 }
 fread(RAM, 1, N, LeerRAM);
 int i,j;
 for(i=0; i<4; i++){
  Cache[i].ETQ=255;
  for(j=0; j<8; j++){
   Cache[i].Datos[j]=0;
   //printf("ETQ: %d, Dato: %d", Cache[i].ETQ, Cache[i].Datos[j]);
  }
 }
 fclose(LeerRAM);
 return 1;
}

int LeerLinea(char LineaLeida[5], int linea){
 FILE *Linea;
 Linea = fopen("accesos_memoria.txt", "r");
 if(Linea == NULL){
 return -1;
 }
 int i;
 for(i=0; i<linea; i++){
  fgets(LineaLeida, 5, Linea);
  if(feof(Linea)){
   return 0;
  } else {
   fgetc(Linea);
  }
  //printf("%s", LineaLeida);
 }
 fclose(Linea);
 return 1;
}

// Recibe una direccion de acceso y la guarda en bloque, linea, ETQ y palabra que se pasan por referencia
// Sabemos que los 3 ultimos bits son para la palabra, 2 para la linea y 5 para la ETQ
void traduccionAcceso(char* acceso, int* palabra, int* linea, int* etq, int* bloque){
   printf("Traduciendo: %s...\n", acceso);

   // Funcion que convierte la parte inicial de un string en un long int segun la base indicada
   int num = (int)strtol(acceso, NULL, 16);

   *palabra = num & 0x0007;
   // Dividimos por un numero en base 2 para quedarnos con los bits que nos interesan
   *linea = (num & 0x0018)/pow(2,3);
   *etq = (num & 0x03E0)/pow(2,5);
   *bloque = (num & 0x03F8)/pow(2,3);
   
}

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

void main(){
 unsigned char RAM[N];
 char Linea[5];
 T_LINEA_CACHE Cache[4];
 inicio(RAM, Cache);
 LeerLinea(Linea,3);
 printf("\n%s\n",RAM);
}
