#ifndef __ENDERECO__
#define __ENDERECO__

typedef struct _Endereco Endereco;

struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade [72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2]; // espaço + quebra de linha ao final de cada registro
};

#endif
