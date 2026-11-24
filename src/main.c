#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>

/* TODO: Mover defines de Error a error.h */
#define OK 0
#define ERROR_HILO 10
#define ERROR_PIPES 11
#define ERROR_FORK 12
/* TODO: Mover a tipos.h */
typedef struct {
  int in;
  int *out;
  void *fichIn;
  void *fichOut;
} threadArgs;

#define N_HILOS 4

int init_thread(pthread_attr_t *attr) {
  return pthread_attr_init(attr) != -1 &&
         pthread_attr_setdetachstate(attr, PTHREAD_CREATE_JOINABLE) != -1;
}

void kac(pthread_t *hilos) {
  int i;
  for (i = 0; i < N_HILOS; i++)
    pthread_cancel(hilos[i]);
}

int main(void) {
  pthread_t hilos[N_HILOS];
  pthread_attr_t atribts;
  int pipa1[2];
  int pipa2[2];
  int pipa3[2];
  pid_t pids[N_HILOS];
  threadArgs args[N_HILOS];
  void *(*functions[N_HILOS])(void *);
  /*PLACEHOLDERS*/
  char *fichero;
  void *hilo_lector;
  void *hilo_tokenizador;
  void *hilo_tablaSintactica;
  void *hilo_semantica;

  if (pipe(pipa1) == -1)
    return ERROR_PIPES;
  if (pipe(pipa2) == -1)
    return ERROR_PIPES;
  if (pipe(pipa3) == -1)
    return ERROR_PIPES;

  functions[0] = hilo_lector;
  functions[1] = hilo_tokenizador;
  functions[2] = hilo_tablaSintactica;
  functions[3] = hilo_semantica;

  args[0] = (threadArgs){-1, &pipa1[0], fichero, NULL};

  int outs[2] = {pipa2[0], pipa3[0]};

  args[1] = (threadArgs){pipa1[1], outs, NULL, NULL};
  args[2] = (threadArgs){pipa2[1], NULL, NULL, NULL};
  args[3] = (threadArgs){pipa3[1], NULL, NULL, NULL};

  if (!init_thread(&atribts))
    return ERROR_HILO;

  int i;
  for (i = 0; i < N_HILOS; i++) {
    pids[i] = fork();
    switch (pids[i]) {
    case -1:
      kac(hilos);
      return ERROR_FORK;
    case 0:

      if (pthread_create(&(hilos[0]), &atribts, functions[i],
                         (void *)&args[i]) == -1)
        return ERROR_HILO;

      void *aux;
      pthread_join(hilos[i], &aux);
      return *((int *)aux);
    default:
      break;
    }
  }
  pthread_attr_destroy(&atribts);
  int status;
  for (i = 0; i < N_HILOS; i++) {
    wait(&status);
    if (status != OK) {
      kac(hilos);
      return status;
    }
  }

  return OK;
}
