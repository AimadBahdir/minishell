/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:06:22 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/13 10:35:37 by abahdir          ###   ########.fr       */
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

char	*getnewelm(t_env *envlst, char **spltd, short first)
{
	char	*newelm;
	char	*tmp;
	int		j;

	j = -1;
	if (first)
		newelm = ft_strdup("");
	else
		newelm = ft_strdup(spltd[++j]);
	while (spltd[++j])
	{
		tmp = newelm;
		if (spltd[j][0] == '?')
		{
			newelm = ft_strjoin(tmp, ft_itoa(t_g.exstat));
			free(tmp);
			tmp = newelm;
			newelm = ft_strjoin(tmp, (spltd[j] + 1));
		}
		else if (spltd[j][0] == '_' || ft_isalpha(spltd[j][0]))
			newelm = ft_strjoin(tmp, getenval(envlst, spltd[j]));
		else
			return (NULL);
		free(tmp);
	}
	return (newelm);
}

short	ft_chkambigs(t_env *envlst, char *prvcmd, char **vars, int concat)
{
	char	*arg;
	char	*tmp;
	int		i;

	if ((i = (concat > 0)))
		arg = ft_strdup(vars[0]);
	else
		arg = ft_strdup("");
	if (prvcmd[0] == 14 || prvcmd[0] == 15)
	{
		while (vars[i])
		{
			tmp = arg;
			arg = ft_strjoin(arg, getenval(envlst, vars[i++]));
			free(tmp);
		}
		if (ft_checkfor(' ', arg) != -1 || arg[0] == '\0')
			return (errthrow("$", vars[(concat > 0)], ": ambiguous redirect", 
					retfree(arg, NULL, 1)));
	}
	return (retfree(arg, NULL, 0));
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
				if (!ft_chkambigs(envlst, cmd[i - 1], spltd, ft_lento(cmd[i], 24)))
				{
					cmd[i] = getnewelm(envlst, spltd, cmd[i][0] == 24);
					retfreetwo(spltd, retfree(tmp, NULL, 0));
				}
				else
					return (retfreetwo(spltd, retfree(tmp, NULL, 1)));
			}
		}
	}
	ft_resetenv(envlst);
	return(0);
}
