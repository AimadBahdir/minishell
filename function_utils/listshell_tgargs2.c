/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listshell_tgargs2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 10:10:46 by wben-sai          #+#    #+#             */
/*   Updated: 2021/03/12 10:26:38 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_position(t_gargs **gargs, int i)
{
	int		x;
	t_gargs	*ptr_list_shell;

	ptr_list_shell = *gargs;
	x = 0;
	while (x < i)
	{
		ptr_list_shell = ptr_list_shell->next;
		x++;
	}
	echonge_list_args(&ptr_list_shell);
}

void	echonge_list_args(t_gargs **lst)
{
	t_gargs	*temp1;
	t_gargs	*temp2;
	int		x;
	int		i;

	temp1 = *lst;
	temp2 = *lst;
	while (temp1)
	{
		while (temp2)
		{
			echonge(&temp1->start, &temp1->end, &temp2->start, &temp2->end);
			echongevld_der(&temp1->vld_der, &temp2->vld_der);
			temp2 = temp2->next;
		}
		temp2 = *lst;
		temp1 = temp1->next;
	}
}

void	echonge(int *start1, int *end1, int *start2, int *end2)
{
	int temp;

	temp = *start2;
	*start2 = *start1;
	*start1 = temp;
	temp = *end2;
	*end2 = *end1;
	*end1 = temp;
}

void	echongevld_der(int *vld_der, int *vld_der2)
{
	int temp;

	temp = *vld_der2;
	*vld_der2 = *vld_der;
	*vld_der = temp;
}
