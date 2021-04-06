/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_args2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:09:08 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/06 15:08:30 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	}
	return (1);
}

int	len_dollar(char *s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && valid_option(s, i) == 1)
		{
			i++;
			while (s[i] != '\'')
				i++;
		}
		else if (s[i] == '$' && valid_option(s, i) == 1)
		{
			if (s[i + 1] == '$')
				i++;
			else if (ft_alpha(s[i + 1]) == 1 || s[i + 1] == '_')
				res++;
		}
		i++;
	}
	return (res);
}

int	exe_change(int i, char **ptr, char *s)
{
	if (s[i] == '\'' && valid_option(s, i) == 1)
	{
		ptr[0][t_params.index++] = s[i++];
		while (s[i] != '\'')
			ptr[0][t_params.index++] = s[i++];
		if (s[i] == '\'')
			ptr[0][t_params.index++] = s[i++];
	}
	else if (s[i] == '$' && valid_option(s, i) == 1)
	{
		ptr[0][t_params.index++] = s[i++];
		if (s[i] == '$')
			ptr[0][t_params.index++] = s[i++];
		else if (ft_alpha(s[i]) == 1 || s[i] == '_')
		{
			while (is_nbr_car(s[i]) == 1 || s[i] == '_')
				ptr[0][t_params.index++] = s[i++];
			ptr[0][t_params.index++] = 17;
		}
	}
	else
		ptr[0][t_params.index++] = s[i++];
	return (i);
}

char	*addchange(char *s)
{
	int		i;
	char	*ptr;
	int		len_dlr;

	i = 0;
	t_params.index = 0;
	len_dlr = len_dollar(s);
	ptr = malloc(sizeof(char) * (ft_strlen(s) + len_dlr + 1));
	while (s[i] != '\0')
		i = exe_change(i, &ptr, s);
	ptr[t_params.index] = '\0';
	return (ptr);
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
	free(t_params.temp);
	t_params.temp = t_params.s;
	t_params.s = checkpath(t_params.s);
	free(t_params.temp);
	return (t_params.s);
}
