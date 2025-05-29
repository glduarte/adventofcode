#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 25

int main() {
  FILE *fp;
  fp = fopen("input.txt", "r");
  if (!fp) {
    return 1;
  }

  char buffer[MAX_LINE_LENGTH];
  int safe_reports = 0;

  while (fgets(buffer, MAX_LINE_LENGTH, fp)) {
    char *cursor = buffer;
    char *next;

    long previous = strtol(cursor, &next, 10);
    if (cursor == next)
      continue;

    cursor = next;

    // boolean variable to keep if is increasing or decreasing
    int increasing = 0;
    // boolean variable to keep if the row is valid or not
    int is_safe = 1;
    int i = 1;

    int tolerated = 0;

    while (1) {
      long current = strtol(cursor, &next, 10);

      // "If there were no digits at all, strtol()  stores  the
      // original value of nptr (cursor) in *endptr (end) (and returns 0)"
      // via man strtol

      // i.e. there is nothing more to read
      if (cursor == next)
        break;

      long diff = current - previous;

      if (diff == 0 || labs(diff) > 3) {
        if (tolerated) {
          is_safe = 0;
          break;
        }
        tolerated++;
      }

      if (i == 1) {
        increasing = diff > 0;
      } else {
        if ((increasing && diff < 0) || (!increasing && diff > 0)) {
          if (tolerated) {
            is_safe = 0;
            break;
          }
          tolerated++;
        }
      }

      previous = current;
      cursor = next;
      i++;
    }

    if (is_safe) {
      safe_reports++;
    }
  }

  fclose(fp);
  printf("%d\n", safe_reports);

  return 0;
}
