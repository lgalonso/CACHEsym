#include <stdio.h>
#include <string.h>
#include <math.h>


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


int main() {
   char acceso[] = "02E4";
   int palabra =-1;
   int linea =-1;
   int ETQ =-1;
   int bloque =-1;

   traduccionAcceso(acceso, &palabra, &linea, &ETQ, &bloque);

   printf("palabra %d 0x%X\n", palabra, palabra);
   printf("ETQ %d 0x%X\n", ETQ, ETQ);
   printf("bloque %d 0x%X\n", bloque, bloque);
   printf("linea %d 0x%X\n", linea, linea);

   return 0;
}

