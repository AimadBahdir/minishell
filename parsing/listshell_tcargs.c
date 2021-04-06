/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listshell_tcargs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 10:08:12 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/06 10:25:06 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cargs	*ft_lstcargsnew(char c)
{
	t_cargs	*nouveau;

	nouveau = malloc(sizeof(*nouveau));
	nouveau->c = c;
	nouveau->next = NULL;
	return (nouveau);
}

void	ft_lstcargsadd_back(t_cargs **list_shell, t_cargs *new)
{
	t_cargs	*ptr_list_shell;

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

int	get_len_list(t_cargs *lst)
{
	t_cargs	*temp1;
	int		i;

	temp1 = lst;
	i = 0;
	while (temp1)
	{
		i++;
		temp1 = temp1->next;
	}
	return (i);
}
