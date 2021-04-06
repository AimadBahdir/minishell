/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 09:19:55 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/06 08:58:05 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	ft_isnum(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
		if (str[i] > '9' || str[i] < '0')
			return (0);
	return (1);
}

static int	getsize(long l, short sign)
{
	int	i;

	if ((l * sign) == 0)
		l = 1;
	else
		l = l * sign;
	i = 0;
	while (l)
	{
		l = l / 10;
		i++;
	}
	i += ft_ternint(sign == -1, 2, 1);
	return (i);
}

char	*ft_itoa(int n)
{
	long	l;
	int		i;
	char	*res;
	short	sign;

	sign = ft_ternint(n < 0, -1, 1);
	i = getsize(n, sign);
	res = malloc(i * sizeof(char));
	if (res == NULL)
		return (NULL);
	l = n;
	l = l * sign;
	res[--i] = '\0';
	while (--i >= 0 || l)
	{
		res[i] = ft_ternint(sign == -1 && i == 0, '-', l % 10 + '0');
		l = l / 10;
	}
	return (res);
}
