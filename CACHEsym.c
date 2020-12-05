#include <stdio.h>
#include <stdlib.h>

typedef struct {
 short int ETQ;
 short int Datos[8];
} T_LINEA_CACHE;


void inicio(unsigned char RAM[1024], T_LINEA_CACHE Cache[4]){
 FILE *LeerRAM;
 LeerRAM = fopen("RAM.bin","r");
 fread(RAM, 1, 1024, LeerRAM);
 int i,j;
 for(i=0; i<4; i++){
  Cache[i].ETQ=255;
  for(j=0; j<8; j++){
   Cache[i].Datos[j]=0;
   //printf("ETQ: %d, Dato: %d", Cache[i].ETQ, Cache[i].Datos[j]);
  }
 }
 fclose(LeerRAM);
}

void LeerLinea(char LineaLeida[5], int linea){
 FILE *Linea;
 Linea = fopen("accesos_memoria.txt", "r");
 int i;
 for(i=0; i<linea; i++){
  fgets(LineaLeida, 5, Linea);
  fgetc(Linea);
  printf("%s", LineaLeida);
 }
 fclose(Linea);
}

void main(){
 unsigned char RAM[1024];
 char Linea[5];
 T_LINEA_CACHE Cache[4];
 inicio(RAM, Cache);
 //printf("\n%s",RAM);
 LeerLinea(Linea,3);
}
