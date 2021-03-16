/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:41:07 by wben-sai          #+#    #+#             */
/*   Updated: 2021/03/11 16:39:43 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		error_msg(void)
{
	t_params.error_text = "bash: syntax Error 2\n";
	return (-1);
}

int		get_end_index(char *line, int i)
{
	if (line[i] == '\"')
	{
		i++;
		while (1 && line[i] != '\0')
		{
			if (line[i] == '\"' && valid_option(line, i) == 1)
				return (i);
			i++;
		}
	}
	else if (line[i] == '\'')
	{
		i++;
		while (1 && line[i] != '\0')
		{
			if (line[i] == '\'')
				return (i);
			i++;
		}
	}
	return (-1);
}

int		check_syntax_redirection(char *line, int i)
{
	if (((line[i] == '>' && line[i + 1] == '>') && valid_option(line, i) == 1)
	|| ((line[i] == '<' && line[i + 1] == '<') && valid_option(line, i) == 1))
	{
		i = pass_spe(line, i + 2);
		if (line[i] == '|' || line[i] == ';'
		|| line[i] == '>' || line[i] == '<')
			return (-1);
		return (i - 1);
	}
	if (i + 1 == pass_spe(line, i + 1))
	{
		if (line[i + 1] == '|' || line[i + 1] == ';' || (line[i + 1] == '<'
		&& line[i] == '>') || (line[i + 1] == '>' && line[i] == '<'))
			return (-1);
	}
	else
	{
		i = pass_spe(line, i + 1);
		if (line[i] == '|' || line[i] == ';'
		|| line[i] == '<' || line[i] == '>')
			return (-1);
		i--;
	}
	return (i);
}

int		check_syntax_line(char *line, int i)
{
	if (line[0] == ';' || line[0] == '|')
		return (error_msg());
	if ((line[i] == '\'' || line[i] == '\"') && valid_option(line, i) == 1)
		i = get_end_index(line, i);
	if (i == -1)
		return (-1);
	if ((line[i] == '|' || line[i] == ';') && valid_option(line, i) == 1)
	{
		i = pass_spe(line, i + 1);
		if (line[i] == '|' || line[i] == ';')
			return (error_msg());
		i--;
	}
	else if ((line[i] == '>' || line[i] == '<') && valid_option(line, i) == 1)
	{
		if (line[i + 1] == '\0')
			return (error_msg());
		i = check_syntax_redirection(line, i);
		if (i == -1)
			return (error_msg());
	}
	else if (line[i] == '\\'
	&& valid_option(line, i) == 1 && line[i + 1] == '\0')
		return (error_msg());
	return (i);
}

int		check_syntax(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		i = check_syntax_line(line, i);
		if (i == -1)
			return (-1);
		i++;
	}
	return (1);
}
