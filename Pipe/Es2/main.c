#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //per il fork()
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h> // per mettere con toupper in maiuscolo

struct Messaggio {
    char str[100];
    int v;
};


int main(void) {
    int fd1[2];
    int fd2[2];

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("errore nel pipe");
        exit(-1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("errore nel fork");
        exit(-2);
    }

    if (pid > 0) { //padre

        close(fd1[0]);
        close(fd2[1]);
        char msg[100];
        printf("Insersci un messaggio : ");
        scanf("%99s", msg);

        write(fd1[1], msg, sizeof(msg));
        close(fd1[1]);


        struct Messaggio m;
        read(fd2[0], &m, sizeof(m));
        close(fd2[0]);

        wait(NULL);

        printf("Messaggio in maiuscolo : %s\n", m.str);
        printf("Numero di vocali: %d\n", m.v);


    } else { //figlio

        close(fd1[1]);
        close(fd2[0]);

        struct Messaggio m;
        m.v = 0;

        read(fd1[0], m.str, sizeof(m.str));
        close(fd1[0]);

        for (int i = 0; m.str[i] != '\0' ; i++) {
            m.str[i] = toupper(m.str[i]);
            if (m.str[i] == 'A' || m.str[i] == 'E' || m.str[i] == 'I' || m.str[i] == 'O' || m.str[i] == 'U') {
                m.v ++;
            }
        }
        write(fd2[1], &m, sizeof(m));
        close(fd2[1]);
        exit(0);
    }
    return 0;
}
