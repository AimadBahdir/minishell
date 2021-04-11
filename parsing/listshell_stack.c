/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listshell_stack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 11:31:52 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/08 17:28:23 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_stack	*ft_lststacknew(char *line, int i)
{
	t_stack	*nouveau;

	nouveau = malloc(sizeof(*nouveau));
	nouveau->line = line;
	nouveau->i = i;
	nouveau->next = NULL;
	return (nouveau);
}

void	ft_lststackadd_back(t_stack **list_shell, t_stack *new)
{
	t_stack	*ptr_list_shell;

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

int	get_len_list_stack(t_stack *lst)
{
	t_stack	*temp1;
	int		i;

	temp1 = lst;
	i = 0;
	while (temp1 != NULL)
	{
		i++;
		temp1 = temp1->next;
	}
	return (i);
}

void	lastnodedeletion(t_cargs **lst)
{
	t_cargs	*ptr_lst;
	t_cargs	*ptr_lst2;

	if (*lst == NULL)
		return ;
	else
	{
		ptr_lst = *lst;
		ptr_lst2 = *lst;
		while (ptr_lst->next != NULL)
		{
			ptr_lst2 = ptr_lst;
			ptr_lst = ptr_lst->next;
		}
		if (ptr_lst == *lst)
			*lst = NULL;
		else
			ptr_lst2->next = NULL;
		free(ptr_lst);
		ptr_lst = NULL;
	}
}

void	free_t_cargs(t_cargs **args)
{
	t_cargs	*ptr_args;
	t_cargs	*ptr_args2;

	ptr_args2 = *args;
	while (ptr_args2 != NULL)
	{
		ptr_args = ptr_args2;
		ptr_args2 = ptr_args2->next;
		free(ptr_args);
		ptr_args = NULL;
	}
	*args = NULL;
}
