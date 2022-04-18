#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    int pid;
    int pipefd[2];
    char *str;

    str = malloc(1000);
    pipe(pipefd);
    pid = fork();
    if (pid == 0)
    {
        write(pipefd[1], "salut", 5);
    }
    else
    {
        read(pipefd[0], str, 1000);
        printf("recu : %s", str);
    }

}