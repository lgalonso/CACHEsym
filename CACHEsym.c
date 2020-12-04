#include <stdio.h>
#include <string.h>
#include <math.h>


void traduccionAcceso(char[4]);
//Recibe una direccion de acceso y la descompone en bloque, linea, ETQ y palabra
//Sabemos que los 3 ultimos bits son para la palabra, 2 para la linea y 5 para la ETQ
void traduccionAcceso(char acceso[]){
   printf("Traduciendo: %s!\n", acceso);

   int num = (int)strtol(acceso, NULL, 16);

   int palabra = num & 0x0007;
   int linea = (num & 0x0018)/pow(2,3);
   int ETQ = (num & 0x03E0)/pow(2,5);
   int bloque = (num & 0x03F8)/pow(2,3);
   

   printf("palabra %d %X\n", palabra, palabra);
   printf("ETQ %d %X\n", ETQ, ETQ);
   printf("bloque %d %X\n", bloque, bloque);
   printf("linea %d %X\n", linea, linea);
}


int main() {
   char acceso[] = "02E4";
   int num = (int)strtol(acceso, NULL, 16);
   int arr_accesos[] = {0x02E4};

   printf("Hello, %X %X!\n", arr_accesos[0], num);

   traduccionAcceso(acceso);

   return 0;
}

