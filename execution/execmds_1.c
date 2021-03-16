/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/16 15:06:43 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**spltcmd(char **cmd)
{
	char	**args;
	short	i;
	short	stop;

	stop = chk_directions(cmd);
	if (!(args = malloc(sizeof(char *) * (stop + 1))))
		return (NULL);
	i = -1;
	while (++i < stop)
		args[i] = cmd[i];
	args[stop] = NULL;
	return (args);
}

char	*ft_joinslash(char *cmdpath, char *path, char *cmd)
{
	char	*tmp;

	tmp = cmdpath;
	cmdpath = ft_strjoin(path, "/");
	free(tmp);
	tmp = cmdpath;
	cmdpath = ft_strjoin(cmdpath, cmd);
	free(tmp);
	return (cmdpath);
}

char	*find_cmd(t_env **lst, char *cmd)
{
	char	*cmdpath;
	char	**spltpath;
	int		fd;
	int		i;

	spltpath = ft_split(getenval(*lst, "PATH"), ':');
	i = -1;
	cmdpath = ft_strdup(cmd);
	while (spltpath[++i])
	{
		if ((fd = open(cmdpath, O_RDONLY)) > 0)
		{
			retfreetwo(spltpath, close(fd));
			if (ft_checkfor('/', cmdpath) != -1)
				return (cmdpath);
			else
			{
				free(cmdpath);
				return (NULL);
			}
		}
		cmdpath = ft_joinslash(cmdpath, spltpath[i], cmd);
	}
	return (ft_ternchar(ft_checkfor('/', cmd) != -1, cmd, NULL));
}

short	ft_othercmd(t_env **lst, char **cmdargs)
{
	int		pid;
	char	*cmd;
	int		exstat;

	if ((pid = fork()) < 0)
		return (errthrow("Error ", "in ", "forking", 1));
	if (pid == 0)
	{
		if (ft_duptwo(t_g.mystdout, STDOUT_FILENO) > 0
		|| ft_duptwo(t_g.mystdin, STDIN_FILENO) > 0)
			exit(1);
		if (!(cmd = find_cmd(lst, cmdargs[0])))
			exit(errthrow(cmdargs[0], ": command not found", NULL, 127));
		if (execve(cmd, cmdargs, t_g.envp) == -1)
			exit(errthrow(strerror(errno), NULL, NULL,
				errno));
		exit(retfree(cmd, NULL, 0));
	}
	else
	{
		wait(&exstat);
		if (WIFEXITED(exstat))
			return (WEXITSTATUS(exstat));
	}
	return (0);
}

short	ft_exit(char **cmd)
{
	int excod;

	excod = t_g.exstat;
	if (!t_pipe.prev)
		ft_putstr("exit", 1);
	if (cmd[1])
	{
		if (ft_isnum(cmd[1]))
		{
			if (ft_lentwop(cmd) > 2)
			{
				return (errthrow("exit: ",
						"too many arguments", NULL, !t_pipe.next));
			}
			excod = ft_atoi(cmd[1]);
		}
		else
		{
			excod = errthrow("exit: ", cmd[1],
					": numeric argument required", 255);
		}
	}
	if (t_pipe.prev || t_pipe.next)
		return (0);
	exit(excod);
}
