/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 10:59:06 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/06 10:57:11 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	ft_setvar(t_env *envlst, char *spltd, char **newvar)
{
	char	*getedval;

	t_g.tmp = *newvar;
	if (spltd[0] == '?')
	{
		getedval = ft_itoa(t_g.exstat);
		*newvar = ft_strjoin(t_g.tmp, getedval);
		retfree(t_g.tmp, getedval, 0);
		t_g.tmp = *newvar;
		*newvar = ft_strjoin(t_g.tmp, (spltd + 1));
	}
	else if (spltd[0] == '_' || ft_isalpha(spltd[0]))
	{
		getedval = spltandgenv(envlst, spltd);
		if (getedval != NULL)
		{
			*newvar = ft_strjoin(t_g.tmp, getedval);
			free(getedval);
		}
		else
			*newvar = ft_strjoin(t_g.tmp, "");
	}
	else
		return (retfree(t_g.tmp, NULL, 0));
	return (retfree(t_g.tmp, NULL, 1));
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
	int		i;

	i = -1;
	ft_dupcmd(cmd);
	while (t_g.cmd[++i])
	{
		if (ft_checkfor(24, t_g.cmd[i]) != -1)
		{
			spltd = ft_split(t_g.cmd[i], 24);
			if (spltd != NULL)
			{
				if (!ft_chkambigs(envlst, &i, spltd))
					retfreetwo(spltd, 0);
				else
					return (retfreetwo(spltd, 1));
			}
		}
	}
	return (0);
}

void	ft_setoldpwd(t_env **e)
{
	t_g.pwd = getenval(*e, "PWD");
	t_g.oldpwd = getenval(*e, "OLDPWD");
	if (t_g.oldpwd == NULL && t_g.pwd != NULL)
	{
		envaddelm(e, newenvelm(ft_strdup("OLDPWD"), t_g.pwd));
		retfree(t_g.oldpwd, NULL, !(t_g.pwd = getenval(t_g.explst, "PWD")));
		t_g.oldpwd = getenval(t_g.explst, "OLDPWD");
		if (t_g.oldpwd == NULL)
			envaddelm(&t_g.explst, newenvelm(ft_strdup("OLDPWD"), t_g.pwd));
		else
			setenval(&t_g.explst, ft_strdup("OLDPWD"), t_g.pwd);
	}
	else if (t_g.pwd == NULL)
	{
		setenval(e, ft_strdup("OLDPWD"), ft_strdup(""));
		setenval(&t_g.explst, ft_strdup("OLDPWD"), ft_strdup(""));
	}
	else
	{
		setenval(e, ft_strdup("OLDPWD"), t_g.pwd);
		t_g.pwd = getenval(t_g.explst, "PWD");
		setenval(&t_g.explst, ft_strdup("OLDPWD"), t_g.pwd);
	}
	free(t_g.oldpwd);
}

short	ft_exit(void)
{
	int	excod;

	excod = t_g.exstat;
	if (!t_pipe.prev)
		ft_putstr("exit", 1);
	if (t_g.cmd[1])
	{
		if (ft_isnum(t_g.cmd[1]))
		{
			if (ft_lentwop(t_g.cmd) > 2)
			{
				return (errthrow("exit: ",
						"too many arguments", NULL, !t_pipe.next));
			}
			excod = ft_atoi(t_g.cmd[1]);
		}
		else
		{
			excod = errthrow("exit: ", t_g.cmd[1],
					": numeric argument required", 255);
		}
	}
	if (t_pipe.prev || t_pipe.next)
		return (0);
	exit(excod);
}
