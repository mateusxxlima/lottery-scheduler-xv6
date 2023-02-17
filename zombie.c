// Create a zombie process that
// must be reparented at exit.

#include "types.h"
#include "stat.h"
#include "user.h"

#define TICKETS_DEFAULT 10

int
main(void)
{
  if(fork(TICKETS_DEFAULT) > 0)
    sleep(5);  // Let child exit before parent.
  exit();
}
