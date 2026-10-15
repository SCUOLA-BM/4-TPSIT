#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

int main(void) {
    pid_t pid = fork();
    int n;

    if (pid <0) {
        perror("errore fork!!");
        exit(-1);
    }
    if (!pid) {
        scanf("INSERISCI UN NUMERO: %d", &n);

        for (int i = 2; i < sqrt(n); i++ )
        if (n % 2 == 0) return 1;
    }
    return 0;
}
