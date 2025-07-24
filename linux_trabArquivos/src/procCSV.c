#include <stdio.h>
#include <string.h>
int main() {

  FILE * f = fopen("data/nomes.csv", "r");
  char buf[4096];
  fgets(buf, 4096, f);
  while(!feof(f)) {

    char * x;
    char * t = strtok_r(buf, ";\n", &x);
    int time = 0;
    while(t) {
      int t2 = (time % 3);
      char category[9];
      switch(t2) {
        case 0:
          strcpy(category, "Nome");
          break;
        case 1:
          strcpy(category,"Endereco");
          break;
        case 2:
          strcpy(category, "Telefone");
        default: 
	  break;
      }
      printf("%s %s \n\n ", category, t);
      t = strtok_r(NULL, ";\n", &x);
      time++;
    }
    fgets(buf, 4096, f);
  }
}
