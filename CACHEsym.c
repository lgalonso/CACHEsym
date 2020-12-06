#include <stdio.h>
#include <stdlib.h>

#define N 1024

typedef struct {
 short int ETQ;
 short int Datos[8];
} T_LINEA_CACHE;


void inicio(unsigned char RAM[N], T_LINEA_CACHE Cache[4]){
 FILE *LeerRAM;
 LeerRAM = fopen("RAM.bin","r");
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
}

int LeerLinea(char LineaLeida[5], int linea){
 FILE *Linea;
 Linea = fopen("accesos_memoria.txt", "r");
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

void main(){
 unsigned char RAM[N];
 char Linea[5];
 T_LINEA_CACHE Cache[4];
 inicio(RAM, Cache);
 //printf("\n%s\n",RAM);
 LeerLinea(Linea,3);
}
