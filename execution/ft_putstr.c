/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:52:49 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/06 08:59:23 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *str, short nl)
{
	int	i;

	i = -1;
	while (str[++i])
		write(t_g.mystdout, (str + i), 1);
	if (nl)
		write(t_g.mystdout, "\n", 1);
}

void	ft_putmstr(char **mstr, char spr)
{
	int	i;

	i = -1;
	while (mstr[++i])
	{
		ft_putstr(mstr[i], 0);
		if (spr && mstr[i + 1])
			write(t_g.mystdout, &spr, 1);
	}
}

short	ft_strnormed(char *str)
{
	short	i;

	i = -1;
	if (str[0] >= '0' && str[0] <= '9')
		return (0);
	while (str[++i])
	{
		if (!(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= 'A' && str[i] <= 'Z')
			&& !(str[i] >= '0' && str[i] <= '9')
			&& str[i] != '_')
			return (i);
	}
	return (-1);
}
