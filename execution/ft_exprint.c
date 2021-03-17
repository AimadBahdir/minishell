/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 10:21:48 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/17 08:25:56 by abahdir          ###   ########.fr       */
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

short	ft_exprint(void)
{
	t_env	*lst;

	lst = t_g.explst;
	ft_envsort(lst);
	while (lst)
	{
		ft_putstr("declare -x ", 0);
		ft_putstr(lst->key, 0);
		if (lst->val[0] != 16)
		{
			write(t_g.mystdout, "=\"", 2);
			ft_putstr(lst->val, 0);
			write(t_g.mystdout, "\"\n", 2);
		}
		else
			write(t_g.mystdout, "\n", 2);
		lst = lst->next;
	}
	return (0);
}
