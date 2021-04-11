/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_args3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:02:43 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/08 17:29:24 by wben-sai         ###   ########.fr       */
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

int	get_args(char *line, int start, int end, int norm)
{
	int		i;
	int		len;
	t_gargs	*gargs;
	t_gargs	*ptr_list_shell;

	gargs = NULL;
	i = 0;
	len = gestion_args(line, start, end, &gargs);
	if (len == -1)
		return (-1);
	check_more(gargs, line, len, norm);
	while (gargs != NULL)
	{
		ptr_list_shell = gargs;
		gargs = gargs->next;
		free(ptr_list_shell);
		ptr_list_shell = NULL;
	}
	return (1);
}

char	*fill_arg(int len, int start, char *line, int vldder)
{
	t_g.indx = -1;
	t_params.index = 0;
	if (len == 0)
		len++;
	t_params.s = (char *)malloc(sizeof(char ) * len + 1);
	while (len > ++t_g.indx)
	{
		if (vldder == 1 && line[start + t_g.indx] == '>')
		{
			t_params.s[t_params.index++] = 14;
			vldder = 0;
		}
		else if (vldder == 1 && line[start + t_g.indx] == '<')
			t_params.s[t_params.index++] = 15;
		else
			t_params.s[t_params.index++] = line[start + t_g.indx];
	}
	t_params.s[t_params.index] = '\0';
	t_params.temp = t_params.s;
	t_params.s = addchange(t_params.s);
	retfree(t_params.temp, NULL, 0);
	t_params.temp = t_params.s;
	t_params.s = checkpath(t_params.s);
	retfree(t_params.temp, NULL, 0);
	return (t_params.s);
}
