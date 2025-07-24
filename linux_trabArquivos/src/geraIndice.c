#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/indiceCEP.h"
#include "../include/endereco.h"
#include "../include/enderecoUtils.h"


int main () {

    FILE *f, *saida;
	IndiceCEP * vecIndice;
    Endereco e;
	long posicao, qtd;

    f = fopen("data/cep_ordenado.dat","rb");

	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	qtd = posicao/sizeof(Endereco);
    rewind(f);
    vecIndice = (IndiceCEP*) malloc(qtd * sizeof(IndiceCEP));
    int qt = fread(&e, sizeof(Endereco),1,f);
    if (!qt) {
        printf("Houve erro na leitura.\n");
        return 1;
    }
    int indiceAtual = 0;
    while (qt > 0)
    {
        strncpy(vecIndice[indiceAtual].cep, e.cep, 8);
        vecIndice[indiceAtual].posicao = indiceAtual;
        qt = fread(&e, sizeof(Endereco),1,f);
        indiceAtual++;
    }
    // for(int i = 0; i < qtd; i++) {
    //     printf("QTD IS %ld\n",qtd);
    //     printf("Posicao: %x\t CEP: %.8s\n",vecIndice[i].posicao, vecIndice[i].cep);
    //     // getchar();
    // }
    qsort(vecIndice,qtd,sizeof(IndiceCEP),comparaIndice);
    saida = fopen("data/CEP_indices.dat", "wb");
    fwrite(vecIndice, sizeof(IndiceCEP), qtd, saida);
}