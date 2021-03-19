/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:07:26 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/19 12:30:56 by abahdir          ###   ########.fr       */
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
		path = ft_strdup(t_g.homepath);
	else if (path[0] == '~')
		path = ft_strjoin(t_g.homepath, (path + 1));
	free(tmp);
	return (path);
}

short	ft_cd(t_env **e, char **args)
{
	char *path;

	if (!args[1] || args[1][0] == '~')
		path = ft_rplchome(ft_strdup(args[1]));
	else if (args[1][0] == '\0')
		return (0);
	else if (ft_strcmp(args[1], "-"))
	{
		if ((path = getenval(*e, "OLDPWD")) == NULL)
			return (errthrow("cd: ", "OLDPWD not set", NULL, 1));
		else
			ft_putstr(path, 1);
	}
	else
		path = ft_strdup(args[1]);
	if (chdir(path) == -1)
	{
		retfree(path, NULL, 1);
		return (errthrow(path, ": cd: ", strerror(errno), 1));
	}
	ft_setoldpwd(e);
	ft_pwd(e, 0);
	return (retfree(path, NULL, 0));
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
