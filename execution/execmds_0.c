/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/06 18:00:41 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_cmd(t_env **lst, char *cmd)
{
	char	*cmdpath;
	char	**spltpath;
	char	*tmp;
	int		fd;
	int		i;

	spltpath = ft_split(getenval(*lst, "PATH"), ':');
	i = -1;
	cmdpath = ft_strdup("");
	cmd = ft_strjoin("/", cmd);
	while (spltpath[++i])
	{
		tmp = cmdpath;
		cmdpath = ft_strjoin(spltpath[i], cmd);
		free(tmp);
		if((fd = open(cmdpath, O_RDONLY)) > 0)
		{
			close(fd);
			retfreetwo(spltpath, 0);
			return (cmdpath);   
		}
	}
	return (NULL);
}

short   ft_othercmd(t_env **lst, char **cmdargs)
{
	int pid;
	char *cmd;

	pid = fork();
	if (pid < 0)
		return (errthrow("Error", "in", "Forking", 1));
	if (pid == 0)
	{
		if (!(cmd = find_cmd(lst, cmdargs[0])))
			exit(errthrow(cmdargs[0], ": command not found", NULL, 127));
		if (execve(cmd, cmdargs, t_g.envp) == -1)
			exit(errthrow(strerror(errno), NULL, NULL, errno));
		free(cmd);
		exit(0);
	}
	else
	{
		wait(&t_g.wstatus);
		if(WIFEXITED(t_g.wstatus))
			return (WEXITSTATUS(t_g.wstatus));
	}
	return (0);
}

short   ft_execmd(t_env **lst, char **cmdargs)
{
	char    *cmd;
	short   err;

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

short   chk_directions(char **lst)
{
	int i;

	i = -1;
	if (!lst)
		return (-1);
	while (lst[++i])
		if (lst[i][0] == 14
			|| lst[i][0] == 15)
			return (i);
	return (-1);
}

short   ft_exchild(t_env **envlst, char **cmd)
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
	close(t_pipe.envio[0]);
	write(t_pipe.envio[1], &envlst, sizeof(envlst));
	close(t_pipe.envio[1]);
	return (err);
}

short	ft_execute(t_env **envlst, t_inputs *cmdlst)
{
	t_inputs    *head;
	int         pid;

	head = cmdlst;
	t_pipe.prev = 0;
	while (head)
	{
		ft_setenvar(*envlst, head->command);
		if ((t_pipe.next = head->pipe) == 1)
			if (pipe(t_pipe.nxtio) < 0)
				exit(errthrow(strerror(errno), NULL, NULL, 1));
		if (pipe(t_pipe.envio) < 0)
			exit(errthrow(strerror(errno), NULL, NULL, 1));
		if ((pid = fork()) < 0)
			exit(errthrow(strerror(errno), NULL, NULL, 1));
		else if (pid == 0)
			exit(ft_exchild(envlst, head->command));
		else
		{
			wait(&t_g.wstatus);
			if(WIFEXITED(t_g.wstatus))
				t_g.exstat = WEXITSTATUS(t_g.wstatus);
			t_pipe.prev = 0;
			if (t_pipe.next)
			{
				if ((t_pipe.prvo = dup(t_pipe.nxtio[0])) < 0)
					return (-1);
				close(t_pipe.nxtio[0]);
				t_pipe.prev = 1;
			}
			close(t_pipe.envio[1]);
			read(t_pipe.envio[0], &envlst, sizeof(envlst));
			close(t_pipe.envio[0]);
		}
		head = head->next;
	}
	return (1);
}