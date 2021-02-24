/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:52:49 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/24 08:04:36 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		write(STDOUT_FILENO, (str + i), 1);
}

void	ft_putmstr(char **mstr, char spr)
{
	int i;

	i = -1;
	while (mstr[++i])
	{
		ft_putstr(mstr[i]);
		if (spr && mstr[i + 1])
			write(STDOUT_FILENO, &spr, 1);
	}
}

short	ft_strnormed(char *str)
{
	short i;

	i = -1;
	if (str[0] >= '0' && str[0] <= '9')
		return (0);
	while (str[++i])
	{
		if (!(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= 'A' && str[i] <= 'Z')
			&& !(str[i] >= '0' && str[i] <= '9')
			&& str[i] != '_')
			return (0);
	}
	return (1);
}
