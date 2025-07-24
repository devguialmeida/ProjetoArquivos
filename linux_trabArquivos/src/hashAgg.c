// http://10.101.1.135:1234/sinasc.csv.gz
// http://10.101.1.135:1234/leSinasc.c
// Teresina = 221100
// Curitiba = 410690

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 2048
#define TEST_SIZE 1000 // Padrão definido pelo professor: TEST_SIZE 1000

// index,CODMUNRES,data_nasc,PESO,SEMAGESTAC,adeq_peso_id_gestac,SEXO,IDANOMAL,RACACOR,ESCMAEAGR1,ESTCIVMAE,IDADEMAE,CONSULTAS,PARTO,STTRABPART,KOTELCHUCK,APGAR5,TPROBSON

typedef struct _HashElement HashElement;

struct _HashElement {
    int uf;
    float soma;
    int qtd;    
    HashElement * next;
};


void acumula(HashElement tabela[], int uf, float peso) {
    int pos = uf % 31;
    HashElement * x = &tabela[pos];

    while(x) {
        if(x->uf == uf) {
            x->soma += peso;
            x->qtd++;
            return;
        }
        x = x->next;
    }
    if(tabela[pos].uf == 0) {
        tabela[pos].uf = uf;
        tabela[pos].soma = peso;
        tabela[pos].qtd = 1;
    }
    else {
        x = (HashElement * ) malloc(sizeof(HashElement));
        x->uf = uf;
        x->soma = peso;
        x->qtd = 1;
        x->next = tabela[pos].next;
        tabela[pos].next = x;
    }
}


struct DadosNascimento {
    int index;
    int CODMUNRES;
    char data_nasc[11];
    int PESO;
    int SEMAGESTAC;
    float adeq_peso_id_gestac;
    int SEXO;
    int IDANOMAL;
    int RACACOR;
    int ESCMAEAGR1;
    int ESTCIVMAE;
    int IDADEMAE;
    int CONSULTAS;
    int PARTO;
    int STTRABPART;
    int KOTELCHUCK;
    int APGAR5;
    int TPROBSON;
};

// void separaData(char* data, int *dia, int *mes, int *)
// {
//     *ano = atoi(strtok(data,"-"));
//     *mes = atoi(strtok(NULL,"-"));
//     *dia = atoi(strtok(NULL,"-"));
// }

int hash(int x ) {
    return x / 10000;
}

float totalPesoTeresina = 0;
float totalPesoCuritiba = 0;
int contadorTeresina = 0;
int contadorCuritiba = 0;
int ano = 2015;

void processa(HashElement * he) {
    // int dia, mes, ano;
    // separaData(dn->data_nasc, &dia, &mes, &ano);

    printf("%d %.2f kg\n",he->uf, (float) he->soma/(he->qtd *1000));
}

int main()
{
    
    char *prox = NULL;
    int lc = 0;
    static char buffer[MAX];
    struct DadosNascimento dn;
    char* linha[18];
    HashElement tabela[31];
    for (int i = 0; i < 31; i++) {
        tabela[i].uf = 0;
        tabela[i].soma = 0.0f;
        tabela[i].qtd = 0;
        tabela[i].next = NULL;
    }

    int i;
    FILE *f = fopen("data/sinasc.csv","r");
    fgets(buffer,MAX,f);
    fgets(buffer,MAX,f);
    while(!feof(f)) {
        linha[0] = strtok_r(buffer,",\n",&prox);
        for(i=1; i<18; i++) {
            linha[i] = strtok_r(NULL,",\n",&prox);
            if(linha[i]==NULL) {
                linha[i]="";
            }
        }
        dn.index = atoi(linha[0]);
        dn.CODMUNRES = atoi(linha[1]);
        strcpy(dn.data_nasc,linha[2]);
        dn.PESO = atoi(linha[3]);
        dn.SEMAGESTAC = atoi(linha[4]);
        dn.adeq_peso_id_gestac = atof(linha[5]);
        dn.SEXO = atoi(linha[6]);
        dn.IDANOMAL = atoi(linha[7]);
        dn.RACACOR = atoi(linha[8]);
        dn.ESCMAEAGR1 = atoi(linha[9]);
        dn.ESTCIVMAE = atoi(linha[10]);
        dn.IDADEMAE = atoi(linha[11]);
        dn.CONSULTAS = atoi(linha[12]);
        dn.PARTO = atoi(linha[13]);
        dn.STTRABPART = atoi(linha[14]);
        dn.KOTELCHUCK = atoi(linha[15]);
        dn.APGAR5 = atoi(linha[16]);
        dn.TPROBSON = atoi(linha[17]);
        acumula(tabela,hash(dn.CODMUNRES),(float)dn.PESO);
        lc++;
        if(lc==TEST_SIZE) {
            break;
        }
        fgets(buffer,MAX,f);
    }
    for (int i = 0; i < 31; i++) {
        HashElement *x = &tabela[i];
        while (x != NULL && x->qtd > 0) {
            processa(x);
            x = x->next;
        }
    }
    fclose(f);
    return 0;
}
