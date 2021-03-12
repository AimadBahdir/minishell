/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:56:06 by wben-sai          #+#    #+#             */
/*   Updated: 2021/03/11 14:56:41 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		greater_less(int start_arg, char *line)
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

int		cut_quotation(int start, char *line, int end)
{
	int i;

	i = 1;
	while (1)
	{
		if (line[start + i] == '\"' && valid_option(line, start + i) == 1)
			break ;
		i++;
	}
	i++;
	if (line[start + i] == '\0' || line[start + i] == ' '
	|| line[start + i] == '<' || line[start + i] == '>' || start + i > end)
		return (start + i);
	else
	{
		while (line[start + i] != '\0' && line[start + i] != ' '
		&& line[start + i] != '<' && line[start + i] != '>' && start + i < end)
		{
			if (line[start + i] == '\"' && valid_option(line, start + i) == 1)
				return (cut_quotation(start + i, line, end));
			i++;
		}
		return (start + i);
	}
}

int		cut_apostrophe(int start, char *line, int end)
{
	int i;

	i = 1;
	while (line[start + i] != '\'')
	{
		if (start + i > end)
			return (-1);
		i++;
	}
	i++;
	if (line[start + i] == '\0' || line[start + i] == ' '
	|| line[start + i] == '<' || line[start + i] == '>' || start + i > end)
		return (start + i);
	else
	{
		while (line[start + i] != '\0' && line[start + i] != ' '
		&& line[start + i] != '<' && line[start + i] != '>' && start + i < end)
		{
			if (line[start + i] == '\'' && valid_option(line, start + i) == 1)
				return (cut_apostrophe(start + i, line, end));
			i++;
		}
		return (start + i);
	}
}

int		cut_outher(int start_arg, char *line, int end, int *i)
{
	while (start_arg + *i < end)
	{
		if ((line[start_arg + *i] == '>' || line[start_arg + *i] == '<')
		&& valid_option(line, start_arg + *i) == 1)
			return (0);
		else if ((line[start_arg + *i] == '\"' || line[start_arg + *i] == '\'')
		&& valid_option(line, start_arg + *i) == 1)
			return (1);
		else if (line[start_arg + *i] == ' '
		&& valid_option(line, start_arg + *i) == 1)
			return (0);
		*i = *i + 1;
	}
	return (0);
}
