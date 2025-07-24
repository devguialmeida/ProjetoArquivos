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
    for (long i = 0; i < qtd; i++) {
        fread(&e, sizeof(Endereco), 1, f);
        strncpy(vecIndice[i].cep, e.cep, 8);
        vecIndice[i].cep[8] = '\0'; // garantir terminação
        vecIndice[i].posicao = i;
    }

   
    qsort(vecIndice, qtd, sizeof(IndiceCEP), comparaIndice);
    saida = fopen("data/CEP_indices.dat", "wb");
    fwrite(vecIndice, sizeof(IndiceCEP), qtd, saida);
    fclose(f);
    fclose(saida);
    free(vecIndice);

}
