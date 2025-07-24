#include <string.h>
#include "endereco.h"
#ifndef __ENDERECO_UTILS__
#define __ENDERECO_UTILS__
int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int comparaIndice(const void *e1, const void *e2)
{
	return strncmp(((IndiceCEP*)e1)->cep,((IndiceCEP*)e2)->cep,8);
}
#endif
