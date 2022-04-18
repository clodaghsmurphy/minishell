#include "minishell.h"
int	cmd_list_size(t_command *lst)
{
	t_command	*current;
	int			count;

	current = lst;
	count = 0;
	while (current)
	{
		current = current->next;
		count += 1;
	}
	return (count - 1);
}

int	cmd_lst_pos(t_command *lst, t_command *current)
{
	int			count;
	t_command	*temp;

	count = 1;
	temp = lst;
	while (temp && (temp != current))
	{
		temp = temp->next;
		count += 1;
	}
	if (temp == current)
		return (count);
	return (0);
}