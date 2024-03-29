/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:15:55 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/08 17:33:31 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	new_check(char **line2)
{
	if (line2[0][0] == '|' || line2[0][0] == ';'
		|| line2[0][0] == '>' || line2[0][0] == '<')
	{
		free(*line2);
		return (-1);
	}
	return (0);
}

int	lsh_read_line_and_trim(char **line, t_stack **stack)
{
	char	*temp;

	*line = get_line(stack);
	temp = *line;
	*line = ft_trim(*line);
	free(temp);
	return (0);
}

int	check_line(t_env **envlst, char **line, t_inputs **list_shell)
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
			exe_list(envlst, *list_shell);
		else
		{
			t_g.exstat = 258;
			write_string("minibash: syntax Error \n");
		}
		*list_shell = NULL;
	}
	return (0);
}
