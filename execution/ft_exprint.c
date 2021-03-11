/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 10:21:48 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/11 11:34:35 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	alphacmp(char *str1, char *str2)
{
	int i;
	int j;

	j = -1;
	i = -1;
	while (str1[++i] && str2[++j])
		if (str1[i] != str2[j])
			return (str1[i] > str2[j]);
	return (0);
}

t_env	*ft_envcpy(t_env *cur)
{
	t_env *ncpy;

	ncpy = malloc(sizeof(*ncpy));
	ncpy = NULL;
	while (cur)
	{
		envaddelm(&ncpy, newenvelm(ft_strdup(cur->key),
					ft_strdup(cur->val)));
		cur = cur->next;
	}
	return (ncpy);
}

void	ft_envsort(t_env *envlst)
{
	t_env	*a;
	t_env	*b;
	char	*tmp;

	a = envlst;
	while (a)
	{
		b = a->next;
		while (b)
		{
			if (alphacmp(a->key, b->key))
			{
				tmp = a->key;
				a->key = b->key;
				b->key = tmp;
				tmp = a->val;
				a->val = b->val;
				b->val = tmp;
			}
			b = b->next;
		}
		a = a->next;
	}
}

short	ft_exprint(t_env *head)
{
	t_env	*lcpy;
	t_env	*lcpytmp;

	lcpy = ft_envcpy(head);
	lcpytmp = lcpy;
	ft_envsort(lcpy);
	while (lcpy)
	{
		ft_putstr("declare -x ", 0);
		ft_putstr(lcpy->key, 0);
		write(t_g.mystdout, "=\"", 2);
		ft_putstr(lcpy->val, 0);
		write(t_g.mystdout, "\"\n", 2);
		lcpy = lcpy->next;
	}
	while (lcpytmp)
	{
		free(lcpytmp->key);
		free(lcpytmp->val);
		lcpytmp = lcpytmp->next;
	}
	free(lcpytmp);
	return (0);
}
