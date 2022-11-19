// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "types.h"
#include "stat.h"
#include "user.h"

#define TICKETS_PROCESS_1 20
#define TICKETS_PROCESS_2 30
#define TICKETS_PROCESS_3 50
#define N_FIB 40

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
