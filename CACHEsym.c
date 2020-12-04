#include <stdio.h>
#include <string.h>
#include <math.h>


void traduccionAcceso(char[4]);
// Recibe una direccion de acceso y la descompone en bloque, linea, ETQ y palabra
// Sabemos que los 3 ultimos bits son para la palabra, 2 para la linea y 5 para la ETQ
void traduccionAcceso(char acceso[]){
   printf("Traduciendo: %s...\n", acceso);

   // Funcion que convierte la parte inicial de un string en un long int segun la base indicada
   int num = (int)strtol(acceso, NULL, 16);

   int palabra = num & 0x0007;
   // Dividimo por un numero en base 2 para quedarnos con los bits que nos interesan
   int linea = (num & 0x0018)/pow(2,3);
   int ETQ = (num & 0x03E0)/pow(2,5);
   int bloque = (num & 0x03F8)/pow(2,3);
   

   printf("palabra %d 0x%X\n", palabra, palabra);
   printf("ETQ %d 0x%X\n", ETQ, ETQ);
   printf("bloque %d 0x%X\n", bloque, bloque);
   printf("linea %d 0x%X\n", linea, linea);
}


int main() {
   char acceso[] = "02E4";

   traduccionAcceso(acceso);

   return 0;
}

