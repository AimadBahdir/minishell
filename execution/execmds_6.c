/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 10:59:06 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/19 12:31:06 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	ft_setvar(t_env *envlst, char *spltd, char **newvar)
{
	char	*tmp;
	char	*getedval;

	tmp = *newvar;
	if (spltd[0] == '?')
	{
		getedval = ft_itoa(t_g.exstat);
		*newvar = ft_strjoin(tmp, getedval);
		retfree(tmp, getedval, 0);
		tmp = *newvar;
		*newvar = ft_strjoin(tmp, (spltd + 1));
	}
	else if (spltd[0] == '_' || ft_isalpha(spltd[0]))
	{
		if ((getedval = spltandgenv(envlst, spltd)) != NULL)
		{
			*newvar = ft_strjoin(tmp, getedval);
			free(getedval);
		}
		else
			*newvar = ft_strjoin(tmp, "");
	}
	else
		return (retfree(tmp, NULL, 0));
	return (retfree(tmp, NULL, 1));
}

char	*ft_getvar(t_env *envlst, char **spltd, short first)
{
	char	*newvar;
	int		j;

	j = -1;
	if (first)
		newvar = ft_strdup("");
	else
		newvar = ft_strdup(spltd[++j]);
	while (spltd[++j])
		if (!ft_setvar(envlst, spltd[j], &newvar))
			return (NULL);
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
			if ((spltd = ft_split(cmd[i], 24)) != NULL)
			{
				tmp = cmd[i];
				if (!ft_chkambigs(envlst, cmd, i, spltd))
				{
					cmd[i] = ft_getvar(envlst, spltd, cmd[i][0] == 24);
					retfreetwo(spltd, retfree(tmp, NULL, 0));
				}
				else
					return (retfreetwo(spltd, 1));
			}
		}
	}
	return (0);
}

void	ft_setoldpwd(t_env **e)
{
	char *pwd;
	char *oldpwd;

	pwd = getenval(*e, "PWD");
	oldpwd = getenval(*e, "OLDPWD");
	if (oldpwd == NULL && pwd != NULL)
	{
		envaddelm(e, newenvelm(ft_strdup("OLDPWD"), pwd));
		pwd = getenval(t_g.explst, "PWD");
		envaddelm(&t_g.explst, newenvelm(ft_strdup("OLDPWD"), pwd));
	}
	else if (pwd == NULL)
	{
		setenval(e, "OLDPWD", ft_strdup(""));
		setenval(&t_g.explst, "OLDPWD", ft_strdup(""));
	}
	else
	{
		setenval(e, "OLDPWD", pwd);
		pwd = getenval(t_g.explst, "PWD");
		setenval(&t_g.explst, "OLDPWD", pwd);
	}
	free(oldpwd);
}
