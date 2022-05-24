#include "../includes/minishell.h"

void   ft_fork(char *str);


int main()
{
    int pid;
    char *str;

    str = malloc(15);
    ft_fork(str);
    printf("salut\n");
    free(str);
    exit (0);
}

void   ft_fork(char *str)
{
    int pid;

    pid = fork();
    if (pid == 0)
    {
        free(str);
        exit(0);
    }
    printf("salutdsfork\n");
    free(str);
    exit (0);
}