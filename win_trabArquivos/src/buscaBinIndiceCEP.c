#include <stdio.h>
#include "../include/endereco.h"
#include "../include/indiceCEP.h"
#include <string.h>

int busca_bin(IndiceCEP * vecIndice, FILE * f, char * cep, int inicio, int fim, int * posFinal) 
{

  if (inicio > fim) {
    return 0;
  }  

  int meio = (inicio + fim) / 2;
  
  
  fseek(f, meio * sizeof(IndiceCEP), SEEK_SET);
  fread(vecIndice, sizeof(IndiceCEP), 1 , f);
  printf("Verificando CEP: %.8s na posição (offset): %ld\n", vecIndice->cep, vecIndice->posicao);
  
  
  *posFinal = vecIndice->posicao;
  

  int cmp = strncmp(vecIndice->cep, cep, 8);

  if (cmp == 0) {
    return 1;
  }
  else if (cmp > 0) {
    return busca_bin(vecIndice,f,cep,inicio,meio-1,posFinal);
  }
  else {
    return busca_bin(vecIndice,f,cep,meio+1, fim,posFinal);
  }
}

int main (int argc, char ** argv)
{   
  FILE * fPtr, * f2Ptr;
  IndiceCEP iCep;
  Endereco  e;
  int qt;
  int posFinal;
  posFinal = 0;

  if (argc != 2) {
    fprintf(stderr, "USO: %s [CEP]\n", argv[0]);
    return 1;
  }
  
  if((fPtr = fopen("data/CEP_indices.dat", "rb")) == NULL) {
    printf("Erro ao abrir o arquivo. O programa será abortado.");
    return 1;
  }

  if((f2Ptr = fopen("data/cep_ordenado.dat", "rb")) == NULL) {
    printf("Erro ao abrir o arquivo. O programa será abortado.");
    return 1;
  }

  long int tam;
  fseek(fPtr,0,SEEK_END);
  tam = ftell(fPtr)/sizeof(IndiceCEP);
  rewind(fPtr);

  int achei = busca_bin(&iCep, fPtr, argv[1],0 , tam, &posFinal);
  if (achei == 0) {
    printf("Não existe tal CEP!\n");
    return 1;
  } 
  else {

    fseek(f2Ptr, posFinal * sizeof(Endereco), SEEK_SET);
    fread(&e,sizeof(Endereco),1,f2Ptr);
    printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n", e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);
  }

  fclose(fPtr);


  return 0;
}
