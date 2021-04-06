/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:56:06 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/06 10:22:37 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	greater_less(int start_arg, char *line)
{
	t_params.vld_der = 1;
	if ((line[start_arg] == '>' && line[start_arg + 1] == '>')
		|| (line[start_arg] == '<' && line[start_arg + 1] == '<'))
	{
		return (start_arg + 2);
	}
	else if ((line[start_arg] == '>') || (line[start_arg] == '<'))
	{
		return (start_arg);
	}
	return (-1);
}

int	cut_quotation(int start, char *line, int end)
{
	start++;
	while (1)
	{
		if (line[start] == '\"' && valid_option(line, start) == 1)
			break ;
		start++;
	}
	start++;
	if (line[start] == '\0' || line[start] == ' ' || line[start] == '\t'
		|| line[start] == '<' || line[start] == '>' || start > end)
		return (start);
	else
	{
		while (line[start] != '\0' && line[start] != ' ' && line[start] != '\t'
			&& line[start] != '<' && line[start] != '>' && start < end)
		{
			if (line[start] == '\"' && valid_option(line, start) == 1)
				return (cut_quotation(start, line, end));
			else if (line[start] == '\'' && valid_option(line, start) == 1)
				return (cut_apostrophe(start, line, end));
			start++;
		}
		return (start);
	}
}

int	cut_apostrophe(int start, char *line, int end)
{
	int	i;

	i = 1;
	while (line[start + i] != '\'')
		i++;
	i++;
	if (line[start + i] == '\0' || line[start + i] == ' '
		|| line[start + i] == '\t' || line[start + i] == '<'
		|| line[start + i] == '>' || start + i > end)
		return (start + i);
	else
	{
		while (line[start + i] != '\0' && line[start + i] != ' '
			&& line[start + i] != '\t' && line[start + i] != '<'
			&& line[start + i] != '>' && start + i < end)
		{
			if (line[start + i] == '\'' && valid_option(line, start + i) == 1)
				return (cut_apostrophe(start + i, line, end));
			else if (line[start + i] == '\"'
				&& valid_option(line, start + i) == 1)
				return (cut_quotation(start + i, line, end));
			i++;
		}
		return (start + i);
	}
}

int	cut_outher(int start_arg, char *line, int end, int *i)
{
	while (start_arg + *i < end)
	{
		if ((line[start_arg + *i] == '>' || line[start_arg + *i] == '<')
			&& valid_option(line, start_arg + *i) == 1)
			return (0);
		else if ((line[start_arg + *i] == '\"' || line[start_arg + *i] == '\'')
			&& valid_option(line, start_arg + *i) == 1)
			return (1);
		else if ((line[start_arg + *i] == ' ' || line[start_arg + *i] == '\t')
			&& valid_option(line, start_arg + *i) == 1)
			return (0);
		*i = *i + 1;
	}
	return (0);
}
