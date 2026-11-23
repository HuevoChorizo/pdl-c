#include "include/lector.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

char *p;

/*NOTE: devuelve la diferencia*/
/*NOTE: Tiene que copiar la funcionalidad del bucle de lector.*/
int func(int i, char *aux) {
  int j = 0;
  int k = 0;
  int s = 0;
  int cb = 0;

  return j;
}

int lectornuevo(char *ruta, char *palabra, int *pipe) {
  /*TODO: falta la gestión de la pipe, pero me da pereza*/
  struct stat bstat;

  int fd = open(ruta, O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "Error al abrir el fichero\n");
    return (LECT);
  }

  fstat(fd, &bstat);
  p = mmap(NULL, bstat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  /*TODO: comprobar la apertura del mapa correcta*/
  if (close(fd) != 0) {
    fprintf(stderr, "El fichero se ha cerrado con error\n");
    return (CRRDO);
  }

  char *aux;
  /*TODO: Igual aloco aux con un tam max de bstat.st_size, pero creo que sería
   * muy esquizo.
   * Igual no tiene mucho sentido, puesto que con el memcpy solo copio lo
   * necesario. pero weno, ya veremos*
   * */

  int i = 0;
  while (i < bstat.st_size) {

    int j = func(i, aux);
    memcpy(palabra, aux, j);
    /*NOTE: manda enteros de forma temporal, el formato aún no se ha definido.*/
    write(pipe[1], 0, sizeof(int));
    read(pipe[0], NULL, sizeof(int));
    i += j;
    /*TODO: mandar una señal EOF o algo para indicar que no espere más
     * palabras*/
  }
  free(aux);
  munmap(p, bstat.st_size);
  /*TODO: comprobar el correcto cierre del mapa*/

  return OK;
}
