#include "../includes/minishell.h"

t_redir_in	*parse_redir_in(char **command)
{
	t_redir_in	*lst;
	int			i;

	i = 0;
	lst = NULL;
	while (command[i])
	{
		if (!ft_strncmp(command[i], "<<", 3) && command[i + 1])
		{
			add_back_redir_in(&lst, command[i + 1], 1);
			command = command_clear_one_in(command);
			i = - 1;
		}
		else if (!ft_strncmp(command[i], "<", 2) && command[i + 1])
		{
			add_back_redir_in(&lst, command[i + 1], 0);
			command = command_clear_one_in(command);
			i = - 1;
		} 
		i++;
	}
	return (lst);
}

void	add_back_redir_in(t_redir_in **lst, char *file_name, int bol)
{
	t_redir_in *new;
	t_redir_in *current;

	new = malloc(sizeof(t_redir_in));
	new->name = ft_strdup(file_name);
	new->type = bol;
	new->next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

char	**command_clear_all_in(char **command)
{
	char	**new;
	int		i;
	int		j;
	int		found = 0;

	i = 0;
	while (command[i])
		i ++;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	j = 0;
	while (command[i])
	{
		if ((!ft_strncmp("<<", command[i], 3) || !ft_strncmp("<", command[i], 2)))
		{
			if (command[i + 1])
				i += 2;
		}
		else
		{
			new[j] = ft_strdup(command[i]);
			j++;
			i++;
		}
	}
	new[j] = 0;
	free_tab(command);
	return (new);
}

char	**command_clear_one_in(char **command)
{
	char	**new;
	int		i;
	int		j;
	int		found = 0;

	i = 0;
	while (command[i])
		i ++;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	j = 0;
	while (command[i])
	{
		if ((!ft_strncmp("<<", command[i], 3) || !ft_strncmp("<", command[i], 2)) && found == 0)
		{
			if (command[i + 1])
			{
				found = 1;
				i += 2;
			}
		}
		else
		{
			new[j] = ft_strdup(command[i]);
			j++;
			i++;
		}
	}
	new[j] = 0;
	return (new);
}