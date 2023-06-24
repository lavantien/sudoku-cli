#include <stdio.h>
#include <string.h>

void readLine(char *line, const int size);

int main(void) {
  for (int i = 0; i < 10; i++) {
    char temp[257];
    readLine(temp, 257);
    printf("%d:[%zu]:%s\n", i, strlen(temp), temp);
  }
}

void readLine(char *line, const int size) {
  fgets(line, size, stdin);
  line[strcspn(line, "\n")] = 0;
}
