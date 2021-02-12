/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:59:14 by wben-sai          #+#    #+#             */
/*   Updated: 2021/02/11 14:52:30 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cargs	*ft_lstcargsnew(char c)
{
	t_cargs *nouveau;

	nouveau = malloc(sizeof(*nouveau));
    nouveau->c = c;
	nouveau->next = NULL;
	return (nouveau);
}

void	ft_lstcargsadd_back(t_cargs **list_shell, t_cargs *new)
{
	t_cargs *ptr_list_shell;

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

t_inputs	*ft_lstnew(char **command, short pipe)
{
	t_inputs *nouveau;

	nouveau = malloc(sizeof(*nouveau));
    nouveau->command = command;
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

void	echonge_list_args(t_gargs **lst)
{
	t_gargs *temp1;
	t_gargs *temp2;
	int x;
	int i;

	temp1 = *lst;
	temp2 = *lst;
	while (temp1)
	{
		while (temp2)
		{
			echonge(&temp1->start, &temp1->end, &temp2->start, &temp2->end);
			temp2 = temp2->next;
		}
		temp2 = *lst;
		temp1 = temp1->next;
	}
}

int	get_len_list(t_cargs *lst)
{
	t_cargs *temp1;
	int i;

	temp1 = lst;
	i = 0;
	while (temp1)
	{
		i++;
		temp1 = temp1->next;
	}
	return(i);
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