#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main(void) {
    srand(time(NULL));
    int random;

    int fd1[2];
    int fd2[2];

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("pipe");
        exit(-1);
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(-2);
    }

    if (pid1 == 0) {
        close(fd1[1]);
        close(fd2[0]);

        int num;
        while (read(fd1[0], &num, sizeof(int)) > 0){
            if (num >= 50) {
                int n = num*num;
                write(fd2[1], &n, sizeof(int));
            }
        }
        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    }


    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(-2);
    }

    if (pid2 == 0) {
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[1]);

        int num;
        float somma = 0;
        int n = 0;
        int primo = 1;

        while (read(fd2[0], &num, sizeof(int)) > 0) {
            if (primo) {
                printf("%d", num);
                primo = 0;
            }
            else printf(" - %d", num);
            somma += (float)num;
            n++;
        }
        printf("\nMEDIA: %.2f\n", somma/(float)n);
        close(fd2[0]);
        exit(0);
    }

    close(fd1[0]);
    close(fd2[0]);
    close(fd2[1]);

    for(int i = 0; i < 20; i++) {
        int num = (rand() % 100)+1;
        write(fd1[1], &num, sizeof(int));
    }
    close(fd1[1]);
    wait(NULL);
    wait(NULL);
}
