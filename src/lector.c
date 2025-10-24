#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char **lector() {
  int fd = open("TokensEntrada", O_RDONLY);
  if (fd == -1) {
    printf("Error al abrir el fichero\n");
    exit(1);
  }

  /* Aquí deberíamos implementar el lector directamente, hay que hacer un struct
   * que desarrolle las propiedades de los tokens (eventualmente xd ) */
  int size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  char buf[size];
  read(fd, buf, size);

  /* Básicamente recorre todo el bufer y copia los tokens a un nuevo bufer de
   * tokens, de esta forma  simplifica el trabajo del analizador, ya ha
   * preparado el texto, solo queda comprobar si el token es un token de verdad
   * o no.*/

  /* TODO: encontrar el tamaño del token, y de paso multiplicar por
   * sizeof(char*) */
  int tamToken = 100;

  /* Habría que ver el tamaño máximo de token, dividir size entre este, y así
   * vas que chutas */
  /* TODO: cambiar el 4 por el tamaño máximo del token (eventualmente) */
  char **tokens = malloc(size / 4 * sizeof(char *));
  if (tokens == NULL) {
    printf("Error al reservar memoria para tokens\n");
    exit(1);
  }

  int i = 0, j = 0;
  while (buf[i] != '\0') {
    int cont = 0;
    int k = 0;
    if (i == 0 || buf[i - 1] == ' ' || buf[i - 1] == '\n') {
      tokens[j] = malloc(tamToken * sizeof(char));
      if (tokens[j] == NULL) {
        printf("Error al reservar la memoria de un token\n");
        exit(1);
      }
      k = 0;

      /* No tengo ni puta idea de como funciona esto, es mejor no preguntar,
       * porque estaba muy cocinado mientras lo hice, pero funciona. */

      while ((buf[i] != ' ' && buf[i] != '\n' && buf[i] != '\0') ||
             (cont != 0)) {
        if (i + 1 < size) {
          if (buf[i] == '"' || (buf[i] == '/' && buf[i + 1] == '*') ||
              ((cont % 2 != 0) && (buf[i] == '*' && buf[i + 1] == '/'))) {
            if (cont == 1)
              cont--;
            else
              cont++;
          }
        }

        tokens[j][k] = buf[i];
        i++;
        k++;
      }
      tokens[j][k] = '\0';
      j++;
    } else {
      i++;
    }
    if (buf[i] == '\n') {
      i++;
    }
  }

  /*No voy a hacer un caso específico para el último token, que aumente j otra
   * vez, sin embargo, como el último de verdad es j-2, j-1 tiene que ser
   * null.*/
  tokens[j - 1] = NULL;

  /*Esto es básicamente una comprobación de que funciona imprimiendolo, es por
   * ello temporal y eventualmente lo borraré.*/
  i = 0;
  while (tokens[i] != NULL) {
    printf("Token %d: %s\n", i + 1, tokens[i]);
    i++;
  }

  /*Cierra el fichero de entrada*/
  if (close(fd) != 0) {
    printf("El fichero se ha cerrado con un error.\n");
    exit(1);
  }

  return tokens;
}
