#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int fd = open("TokensEntrada", O_RDONLY);
  if (fd == -1) {
    printf("Error al abrir el fichero");
    exit(1);
  }

  /*Aquí deberíamos implementar el lector directamente, hay que hacer un struct
   * que desarrolle las propiedades de los tokens (eventualmente xd ) */
  int size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  char buf[size];
  read(fd, buf, size);

  /*Prueba a escribirlo en otro fichero*/
  int fd2 = creat("Salida.txt", 0777);
  if (fd == -1) {
    printf("Error al crear el archivo de salida");
    exit(1);
  }
  write(fd2, buf, size);

  /* Sobre buf hay que aplicar strtok, para de esta manera dividir los tokens en
   * sus componentes <(lo que haya)>, strtok, básicamente nos permite crear
   * nuevos strings, se crean con un bucle simple, y luego analizar dichos
   * strings., también se puede arreglar comparando caracter a caractér,
   * probablemente nos de menos problemas */
  int i = 0;
  int j = 0;
  /* Habría que ver el tamaño máximo de token, dividir size entre este, y así
   * vas que chutas*/
  char **tokens = malloc(200 * sizeof(char *));
  if (tokens == NULL) {
    printf("Error al reservar memoria para tokens\n");
    return 1;
  }

  while (buf[i] != '\0') {
    if (buf[i] == '<') {
      tokens[j] = malloc(100 * sizeof(char));
      if (tokens[j] == NULL) {
        printf("Error al reservar memoria para un token\n");
        return 1;
      }

      int k = 0;
      while (buf[i] != '>' && buf[i] != '\0') {
        tokens[j][k] = buf[i];
        i++;
        k++;
      }
      tokens[j][k] = '\0';

      if (buf[i] == '>') {
        tokens[j][k] = '>';
        tokens[j][k + 1] = '\0';
        i++;
      }

      j++;
    } else {
      i++;
    }
  }

  tokens[j] = NULL;

  i = 0;
  while (tokens[i] != NULL) {
    printf("Token %d: %s\n", i + 1, tokens[i]);
    i++;
  }

  for (int i = 0; tokens[i] != NULL; i++) {
    free(tokens[i]);
  }
  free(tokens);

  if (close(fd) != 0 || close(fd2) != 0) {
    printf("El fichero se ha cerrado con un error.");
    return -1;
  }

  return 0;
}
