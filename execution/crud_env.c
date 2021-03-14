/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:06:22 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/14 11:29:05 by abahdir          ###   ########.fr       */
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
			e->val = val;
			free(tmp);
			tmp = NULL;
			break ;
		}
		e = e->next;
	}
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

char	*ft_getvar(t_env *envlst, char **spltd, short first)
{
	char	*newvar;
	char	*tmp;
	int		j;

	j = -1;
	if (first)
		newvar = ft_strdup("");
	else
		newvar = ft_strdup(spltd[++j]);
	while (spltd[++j])
	{
		tmp = newvar;
		if (spltd[j][0] == '?')
		{
			newvar = ft_strjoin(tmp, ft_itoa(t_g.exstat));
			free(tmp);
			tmp = newvar;
			newvar = ft_strjoin(tmp, (spltd[j] + 1));
		}
		else if (spltd[j][0] == '_' || ft_isalpha(spltd[j][0]))
			newvar = ft_strjoin(tmp, getenval(envlst, spltd[j]));
		else
			return (NULL);
		free(tmp);
	}
	return (newvar);
}

short	ft_setenvar(t_env *envlst, char **cmd)
{
	char	**spltd;
	char	*tmp;
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (ft_checkfor(24, cmd[i]) != -1)
		{
			if ((spltd = ft_split(cmd[i], 24)))
			{
				tmp = cmd[i];
				if (!ft_chkambigs(envlst, cmd, i, spltd))
				{
					cmd[i] = ft_getvar(envlst, spltd, cmd[i][0] == 24);
					retfreetwo(spltd, retfree(tmp, NULL, 0));
				}
				else
					return (retfreetwo(spltd, retfree(tmp, NULL, 1)));
			}
		}
	}
	ft_resetenv(envlst);
	return (0);
}
