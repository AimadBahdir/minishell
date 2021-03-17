/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/17 08:47:11 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	ft_execmd(t_env **lst, char **cmdargs)
{
	char	*cmd;
	short	err;

	ft_setoldcmd(lst, cmdargs[0]);
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
	else if (ft_strcmp(cmd, "exit"))
		err = ft_exit(cmdargs);
	else
		err = ft_othercmd(lst, cmdargs);
	t_pipe.prev = 0;
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

short	ft_setprvpip(void)
{
	if ((t_pipe.prvo = dup(t_pipe.nxtio[0])) < 0)
		return (0);
	close(t_pipe.nxtio[0]);
	t_pipe.prev = 1;
	return (1);
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
			if (t_pipe.next && !ft_setprvpip())
				return (errthrow("dup: ",
						"prvo pipe dosn't dupplicated.", NULL, 1));
		}
		else
			t_g.exstat = 1;
		close(t_g.mystdin);
		close(t_g.mystdout);
		head = head->next;
	}
	return (0);
}
