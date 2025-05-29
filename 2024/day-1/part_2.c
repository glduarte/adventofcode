#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 100007
#define MAX_ENTRIES 1000

int main() {
  int table[TABLE_SIZE] = {};

  int aux_arr[MAX_ENTRIES];

  FILE *fpt;
  fpt = fopen("input.txt", "r");

  if (!fpt) {
    printf("file doesn't exist\n");
    return EXIT_FAILURE;
  }

  // char buffer[15];

  size_t i = 0;

  // char *end;

  int n1, n2;

  // Uma forma alternativa ao método de usar fgets + strtol
  // fscanf já vai procurar por dois números na linha
  // precisa verificar se == 2 porque o fscanf retorna quantos ponteiros ele
  // conseguiu ler/atribuir se os dois falharem, ou apenas um ou ambos, para de
  // executar o loop
  while (fscanf(fpt, "%d %d", &n1, &n2) == 2 && i < MAX_ENTRIES) {
    aux_arr[i] = n1;
    table[n2] += 1;
    i++;
  }

  fclose(fpt);

  int sum = 0;

  for (int k = 0; k < MAX_ENTRIES; k++) {
    if (table[aux_arr[k]] > 0) {
      sum += (aux_arr[k] * table[aux_arr[k]]);
    }
  }

  printf("%d\n", sum);
}
