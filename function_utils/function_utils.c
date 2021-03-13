/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 18:22:25 by wben-sai          #+#    #+#             */
/*   Updated: 2021/03/13 09:26:16 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	number_of_derc_in_table(char **s)
{
	int i;
	int j;
	int res;

	i = 0;
	res = 0;
	if (s != NULL)
	{
		while (s[i] != NULL)
		{
			j = 0;
			while(s[i][j] != '\0')
			{
				if(s[i][j] == 14 || s[i][j] == 15)
					res++;
				j++;
			}
			i++;
		}
	}
	return (res);
}

int	ft_isnumber(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	valid_option(char *line, int start)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (start > 0 && line[start - i] == '\\')
	{
		j++;
		i++;
	}
	if (j % 2 == 0)
		return (1);
	return (0);
}
