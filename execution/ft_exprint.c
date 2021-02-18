/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 10:21:48 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/18 11:28:27 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	alphacmp(char *str1, char *str2)
{
	int i;
	int s1;
	int s2;

	i = -1;
	s1 = 0;
	while (str1[++i])
		s1 += str1[i];
	i = -1;
	s2 = 0;
	while (str2[++i])
		s2 += str2[i];
	return (s1 > s2);
}

t_env	*ft_envcpy(t_env *cur)
{
	t_env *ncpy;

	ncpy = malloc(sizeof(*ncpy));
	ncpy = NULL;
	while (cur)
	{
		envaddelm(&ncpy, newenvelm(cur->key, cur->val));
		cur = cur->next;
	}
	return (ncpy);
}

void	ft_envsort(t_env **envlst)
{
	t_env	*a;
	t_env	*b;
	char	*tmp;

	a = *envlst;
	while (a)
	{
		b = a;
		while (b)
		{
			if (alphacmp(b->key, a->key))
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

	lcpy = ft_envcpy(head);
	ft_envsort(&lcpy);
	while (lcpy)
	{
		ft_putstr("declare -x ");
		ft_putstr(lcpy->key);
		write(1, "=\"", 2);
		ft_putstr(lcpy->val);
		write(1, "\"\n", 2);
		lcpy = lcpy->next;
	}
	while (lcpy)
	{
		free(lcpy->key);
		free(lcpy->val);
		lcpy = lcpy->next;
	}
	free(lcpy);
	return (1);
}
