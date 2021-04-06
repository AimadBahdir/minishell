/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listshell_tinputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:59:14 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/06 10:27:31 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_inputs	*ft_lstnew(char **command, short pipe)
{
	t_inputs	*nouveau;

	nouveau = malloc(sizeof(*nouveau));
	nouveau->command = command;
	nouveau->pipe = pipe;
	nouveau->next = NULL;
	return (nouveau);
}

int	check_syntax_list(t_inputs *list_shell)
{
	int			i;
	int			pipe;
	t_inputs	*ptr_list_shell;

	i = 0;
	ptr_list_shell = list_shell;
	while (ptr_list_shell != NULL)
	{
		pipe = ptr_list_shell->pipe;
		if (pipe == 1 && ptr_list_shell->command[0] == NULL)
			return (-1);
		ptr_list_shell = ptr_list_shell->next;
		if (ptr_list_shell != NULL && pipe == 1
			&& ptr_list_shell->command[0] == NULL)
			return (-1);
	}
	return (1);
}

void	ft_lstadd_back(t_inputs **list_shell, t_inputs *new)
{
	t_inputs	*ptr_list_shell;

	ptr_list_shell = *list_shell;
	if (*list_shell == NULL)
	{
		*list_shell = new;
		new->next = NULL;
	}
	else
	{
		while (ptr_list_shell->next)
			ptr_list_shell = ptr_list_shell->next;
		ptr_list_shell->next = new;
		new->next = NULL;
	}
}
