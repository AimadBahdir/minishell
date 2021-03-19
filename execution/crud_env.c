/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:06:22 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/19 11:50:39 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setenval(t_env **lst, char *key, char *val)
{
	t_env	*e;
	char	*tmp;

	e = *lst;
	while (e)
	{
		if (ft_strcmp(e->key, key))
		{
			tmp = e->val;
			e->val = ft_strdup(val);
			free(tmp);
			tmp = NULL;
			break ;
		}
		e = e->next;
	}
	retfree(val, NULL, 0);
}

char	*getenval(t_env *e, char *key)
{
	while (e)
	{
		if (ft_strcmp(e->key, key))
			return (ft_strtrim(e->val, " \t"));
		e = e->next;
	}
	return (NULL);
}

void	rmenval(t_env **lst, char *key)
{
	t_env *e;
	t_env *tmp;

	e = *lst;
	while (e)
	{
		if (ft_strcmp(e->key, key))
		{
			free(e->key);
			free(e->val);
			tmp->next = e->next;
			free(e);
			break ;
		}
		tmp = e;
		e = e->next;
	}
}
