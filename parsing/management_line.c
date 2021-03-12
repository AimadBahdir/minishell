/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:15:55 by wben-sai          #+#    #+#             */
/*   Updated: 2021/03/12 10:33:11 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		new_check(char **line2)
{
	if (line2[0][0] == '|' || line2[0][0] == ';'
	|| line2[0][0] == '>' || line2[0][0] == '<')
	{
		free(*line2);
		return (-1);
	}
	return (0);
}

int		join_new_line_check_read_more(char **line, char **line2)
{
	char	*temp;
	int		len;

	temp = *line;
	*line = ft_strjoin(*line, *line2);
	free(temp);
	len = ft_strlen(*line2);
	if (line2[0][len - 1] != '|' && valid_option(*line2, len - 1) == 1)
	{
		free(*line2);
		return (1);
	}
	return (0);
}

int		read_more(char **line)
{
	int		len;
	char	*line2;

	len = ft_strlen(*line);
	if (check_syntax(*line) == -1)
		return (-1);
	if (line[0][len - 1] == '|' && valid_option(*line, len - 1) == 1)
	{
		while (1)
		{
			write_string("> ");
			if (lsh_read_line_and_trim(&line2) == -1)
				return (-1);
			if (new_check(&line2) == -1)
				return (-1);
			if (line2[0] != '\0')
				if (join_new_line_check_read_more(line, &line2) == 1)
					return (1);
			free(line2);
		}
	}
	return (1);
}

int		lsh_read_line_and_trim(char **line)
{
	char *temp;

	if (get_next_line(0, line) == -1)
		return (-1);
	temp = *line;
	*line = ft_trim(*line);
	free(temp);
	return (0);
}

int		check_line(char **line, t_inputs **list_shell)
{
	int	errors;

	errors = 0;
	if (check_syntax(*line) != -1)
		errors = lsh_split_line(*line, list_shell);
	else
	{
		write_string(t_params.error_text);
		free(*line);
		return (1);
	}
	if (errors == -1)
		write_string(t_params.error_text);
	else
	{
		if (check_syntax_list(*list_shell) != -1)
			exe_list(*list_shell);
		else
			write_string("bash: syntax Error 3\n");
		*list_shell = NULL;
	}
	return (0);
}
