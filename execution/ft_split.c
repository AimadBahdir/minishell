/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:38:18 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/04 16:48:03 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		lenwords(char const *s, char c)
{
	int lenw;
	int i;

	i = 0;
	lenw = 0;
	if (!s)
		return (lenw);
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

static int		wordlen(char const *s, char c, int start)
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

static char		*getword(char const *s, char c, int *i, char **sp)
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

char			**ft_split(char const *s, char c)
{
	char	**sp;
	int		lw;

	if (!s)
		return (NULL);
	lw = lenwords(s, c);
	sp = malloc((lw + 1) * sizeof(char *));
	t_g.indx = 0;
	t_g.err = -1;
	while (s[t_g.indx])
	{
		while (s[t_g.indx] && s[t_g.indx] == c)
			t_g.indx++;
		if (t_g.indx == 0)
		{
			if ((sp[++t_g.err] = getword(s, c, &t_g.indx, sp)) == NULL)
				return (NULL);
		}
		else if (s[t_g.indx - 1] == c && s[t_g.indx] != c && s[t_g.indx])
			if ((sp[++t_g.err] = getword(s, c, &t_g.indx, sp)) == NULL)
				return (NULL);
		t_g.indx += ft_ternint(s[t_g.indx], 1, 0);
	}
	sp[++t_g.err] = 0;
	return (sp);
}
