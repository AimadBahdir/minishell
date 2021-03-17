/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:07:26 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/17 08:24:25 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	ft_chkopt(char **args, int *i)
{
	short	nl;
	int		j;

	*i = 0;
	nl = 1;
	while (args[++(*i)])
	{
		j = 0;
		if (args[*i][0] == '-')
		{
			while (args[*i][++j])
				if (args[*i][j] != 'n')
					break ;
			if (*i == 1)
				nl = !(!args[*i][j] && args[*i][j - 1] == 'n');
			if (args[*i][j] && args[*i][j] != 'n')
				break ;
		}
		else
			break ;
	}
	return (nl);
}

short	ft_echo(char **args)
{
	short	newline;
	int		i;

	if (!args[1])
		return (!(write(t_g.mystdout, "\n", 1)));
	newline = ft_chkopt(args, &i);
	while (args[i])
	{
		ft_putstr(args[i++], 0);
		if (args[i])
			write(t_g.mystdout, " ", 1);
	}
	if (newline)
		write(t_g.mystdout, "\n", 1);
	return (0);
}

char	*ft_rplchome(char *path)
{
	char *tmp;

	tmp = path;
	if (path == NULL)
		path = t_g.homepath;
	else if (path[0] == '~')
		path = ft_strjoin(t_g.homepath, (path + 1));
	return (path);
}

void	ft_setoldpwd(t_env **e)
{
	char *pwd;

	pwd = getenval(*e, "PWD");
	if (getenval(*e, "OLDPWD") == NULL)
	{
		envaddelm(e, newenvelm(ft_strdup("OLDPWD"), pwd));
		pwd = getenval(t_g.explst, "PWD");
		envaddelm(&t_g.explst, newenvelm(ft_strdup("OLDPWD"), pwd));
	}
	else
	{
		setenval(e, "OLDPWD", pwd);
		pwd = getenval(t_g.explst, "PWD");
		setenval(&t_g.explst, "OLDPWD", pwd);
	}
}

short	ft_cd(t_env **e, char **args)
{
	char *pwd;
	char *path;

	path = args[1];
	if (!path || path[0] == '~')
		path = ft_rplchome(path);
	else if (ft_strcmp(path, "-"))
	{
		if ((path = getenval(*e, "OLDPWD")) == NULL)
			return (errthrow("cd: ", "OLDPWD not set", NULL, 1));
		else
			ft_putstr(path, 1);
	}
	if (chdir(path) == -1)
		return (errthrow(path, ": cd: ", strerror(errno), errno));
	if (!(pwd = getcwd(NULL, 0)))
		return (errthrow("cd: ", "getcwd: ", strerror(errno), errno));
	ft_setoldpwd(e);
	if (getenval(*e, "PWD"))
		setenval(e, "PWD", pwd);
	return (0);
}

short	ft_pipe(void)
{
	int err;

	err = 0;
	if (t_pipe.next)
	{
		if ((t_g.mystdout = dup(t_pipe.nxtio[1])) == -1)
			err = 1;
		close(t_pipe.nxtio[1]);
	}
	if (t_pipe.prev)
	{
		if ((t_g.mystdin = dup(t_pipe.prvo)) == -1)
			err = 1;
		close(t_pipe.prvo);
	}
	return (err);
}
