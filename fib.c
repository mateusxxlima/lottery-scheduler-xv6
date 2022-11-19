#include "types.h"
#include "stat.h"
#include "user.h"
 
// Function to find the nth Fibonacci number
int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
 
int main() {
    int n = 40;
    printf(1, "F(%d) = %d\n", n, fib(n));
    return 0;
}