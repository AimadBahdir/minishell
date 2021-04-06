/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listshell_tgargs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 10:10:29 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/06 10:25:28 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_gargs	*ft_lstnew_args(int start, int end, int vld_der)
{
	t_gargs	*nouveau;

	nouveau = malloc(sizeof(*nouveau));
	nouveau->start = start;
	nouveau->end = end;
	nouveau->vld_der = vld_der;
	nouveau->next = NULL;
	return (nouveau);
}

void	ft_lstadd_back_arg(t_gargs **list_shell, t_gargs *new)
{
	t_gargs	*ptr_list_shell;

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

int	get_number_args(t_gargs **gargs)
{
	t_gargs	*ptr_list_shell;
	int		x;

	x = 0;
	ptr_list_shell = *gargs;
	if (ptr_list_shell == NULL)
		return (0);
	else
	{
		while (ptr_list_shell != NULL)
		{
			ptr_list_shell = ptr_list_shell->next;
			x++;
		}
	}
	return (x);
}
