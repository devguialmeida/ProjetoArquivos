#include <stdio.h>
#include "../include/endereco.h"
#include <string.h>



int c = 0;

int busca_bin(Endereco * e, FILE * f, char * cep, int inicio, int fim) 
{

  if (inicio > fim) {
    return 0;
  }  

  int meio = (inicio + fim) / 2;



  fseek(f, meio * sizeof(Endereco), SEEK_SET);
  fread(e, sizeof(Endereco), 1 , f);
  
  c++;
  
  int cmp = strncmp(e->cep, cep, 8);

  if (cmp == 0) {
    return 1;
  }
  else if (cmp > 0) {
   return busca_bin(e,f,cep,inicio,meio-1);
  }
  else {
    return busca_bin(e,f,cep,meio+1, fim);
  }
}


int main (int argc, char ** argv)
{   
  FILE * fPtr;
  Endereco e;
  // int qt;


  if (argc != 2) {
    fprintf(stderr, "USO: %s [CEP]\n", argv[0]);
    return 1;
  }
  
  c = 0;

  if((fPtr = fopen("data/novo.dat", "rb")) == NULL) {
    printf("Erro ao abrir o arquivo. O programa será abortado.\n");
    printf("\033[0;31mVocê chegou a compilar e executar ordena.c? Este programa %s utiliza o arquivo \"novo.dat\", o qual é gerado por external merge sort, para buscar o CEP.\033[0m\n", argv[0]);
    return 1;
  }

  long int tam;
  fseek(fPtr,0,SEEK_END);
  tam = ftell(fPtr)/sizeof(Endereco);
  rewind(fPtr);

  int achei = busca_bin(&e, fPtr, argv[1],0 , tam);
  if (achei == 0) {
    printf("Não existe tal CEP!\n");
    return 1;
  } 
  else {
    printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n", e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);
  }

  printf("Total lido: %d\n", c);
  fclose(fPtr);


  return 0;
}
