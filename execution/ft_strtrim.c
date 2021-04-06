/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:43:40 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/06 10:34:59 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	getlen(const char *s1, const char *set, int start)
{
	int	i;
	int	j;

	i = ft_strlen(s1) + 1;
	if (i > start)
	{
		while (--i >= 0)
		{
			j = -1;
			while (set[++j])
				if (s1[i] == set[j])
					break ;
			if (s1[i] != set[j])
				break ;
		}
	}
	return ((i - start) + 1);
}

static int	getstart(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (s1[++i])
	{
		while (set[++j])
			if (s1[i] == set[j])
				break ;
		if (s1[i] != set[j])
			break ;
		j = -1;
	}
	return (i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int	start;
	int	len;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = getstart(s1, set);
	len = getlen(s1, set, start);
	return (ft_substr(s1, start, len));
}
