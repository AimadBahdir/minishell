/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:01:48 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/06 10:34:36 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strlower(char *str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i] != '\0')
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
				str[i] += 32;
		}
	}
}
