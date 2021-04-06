/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:51:36 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/06 10:29:59 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	gestion_fill_arg(t_gargs *gargs, char *line, int len)
{
	t_gargs	*ptr_list_shell;
	int		i;

	i = 0;
	ptr_list_shell = gargs;
	t_params.args = (char **)malloc(sizeof(char *) * len + 1);
	while (ptr_list_shell != NULL)
	{
		len = ptr_list_shell->end - ptr_list_shell->start;
		t_params.args[i] = (char *)fill_arg(len,
				ptr_list_shell->start, line, ptr_list_shell->vld_der);
		ptr_list_shell = ptr_list_shell->next;
		i++;
	}
	t_params.args[i] = NULL;
}

int	get_start_and_end_args(char *lne, t_inputs **list_shell)
{
	int	i;
	int	start;
	int	pipe;

	i = -1;
	start = 0;
	while (1)
	{
		if ((lne[++i] == '\"' || lne[i] == '\'') && valid_option(lne, i) == 1)
			i = get_end_index(lne, i);
		else if (((lne[i] == ';' || lne[i] == '|')
				&& valid_option(lne, i) == 1) || lne[i] == '\0')
		{
			pipe = 0;
			if (lne[i] == '|')
				pipe = 1;
			if (get_param_list_shell(lne, start, i) == -1)
				return (-1);
			ft_lstadd_back(list_shell, ft_lstnew(t_params.args, pipe));
			if ((lne[i] == ';' && lne[i + 1] == '\0') || lne[i] == '\0')
				break ;
			start = i + 1;
		}
	}
	return (1);
}

int	get_end_arg(int start_arg, char *line, int end)
{
	int	i;

	i = 0;
	t_params.vld_der = 0;
	while (start_arg + i < end)
	{
		while (line[start_arg + i] == ' ' && start_arg + i < end)
			i++;
		if (valid_option(line, start_arg + i) == 1
			&& (line[start_arg + i] == '>' || line[start_arg + i] == '<'))
			return (greater_less(start_arg + i, line));
		else if (valid_option(line, start_arg + i) == 1
			&& line[start_arg + i] == '\"')
			return (cut_quotation(start_arg + i, line, end));
		else if (line[start_arg + i] == '\'')
			return (cut_apostrophe(start_arg + i, line, end));
		else
		{
			if (cut_outher(start_arg + i, line, end, &i) == 0)
				break ;
			continue ;
		}
	}
	return (start_arg + i);
}

int	gestion_args(char *line, int start, int end, t_gargs **gargs)
{
	int	i;
	int	start_arg;
	int	end_arg;

	i = 0;
	while (start + i < end && i >= 0)
	{
		while (line[start + i] == ' ' || line[start + i] == '\t')
			i++;
		if (start + i >= end)
			break ;
		start_arg = start + i;
		end_arg = get_end_arg(start_arg, line, end);
		if (end_arg == -1)
			return (-1);
		ft_lstadd_back_arg(gargs, ft_lstnew_args(start_arg,
				end_arg, t_params.vld_der));
		if (end_arg - start_arg == 0)
			i += 1;
		else
			i += end_arg - start_arg;
	}
	return (get_number_args(gargs));
}
