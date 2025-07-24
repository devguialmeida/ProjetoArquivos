#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/endereco.h"


int compara ( const void * e1, const void * e2 ) {
    return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}


void intercala(FILE * f1, FILE * f2, FILE * saida) {
    // FILE * saida = fopen(nomeSaida, "wb");
    Endereco ea, eb;
    fread(&ea, sizeof(Endereco) ,1 ,f1);
    fread(&eb, sizeof(Endereco) ,1 ,f2);

    while (!feof(f1) && !feof(f2)) {
        if (compara(&ea, &eb) < 0) {
            fwrite(&ea, sizeof(Endereco), 1, saida);
            fread(&ea, sizeof(Endereco), 1, f1);
        }
        else {
            fwrite(&eb, sizeof(Endereco), 1, saida);
            fread(&eb, sizeof(Endereco), 1, f2);
        }
    }

    while(!feof(f1)) {
        fwrite(&ea, sizeof(Endereco), 1, saida);
        fread(&ea, sizeof(Endereco), 1, f1);
    }

    while(!feof(f2)) {
        fwrite(&eb, sizeof(Endereco), 1, saida);
        fread(&eb, sizeof(Endereco), 1, f2);
    }

    
    fclose(saida);


}



int main (void)
{
    FILE * fPtr;
    Endereco * e;
    long qtdParcelas = 8;
    long qtdEnderecos, posicao, parcela;

    

    fPtr = fopen("data/cep.dat", "rb");
    if(fPtr == NULL) {
        printf("Não foi possível abrir o arquivo. O programa será abortado.\n");
        return 1;
    }
    fseek(fPtr,0,SEEK_END);
    posicao = ftell(fPtr);
    qtdEnderecos = posicao / sizeof(Endereco);
    parcela = (long) qtdEnderecos / qtdParcelas;
    e = (Endereco *) malloc(sizeof(Endereco) * parcela);
    rewind(fPtr);
    
    if ((long) fread(e,sizeof(Endereco),parcela, fPtr) ==  parcela) {
        printf("Lido = OK!\n");
    }
    
    rewind(fPtr);
    char nomeArq[100];
    
    long restante = qtdEnderecos;

    for (int i = 0; i < qtdParcelas && restante > 0; i++) {
        FILE * iParcelaPtr;
        sprintf(nomeArq, "data/a%d.dat", i);
        iParcelaPtr = fopen(nomeArq,"wb");

        long qtdLer = parcela;
        if (i == qtdParcelas - 1) {
            qtdLer = restante; // lê o que sobrou
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
    
    for (int i = 0; i < (qtdParcelas-1) * 2; i+=2) {
        char iNomeParcela[100];
        char proxNomeParcela[100];
        char nomeSaida[100];
        
        sprintf(iNomeParcela, "data/a%d.dat", i);
        sprintf(proxNomeParcela, "data/a%d.dat", i+1);
        sprintf(nomeSaida, "data/a%d.dat", indexSaida);
        
        FILE * saida = fopen(nomeSaida, "wb");
        FILE * iParcelaPtr = fopen(iNomeParcela, "rb");
        FILE * proxParcelaPtr = fopen(proxNomeParcela, "rb");
        
        printf("Merge a%d with a%d. Output ----> a%d\n", i, i+1, indexSaida);
        remove(iNomeParcela);
        remove(proxNomeParcela);
        intercala(iParcelaPtr, proxParcelaPtr, saida);
        indexSaida++;
    }

    rename("data/a14.dat", "data/novo.dat");

    



}
