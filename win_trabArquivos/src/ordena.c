#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/endereco.h"

int compara (const void * e1, const void * e2) {
    return strncmp(((Endereco*)e1)->cep, ((Endereco*)e2)->cep, 8);
}

void intercala(FILE *f1, FILE *f2, FILE *saida) {
    Endereco ea, eb;
    int temEa = fread(&ea, sizeof(Endereco), 1, f1);
    int temEb = fread(&eb, sizeof(Endereco), 1, f2);

    while (temEa && temEb) {
        if (compara(&ea, &eb) < 0) {
            fwrite(&ea, sizeof(Endereco), 1, saida);
            temEa = fread(&ea, sizeof(Endereco), 1, f1);
        } else {
            fwrite(&eb, sizeof(Endereco), 1, saida);
            temEb = fread(&eb, sizeof(Endereco), 1, f2);
        }
    }

    while (temEa) {
        fwrite(&ea, sizeof(Endereco), 1, saida);
        temEa = fread(&ea, sizeof(Endereco), 1, f1);
    }

    while (temEb) {
        fwrite(&eb, sizeof(Endereco), 1, saida);
        temEb = fread(&eb, sizeof(Endereco), 1, f2);
    }

    fclose(f1);
    fclose(f2);
    fclose(saida);
}

int main(void) {
    FILE *fPtr;
    Endereco *e;
    int qtdParcelas = 8;
    long qtdEnderecos, posicao, parcela;

    fPtr = fopen("data/cep.dat", "rb");
    fseek(fPtr, 0, SEEK_END);
    posicao = ftell(fPtr);
    qtdEnderecos = posicao / sizeof(Endereco);
    parcela = qtdEnderecos / qtdParcelas;
    e = (Endereco *) malloc(sizeof(Endereco) * parcela);
    rewind(fPtr);
    
    if (fread(e, sizeof(Endereco), parcela, fPtr) == parcela) {
        printf("Lido = OK!\n");
    }

    rewind(fPtr);
    char nomeArq[100];
    long restante = qtdEnderecos;

    for (int i = 0; i < qtdParcelas && restante > 0; i++) {
        FILE *iParcelaPtr;
        sprintf(nomeArq, "data/a%d.dat", i);
        iParcelaPtr = fopen(nomeArq, "wb");

        long qtdLer = parcela;
        if (i == qtdParcelas - 1) {
            qtdLer = restante;
        }

        long qtdLida = fread(e, sizeof(Endereco), qtdLer, fPtr);
        if (qtdLida == 0) break;

        qsort(e, qtdLida, sizeof(Endereco), compara);
        fwrite(e, sizeof(Endereco), qtdLida, iParcelaPtr);
        fclose(iParcelaPtr);

        restante -= qtdLida;
    }

    rewind(fPtr);

    int indexSaida = qtdParcelas;
    char iNomeParcela[100];
    char proxNomeParcela[100];
    char nomeSaida[100];

    for (int i = 0; i < (qtdParcelas - 1) * 2; i += 2) {
        sprintf(iNomeParcela, "data/a%d.dat", i);
        sprintf(proxNomeParcela, "data/a%d.dat", i + 1);
        sprintf(nomeSaida, "data/a%d.dat", indexSaida);

        FILE *saida = fopen(nomeSaida, "wb");
        FILE *iParcelaPtr = fopen(iNomeParcela, "rb");
        FILE *proxParcelaPtr = fopen(proxNomeParcela, "rb");

        printf("Merge a%d with a%d. Output ----> a%d\n", i, i + 1, indexSaida);
        intercala(iParcelaPtr, proxParcelaPtr, saida);
        fclose(iParcelaPtr);
        fclose(proxParcelaPtr);
        remove(iNomeParcela);
        remove(proxNomeParcela);
        indexSaida++;
    }

    char finalNome[30];
    sprintf(finalNome, "data/a%d.dat", indexSaida - 1);
    rename(finalNome, "data/novo.dat");

    return 0;
}
