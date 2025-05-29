#include <stdio.h>
#include <stdlib.h>

// (long *) transforma em um ponteiro para long
// * acessa o valor
static int compar(const void *a, const void *b) {
  long la = *(const long *)a;
  long lb = *(const long *)b;
  if (la < lb)
    return -1;
  else if (la > lb)
    return 1;
  else
    return 0;
}

int main() {
  long arr_1[1000];
  long arr_2[1000];
  FILE *fptr;

  fptr = fopen("input.txt", "r");
  if (!fptr) {
    return EXIT_FAILURE;
  }

  // 10 dos números, + 3 dos espaços entre os números, + 1 do \n (precisa
  // incluir para o próximo fgets já começar nos números da próxima linha), + 1
  // do \0 (requerido pelo fgets, ele vai colocar no final da lida)
  char str[15];
  char *end;
  size_t i = 0;
  // fgets vai ler linha por linha
  while (fgets(str, 15, fptr)) {
    // para caso o arquivo seja maior que 1000 linhas
    // nesse caso não vai ter mais espaço nos arrays
    if (i >= 1000)
      break;

    // pega as duas colunas
    long n1 = strtol(str, &end, 10);
    long n2 = strtol(end, NULL, 10);
    arr_1[i] = n1;
    arr_2[i] = n2;
    i++;
  }

  fclose(fptr);

  qsort(arr_1, 1000, sizeof(long), compar);
  qsort(arr_2, 1000, sizeof(long), compar);

  long result = 0;

  for (size_t j = 0; j < 1000; j++) {
    long distance = labs(arr_1[j] - arr_2[j]); // labs = long abs
    result += distance;
  }

  printf("%ld\n", result);

  return 0;
}
