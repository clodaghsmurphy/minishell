#include "../includes/minishell.h"


void	free_redir_in(t_redir_in *lst)
{
	t_redir_in *temp;
	
	while (lst)
	{
		temp = lst;
		free(lst->name);
		lst = lst->next;
		free(temp);
	}
}

void	free_redir_out(t_redir_out *lst)
{
	t_redir_out *temp;
	
	while (lst)
	{
		temp = lst;
		free(lst->name);
		lst = lst->next;
		free(temp);
	}
}

void	free_mini(t_mshell *mini)
{
	free(mini->pipe_fd);
	free_command(&mini->command);
	env_free(mini->env);
	free(mini);
}