#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *hosts = fopen("hosts.txt", "r");
  FILE *blacklist = fopen("blacklist.txt", "w");

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, hosts)) != -1) {
    if (line[0] == '#') continue;

    char *token = strtok(line, " ");
    if (strcmp(token, "0.0.0.0") == 0) {
      token = strtok(NULL, " ");

      char *hash = strchr(token, '#');
      if (hash != NULL) {
        *hash = '\0';
      }

      // Trim leading and trailing whitespace
      int i = 0;
      while (token[i] == ' ') i++;

      int j = strlen(token) - 1;
      while (j > 0 && token[j] == ' ') j--;
      token[j + 1] = '\0';

      fprintf(blacklist, "%s ", &token[i]);
    }
  }

  fclose(hosts);
  fclose(blacklist);
  free(line);

  return 0;
}
