/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 10:01:48 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/04 13:30:46 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_nbr_car(char c)
{
	int i;

	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

void	write_string(char *s)
{
	int i;

	i = -1;
	while (s != NULL && s[++i])
		write(1, &s[i], 1);
}

int		pass_spe(char *line, int i)
{
	while (line[i] == ' ')
	{
		if (line[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

int		ft_puts(int d)
{
	return (write(1, &d, sizeof(int)));
}
