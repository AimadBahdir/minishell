/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:16:06 by wben-sai          #+#    #+#             */
/*   Updated: 2021/01/11 18:23:07 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int		lenwords(char const *s, char c)
{
	int lenw;
	int i;

	i = 0;
	lenw = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (i == 0)
			lenw++;
		else if (s[i - 1] == c && s[i] != c && s[i])
			lenw++;
		if (s[i])
			i++;
	}
	return (lenw);
}

int		wordlen(char const *s, char c, int start)
{
	int len;

	len = 0;
	while (s[start] != c && s[start] != '\0')
	{
		len++;
		start++;
	}
	return (len);
}

char	*getword(char const *s, char c, int *i, char **sp)
{
	int		wlen;
	char	*ns;
	int		j;

	wlen = wordlen(s, c, *i);
	j = -1;
	if ((ns = malloc(wlen * sizeof(char) + 1)) == NULL)
	{
		while (sp[++j])
			free(sp[j]);
		free(sp);
		return (NULL);
	}
	while (s[*i] != c && s[*i])
	{
		ns[++j] = s[*i];
		*i += 1;
	}
	ns[++j] = '\0';
	return (ns);
}

char	**ft_split(char *s, char c)
{
	char	**sp;
	int		lw;
	int		i;
	int		j;

	lw = lenwords(s, c) + 1;
	sp = malloc(lw * sizeof(char *));
	i = 0;
	j = -1;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (i == 0)
		{
			if ((sp[++j] = getword(s, c, &i, sp)) == NULL)
				return (NULL);
		}
		else if (s[i - 1] == c && s[i] != c && s[i])
			if ((sp[++j] = getword(s, c, &i, sp)) == NULL)
				return (NULL);
		i += (s[i]) ? 1 : 0;
	}
	sp[++j] = 0;
	return (sp);
}
