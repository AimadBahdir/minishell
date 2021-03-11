/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/11 17:37:58 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_cmd(t_env **lst, char *cmd)
{
	char	*cmdpath;
	char	**spltpath;
	char	*tmp;
	int		fd;
	int		i;

	spltpath = ft_split(getenval(*lst, "PATH"), ':');
	i = -1;
	cmdpath = ft_strdup(cmd);
	if (ft_checkfor('/', cmd) == -1)
		cmd = ft_strjoin("/", cmd);
	while (spltpath[++i])
	{
		if ((fd = open(cmdpath, O_RDONLY)) > 0 || errno == EACCES)
		{
			close(fd);
			retfreetwo(spltpath, 0);
			return (cmdpath);
		}
		tmp = cmdpath;
		cmdpath = ft_strjoin(spltpath[i], cmd);
		free(tmp);
	}
	return (NULL);
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

short	ft_execmd(t_env **lst, char **cmdargs)
{
	char	*cmd;
	short	err;

	cmd = ft_strlower(cmdargs[0]);
	if (ft_strcmp(cmd, "echo"))
		err = ft_echo(cmdargs);
	else if (ft_strcmp(cmd, "cd"))
		err = ft_cd(lst, cmdargs);
	else if (ft_strcmp(cmd, "pwd"))
		err = ft_pwd(lst);
	else if (ft_strcmp(cmd, "env"))
		err = ft_env(*lst, cmdargs);
	else if (ft_strcmp(cmd, "export"))
		err = ft_export(lst, cmdargs);
	else if (ft_strcmp(cmd, "unset"))
		err = ft_unset(lst, cmdargs);
	else
		err = ft_othercmd(lst, cmdargs);
	return (err);
}

short	ft_exchild(t_env **envlst, char **cmd)
{
	int err;

	err = 0;
	if ((err = ft_pipe()) > 0)
		return (err);
	if (chk_directions(cmd) != -1)
	{
		if ((err = gdirections(envlst, cmd)) > 0)
			return (err);
	}
	else
	{
		if ((err = ft_execmd(envlst, cmd)) > 0)
			return (err);
	}
	return (err);
}

short	ft_execute(t_env **envlst, t_inputs *cmdlst)
{
	t_inputs	*head;

	head = cmdlst;
	t_pipe.prev = 0;
	while (head)
	{
		t_g.mystdout = dup(STDOUT_FILENO);
		t_g.mystdin = dup(STDIN_FILENO);
		if (!ft_setenvar(*envlst, head->command))
		{
			if ((t_pipe.next = head->pipe) == 1)
				if (pipe(t_pipe.nxtio) < 0)
					exit(errthrow(strerror(errno), NULL, NULL, 1));
			t_g.exstat = ft_exchild(envlst, head->command);
			t_pipe.prev = 0;
			if (t_pipe.next)
			{
				if ((t_pipe.prvo = dup(t_pipe.nxtio[0])) < 0)
					return (-1);
				close(t_pipe.nxtio[0]);
				t_pipe.prev = 1;
			}
		}
		else
			t_g.exstat = 1;
		ft_closefds();
		head = head->next;
	}
	return (1);
}
