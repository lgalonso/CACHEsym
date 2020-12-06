#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

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
  fgetc(Linea);
  //printf("%s", LineaLeida);
 }
 fgetc(Linea);
  if(feof(Linea)){
   return 0;
  }
 fclose(Linea);
 return 1;
}

// Recibe una direccion de acceso y la guarda en bloque, linea, ETQ y palabra que se pasan por referencia
// Sabemos que los 3 ultimos bits son para la palabra, 2 para la linea y 5 para la ETQ
void traduccionAcceso(char* acceso, int* palabra, int* linea, int* etq, int* bloque, int* acceso_hex){
   printf("Traduciendo: %s...\n", acceso);

   // Funcion que convierte la parte inicial de un string en un long int segun la base indicada
   int num = (int)strtol(acceso, NULL, 16);

   *acceso_hex = num;
   *palabra = num & 0x0007;
   // Dividimos por un numero en base 2 para quedarnos con los bits que nos interesan
   *linea = (num & 0x0018)/pow(2,3);
   *etq = (num & 0x03E0)/pow(2,5);
   *bloque = (num & 0x03F8)/pow(2,3);
}

void printfail(int tiempo, int palabra, int linea, int etiqueta, int bloque, int acceso_hex, int fallos){
    printf("T:%d, Fallo de CACHE %d, ADDR %04X ETQ %X linea %02X palabra %02X bloque %02X\n", tiempo, fallos, acceso_hex, etiqueta, linea, palabra, bloque);
}

void printsuccess(int tiempo, int palabra, int linea, int etiqueta, int acceso_hex, int dato){
    printf("T:%d, Acierto de CACHE, ADDR %04X ETQ %X linea %02X palabra %02X DATO %02X\n", tiempo, acceso_hex, etiqueta, linea, palabra, dato);
}

//Busca la linea de la cache y compara las etiquetas, si la etiqueta está bién, devuelve
int busqueda(T_LINEA_CACHE *cache, int palabra, int linea, int etiqueta, int *tiempo, int *fallos, int acceso_hex, int bloque){

    if(cache[linea].ETQ == etiqueta){
        //Recoge el dato
        int dato = cache[linea].Datos[palabra];
        //Llama a Imprimir Acierto
        printsuccess(*tiempo, palabra, linea, etiqueta, acceso_hex, dato);
        return 1;
        //Modificar Tiempo
    }
    else{
    *(fallos) = *(fallos) + 1;
    //Llama a Imprimir Fallo
    printfail(*tiempo, palabra, linea, etiqueta, bloque, acceso_hex, *fallos);
    *(tiempo) = *(tiempo) + 10;
    //Modificar Tiempo
    return 0;
    }

}

int loadram(unsigned char *RAM, int bloque, T_LINEA_CACHE *cache, int linea, int etiqueta){
    if(bloque > 127){
        return 0;
    }
    int x;
    printf("Cargando el bloque %02X en la linea %02X\n", bloque, linea);
    for(x = 0; x < 8; x++){
        cache->Datos[x] = RAM[(bloque*8) + x];
    }
    cache->ETQ = etiqueta;
    return 1;
}

//Funcion sleep

void main(){
 int tiempoglobal = 0;
 int numfallos = 0;
 unsigned char RAM[N];
 char acceso[5];
 T_LINEA_CACHE Cache[4];
 if (inicio(RAM, Cache) == -1){
  exit(-1);
 }
 if (LeerLinea(acceso,1) == -1){
  exit(-1);
 }

 int etiqueta = -1;
 int linea = -1;
 int palabra = -1;
 int bloque = -1;
 int acceso_hex = -1;
 int i,j,o=1,m=1;
 char textototal[100];

 //Bucle de lineas

 traduccionAcceso(acceso, &palabra, &linea, &etiqueta, &bloque, &acceso_hex);

 for(;m!=0;o++){
  if(o!=1){
   m=LeerLinea(acceso,o);
   traduccionAcceso(acceso, &palabra, &linea, &etiqueta, &bloque, &acceso_hex);
  }
  if(busqueda(Cache, palabra, linea, etiqueta, &tiempoglobal, &numfallos, acceso_hex, bloque) == 0){
    loadram(RAM, bloque, &(Cache[linea]), linea, etiqueta);
    printsuccess(tiempoglobal, palabra, linea, etiqueta, acceso_hex, Cache[linea].Datos[palabra]);
  }
  textototal[o-1]=Cache[linea].Datos[palabra];
  for(i=0;i<4;i++){
   printf("ETQ:%02X\tDatos ", Cache[i].ETQ);
   for(j=7;j>=0;j--){
    printf("%02X ",Cache[i].Datos[j]);
   }
   printf("\n");
  }
  sleep(2);
  tiempoglobal+=2;
 }
 textototal[o-1]='\0';
 float ofloat = (float)o-1;
 float fallosfloat = (float)numfallos;
 float tiempomedio = 2*(1-(fallosfloat/(ofloat)))+10*(fallosfloat/(ofloat));
 printf("Acesos totales: %d\nFallos totales: %d\nTiempo medio de acceso: %.2f\n",o-1,numfallos, tiempomedio);
 printf("El texto leido es: %s\n", textototal);
//printf("\n%s\n",RAM);
}
