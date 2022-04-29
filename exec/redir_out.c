#include "../includes/minishell.h"

void	add_back_redir_out(t_redir_out **lst, char *file_name, int	bol);
char	**command_clear_one(char **command);
char	**command_clear_all(char **command);
t_redir_out	*parse_redir_out(char **command);
void	free_tab(char **tab);


t_redir_out	*parse_redir_out(char **command)
{
	t_redir_out	*lst;
	int			i;

	i = 0;
	lst = NULL;
	while (command[i])
	{
		if (!ft_strncmp(command[i], ">>", 3) && command[i + 1])
		{
			add_back_redir_out(&lst, command[i + 1], 1);
			command = command_clear_one(command);
			i = - 1;
		}
		else if (!ft_strncmp(command[i], ">", 2) && command[i + 1])
		{
			add_back_redir_out(&lst, command[i + 1], 0);
			command = command_clear_one(command);
			i = - 1;
		} 
		i++;
	}
	return (lst);
}

void	add_back_redir_out(t_redir_out **lst, char *file_name, int	bol)
{
	t_redir_out *new;
	t_redir_out *current;

	new = malloc(sizeof(t_redir_out));
	new->name = ft_strdup(file_name);
	new->append = bol;
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

char	**command_clear_all_out(char **command)
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
		if ((!ft_strncmp(">>", command[i], 3) || !ft_strncmp(">", command[i], 2)))
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

char	**command_clear_one(char **command)
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
		if ((!ft_strncmp(">>", command[i], 3) || !ft_strncmp(">", command[i], 2)) && found == 0)
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
// void	free_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	if (tab == NULL)
// 	{
// 		return ;
// 	}
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }

// int main()
// {
// 	t_redir_out *lst;

// 	char **test = malloc(sizeof(char *) * 14);
	
// 	int i = 0;
// 	test[0] = ft_strdup("ls");
// 	test[1] = ft_strdup(">>");
// 	test[2] = ft_strdup("cacahuette");
// 	test[3] = ft_strdup(">");
// 	test[4] = ft_strdup("salut");
// 	test[5] = ft_strdup("la");
// 	test[6] = ft_strdup("bas");
// 	test[7] = ft_strdup("cacahuette");
// 	test[8] = ft_strdup("cacahuette");
// 	test[9] = ft_strdup(">>");
// 	test[10] = ft_strdup("croute");
// 	test[11] = ft_strdup("cacahuette");
// 	test[12] = ft_strdup(">");
// 	test[13] = ft_strdup("oui");
// 	test[14] = NULL;

// 	while (test[i])
// 		printf("%s\n", test[i++]);
// 	printf("____________________\n");
// 	lst = parse_redir_out(test);
// 	while (lst)
// 	{
// 		printf("%s ---- %d\n", lst->name, lst->append);
// 		lst = lst->next;
// 	}
// }