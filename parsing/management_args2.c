/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_args2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:09:08 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/08 17:21:55 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cont_dollar_apostrophe(char *s, int *i, int *res)
{
	*i += 1;
	while (1)
	{
		if (s[*i] == '\"' && valid_option(s, *i) == 1)
			break ;
		else if (s[*i] == '$' && valid_option(s, *i) == 1)
		{
			if (s[*i + 1] == '$')
				*i += 1;
			else if (ft_alpha(s[*i + 1]) == 1 || s[*i + 1] == '_')
				*res += 1;
		}
		*i += 1;
	}
}

int	len_dollar(char *s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' && valid_option(s, i) == 1)
			cont_dollar_apostrophe(s, &i, &res);
		else if (s[i] == '\'' && valid_option(s, i) == 1)
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

int	exe_dollar_apostrophe(char **ptr, char *s, int i)
{
	ptr[0][t_params.index++] = s[i++];
	while (1)
	{
		if (s[i] == '\"' && valid_option(s, i) == 1)
		{
			ptr[0][t_params.index++] = s[i++];
			break ;
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
	}
	return (i);
}

int	exe_change(int i, char **ptr, char *s)
{
	if (s[i] == '\"' && valid_option(s, i) == 1)
		i = exe_dollar_apostrophe(ptr, s, i);
	else if (s[i] == '\'' && valid_option(s, i) == 1)
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
