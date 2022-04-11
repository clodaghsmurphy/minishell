#include "../includes/minishell.h"

void	del_one(t_env **lst, t_env *to_del);
void	unset_variable(t_env **env, char *variable_name);

void	unset(t_env	**env, char **params)
{
	int	i;

	i = 1;
	if (params[i] == NULL)
		ft_putstr_fd("unset: not enough arguments\n", 1);
	else
	{
		while (params[i])
		{
			unset_variable(env, params[i]);
			i++;
		}
	}
}

void	unset_variable(t_env **env, char *variable_name)
{
	t_env	*current;
	t_env	*save;
	
	current = *env;
	while (current)
	{
		if (!ft_strncmp(current->name, variable_name, 2147483647))
		{
			del_one(env, current);
            //free(current);
			return ;
		}
		current = current->next;
	}
}
