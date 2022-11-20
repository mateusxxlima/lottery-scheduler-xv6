#include "types.h"
#include "stat.h"
#include "user.h"


//  Aqui é possível definir o número de tickets para cada processo filho, sendo que
//  cada processo executa a mesma função fibonacci que recebe um valor por parâmetro (N_FIB),
//  esse valor inicialmente é definido em 40, porém também pode ser ajustado.
//  Os valores definidos aqui devem estar no intervalo entre MIN_TICKETS e MAX_TICKETS(inclusive)
//###############################
#define TICKETS_PROCESS_1 3
#define TICKETS_PROCESS_2 2
#define TICKETS_PROCESS_3 1
#define N_FIB 40
//################################

void printf(int fd, const char *s, ...) {
  write(fd, s, strlen(s));
}

int fib(int n) {
  if (n <= 1) return n;
  return fib(n - 1) + fib(n - 2);
}

void forktest(void) {
  int n, pid;

  printf(1, "\nFork test iniciado\n");

  // Criando o primeiro processo
  pid = fork(TICKETS_PROCESS_1);
  if(pid == 0) {
    printf(1, "\n\nPrimeiro processo filho executando fibonacci!\n");
    fib(N_FIB);
    printf(1, "Primeiro processo filho terminou!\n");
    exit();
  }

  // Criando o segundo processo
  pid = fork(TICKETS_PROCESS_2);
  if(pid == 0) {
    printf(1, "Segundo processo filho executando fibonacci!\n");
    fib(N_FIB);
    printf(1, "Segundo processo filho terminou!\n");
    exit();
  }

  // Criando o terceiro processo
  pid = fork(TICKETS_PROCESS_3);
  if(pid == 0) {
    printf(1, "Terceiro processo filho executando fibonacci!\n\n");
    fib(N_FIB);
    printf(1, "Terceiro processo filho terminou!\n");
    exit();
  }


  n = 3;
  for(; n > 0; n--) {
    if(wait() < 0){
      printf(1, "wait stopped early\n");
      exit();
    }
  }

  if(wait() != -1) {
    printf(1, "wait got too many\n");
    exit();
  }

  printf(1, "\nFork test OK\n\n");
}

int main(void) {
  forktest();
  exit();
}
