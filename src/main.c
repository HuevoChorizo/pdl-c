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

  /* Básicamente recorre todo el bufer y copia los tokens a un nuevo bufer de
   * tokens, de esta forma  simplifica el trabajo del analizador, ya ha
   * preparado el texto, solo queda comprobar si el token es un token de verdad
   * o no.*/
  int i = 0;
  int j = 0;
  /* TODO: encontrar el tamaño del token, y de paso multiplicar por
   * sizeof(char*)*/
  int tamToken = 100;

  /* Habría que ver el tamaño máximo de token, dividir size entre este, y así
   * vas que chutas*/
  /* TODO: cambiar el 4 por el tamaño máximo del token (eventualmente)*/
  char **tokens = malloc(size / 4 * sizeof(char *));
  if (tokens == NULL) {
    printf("Error al reservar memoria para tokens\n");
    return 1;
  }

  while (buf[i] != '\0') {
    if (buf[i] == '<') {
      tokens[j] = malloc(tamToken * sizeof(char));
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
