/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 09:19:55 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/11 09:30:51 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	getsize(long l, short sign)
{
	int i;

	l = ((l * sign) == 0) ? 1 : (l * sign);
	i = 0;
	while (l)
	{
		l = l / 10;
		i++;
	}
	i += (sign == -1) ? 2 : 1;
	return (i);
}

char		*ft_itoa(int n)
{
	long	l;
	int		i;
	char	*res;
	short	sign;

	sign = (n < 0) ? -1 : 1;
	i = getsize(n, sign);
	res = malloc(i * sizeof(char));
	if (res == NULL)
		return (NULL);
	l = n;
	l = l * sign;
	res[--i] = '\0';
	while (--i >= 0 || l)
	{
		res[i] = (sign == -1 && i == 0) ? '-' : l % 10 + '0';
		l = l / 10;
	}
	return (res);
}
