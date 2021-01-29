/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:59:14 by wben-sai          #+#    #+#             */
/*   Updated: 2021/01/25 14:59:52 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

t_inputs	*ft_lstnew(char *command, char *option, char **args, int pipe)
{
	t_inputs *nouveau;

	nouveau = malloc(sizeof(*nouveau));
    nouveau->command = command;
    nouveau->option = option;
    nouveau->args = args;
    nouveau->pipe = pipe;
	nouveau->next = NULL;
	return (nouveau);
}

t_gargs *ft_lstnew_args(int start ,int  end)
{
	t_gargs *nouveau;

	nouveau = malloc(sizeof(*nouveau));
    nouveau->start = start;
    nouveau->end = end;
	nouveau->next = NULL;
	return (nouveau);
}

void	ft_lstadd_back(t_inputs **list_shell, t_inputs *new)
{
	t_inputs *ptr_list_shell;

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

void	ft_lstadd_back_arg(t_gargs **list_shell, t_gargs *new)
{
	t_gargs *ptr_list_shell;

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
