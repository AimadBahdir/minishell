/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:49:18 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/06 12:10:16 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open(char *name, int flags, short out)
{
	int	file;

	file = open(name, flags, 0644);
	if (file == -1)
		return (0);
	if (out)
	{
		close(t_g.mystdout);
		t_g.mystdout = dup(file);
		close(file);
	}
	else
	{
		close(t_g.mystdin);
		t_g.mystdin = dup(file);
		close(file);
	}
	return (1);
}

short	ft_creatfiles(char **cmd, int stop)
{
	short	i;

	i = -1;
	while (cmd[++i] && (i < stop || stop == -1))
	{
		if (cmd[i][0] == 15 && ft_open(cmd[++i], O_RDWR, 0) == -1)
			return (errthrow(cmd[i], ": ", strerror(errno), 1));
		else if (cmd[i][0] == 14 && cmd[i][1] == '>' && ft_open(cmd[++i],
			O_CREAT | O_RDWR | O_APPEND, 1) == -1)
			return (errthrow(cmd[i], ": ", strerror(errno), 1));
		else if (cmd[i][0] == 14 && ft_open(cmd[++i],
			O_CREAT | O_RDWR | O_TRUNC, 1) == -1)
			return (errthrow(cmd[i], ": ", strerror(errno), 1));
	}
	return (0);
}

short	gdirections(t_env **envlst)
{
	int		err;
	char	**splt;

	err = ft_creatfiles(t_g.cmd, -1);
	if (err == 0)
	{
		if (t_g.cmd[0][0] == 14 || t_g.cmd[0][0] == 15)
			return (err);
		splt = spltcmd();
		if (splt != NULL)
		{
			if (ft_dupcmd(splt))
				err = ft_execmd(envlst);
			else
				err = 1;
			return (retfreetwo(splt, err));
		}
	}
	return (err);
}

short	ft_env(t_env *e)
{
	if (ft_lentwop(t_g.cmd) > 1)
	{
		return (errthrow("env: ", t_g.cmd[1],
				": No such file or directory", 127));
	}
	while (e)
	{
		ft_putstr(e->key, 0);
		write(t_g.mystdout, "=", 1);
		ft_putstr(e->val, 1);
		e = e->next;
	}
	return (0);
}

short	ft_pwd(t_env **e, short get)
{
	char	*path;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (errthrow(strerror(errno), NULL, NULL, errno));
	path = getenval(*e, "PWD");
	if (get)
		ft_putstr(pwd, 1);
	if (path != NULL)
	{
		setenval(e, ft_strdup("PWD"), ft_strdup(pwd));
		setenval(&t_g.explst, ft_strdup("PWD"), ft_strdup(pwd));
	}
	else if (!get)
	{
		envaddelm(e, newenvelm(ft_strdup("PWD"), ft_strdup(pwd)));
		envaddelm(&t_g.explst, newenvelm(ft_strdup("PWD"), ft_strdup(pwd)));
	}
	return (retfree(path, pwd, 0));
}
