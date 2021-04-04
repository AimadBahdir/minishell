/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/04 13:26:56 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**spltcmd(void)
{
	char	**args;
	short	i;
	short	stop;

	stop = chk_directions();
	if (!(args = malloc(sizeof(char *) * (stop + 1))))
		return (NULL);
	i = -1;
	while (++i < stop)
		args[i] = ft_strdup(t_g.cmd[i]);
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

	if (!(spltpath = ft_split(getenval(*lst, "PATH"), ':')))
		return (NULL);
	i = -1;
	cmdpath = ft_ternchar(*cmd == '\0', NULL, ft_strdup(cmd));
	while (spltpath[++i] && cmdpath != NULL)
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

int		chkprms(int err)
{
	if (err == 13)
		return(errthrow(strerror(err), NULL, NULL, 126));
	else if (err == 8)
		return (0);
	return (err);
}

short	ft_othercmd(t_env **lst)
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
		if (!ft_strcmp(t_g.cmd[0], "") && !(cmd = find_cmd(lst, t_g.cmd[0])))
			exit(errthrow(t_g.cmd[0], ": command not found", NULL, 127));
		if (execve(cmd, t_g.cmd, t_g.envp) == -1)
			exit(chkprms(errno));
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

short	ft_exit(void)
{
	int excod;

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
