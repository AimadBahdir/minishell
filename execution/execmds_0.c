/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/06 08:55:23 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*lowercmd(t_env **lst)
{
	char	*cmd;

	cmd = ft_strdup(t_g.cmd[0]);
	ft_setoldcmd(lst, cmd);
	ft_strlower(cmd);
	return (cmd);
}

short	ft_execmd(t_env **lst)
{
	char	*cmd;
	short	err;

	cmd = lowercmd(lst);
	if (ft_strcmp(cmd, "echo") > 0)
		err = ft_echo();
	else if (ft_strcmp(cmd, "cd") > 0)
		err = ft_cd(lst);
	else if (ft_strcmp(cmd, "pwd") > 0)
		err = ft_pwd(lst, 1);
	else if (ft_strcmp(cmd, "env") > 0)
		err = ft_env(*lst);
	else if (ft_strcmp(t_g.cmd[0], "export") > 0)
		err = ft_export(lst);
	else if (ft_strcmp(t_g.cmd[0], "unset") > 0)
		err = ft_unset(lst);
	else if (ft_strcmp(cmd, "exit") > 0)
		err = ft_exit();
	else
	{
		ft_resetenv(*lst);
		err = ft_othercmd(lst);
	}
	t_pipe.prev = 0;
	return (retfree(cmd, NULL, err));
}

short	ft_exchild(t_env **envlst)
{
	int	err;

	err = 0;
	err = ft_pipe();
	if (err > 0)
		return (err);
	if (chk_directions() != -1)
	{
		err = gdirections(envlst);
		if (err > 0)
			return (err);
	}
	else
	{
		err = ft_execmd(envlst);
		if (err > 0)
			return (err);
	}
	return (err);
}

short	ft_setprvpip(void)
{
	t_pipe.prvo = dup(t_pipe.nxtio[0]);
	if (t_pipe.prvo < 0)
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
			t_pipe.next = head->pipe;
			if (t_pipe.next == 1)
				if (pipe(t_pipe.nxtio) < 0)
					exit(errthrow(strerror(errno), NULL, NULL, 1));
			t_g.exstat = ft_exchild(envlst);
			if (t_pipe.next && !ft_setprvpip())
				return (errthrow("dup: ",
						"prvo pipe dosn't dupplicated.", NULL, 1));
		}
		else
			t_g.exstat = 1;
		ft_closestd();
		head = head->next;
	}
	return (0);
}
