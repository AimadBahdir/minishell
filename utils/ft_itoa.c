/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 10:48:23 by wben-sai          #+#    #+#             */
/*   Updated: 2021/02/10 10:48:46 by wben-sai         ###   ########.fr       */
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
