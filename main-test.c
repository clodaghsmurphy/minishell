#include "includes/minishell.h"
char	**env_to_tab(t_env *env)
{
	t_env	*current;
	char	**env_tab;
	int		i;

	current = env;
	env_tab = malloc(sizeof(char *) * (lst_env_size(env) + 1));
	i = 0;
	while (current)
	{
		env_tab[i++] = ft_strjoin_f(ft_strjoin(current->name, "="), current->value);
		current = current->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

int main(int ac, char **av, char **env)
{
    t_env   *tenv;

    tenv = parse_env(env);

    char **tab = env_to_tab(tenv);
    int i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}
