/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkfor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 08:55:32 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/15 10:42:01 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	ft_checkfor(char c, char *str)
{
	int i;

	i = -1;
	if (str == NULL)
		return (-1);
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

short	ft_checkforstr(char *str, char **lst)
{
	int i;

	i = -1;
	if (!lst || !str)
		return (-1);
	while (lst[++i])
		if (ft_strcmp(str, lst[i]))
			return (1);
	return (0);
}

short	chk_directions(char **lst)
{
	int i;

	i = -1;
	if (!lst)
		return (-1);
	while (lst[++i])
		if (lst[i][0] == 14
			|| lst[i][0] == 15)
			return (i);
	return (-1);
}

int		ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z'));
}
