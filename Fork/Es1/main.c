#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t r = fork();

    if (r == -1) {
        perror("ERRORE FORK");
    }
    if (!r) {
        printf("\nFIGLIO(1-5): ");
        for (int i = 1; i<=5; i++) {
            printf("\n%d",i);
        }
        exit(0);
    }
    wait(NULL);
    printf("\nPADRE(6-10): ");
    for (int i = 6; i<=10; i++) {
        printf("\n%d",i);
    }

    return 0;
}
