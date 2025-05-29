#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT 6

const static char correct_input[INPUT] = "mul(,)";

int main() {
  FILE *file;

  file = fopen("input.txt", "r");
  if (!file) {
    return 1;
  }

  int result = 0;

  int correct_letters = 0;

  int nums_arr[2] = {};
  size_t nums_arr_index = 0;

  int file_character = fgetc(file);

  while (file_character != EOF) {
    while (file_character == correct_input[correct_letters]) {
      correct_letters++;
      file_character = fgetc(file);
    }
    if (correct_letters > INPUT - 1) {
      result += nums_arr[0] * nums_arr[1];
      correct_letters = 0;
    }
    while (isdigit(file_character)) {
      int number = 0;
      number = file_character - '0';
      file_character = fgetc(file);
      while (isdigit(file_character)) {
        number = number * 10 + (file_character - '0');
        // uma função interessante aqui seria o ungetc, que "devolveria" o
        // carácter que não é número. O ponteiro iria voltar uma casa.
        file_character = fgetc(file);
      }
      nums_arr[nums_arr_index] = number;
      nums_arr_index = (nums_arr_index + 1) % 2;
    }

    if (file_character != correct_input[correct_letters]) {
      file_character = fgetc(file);
      correct_letters = 0;
    }
  }

  fclose(file);
  printf("%d\n", result);
  return 0;
}
