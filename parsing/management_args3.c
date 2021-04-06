/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_args3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:02:43 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/06 15:03:06 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_more(t_gargs *gargs, char *line, int len, int norm)
{
	int	i;
	int	j;

	i = 0;
	gestion_fill_arg(gargs, line, len);
	j = number_of_derc_in_table(t_params.args);
	if (norm == 1)
	{
		j--;
		echonge_list_args(&gargs);
		free_table_args();
		gestion_fill_arg(gargs, line, len);
	}
	while (j > 0)
	{
		if (t_params.args[i][0] == 14 || t_params.args[i][0] == 15)
		{
			change_position(&gargs, i);
			free_table_args();
			gestion_fill_arg(gargs, line, len);
			j--;
			continue ;
		}
		i++;
	}
}

int	lsh_split_line(char *line, t_inputs **list_shell)
{
	if (get_start_and_end_args(line, list_shell) == -1)
		return (-1);
	return (1);
}

int	get_param_list_shell(char *line, int start, int end)
{
	int	i;

	i = 0;
	while (line[start + i] == ' ')
		i++;
	if (line[start + i] != '>' && line[start + i] != '<')
	{
		if (get_args(line, start, end, 0) == -1)
			return (-1);
	}
	else
	{
		if (get_args(line, start, end, 1) == -1)
			return (-1);
	}
	return (1);
}
