/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/26 12:13:39 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    **spltcmd(char **cmd)
{
	char    **args;
	short   i;
	short   stop;

	stop = -1;
	while (cmd[++stop])
		if (cmd[stop][0] == 27)
			break;
	if (!(args = malloc(sizeof(char *) * (stop + 1))))
		return (NULL);
	i = -1;
	while (++i < stop)
		args[i] = cmd[i];
	args[stop] = NULL;
	return (args);
}

int   fillfile(t_env **envlst, char **cmd)
{
	int pid;
	int file;
	int res;
	
	res = 1;
	pid = fork();
	if (pid == 0)
	{
		if (g_stdout != STDOUT_FILENO)
			ft_duptwo(g_stdout, STDOUT_FILENO);
		if (g_stdin != STDIN_FILENO)
			ft_duptwo(g_stdin, STDIN_FILENO);
		res = ft_execmd(envlst, cmd);
		exit(0);
	}
	return (res);
}

int		ft_open(char *name, int flags, short out)
{
	if (out)
	{
		if (g_stdout > 2)
			ft_stdrst(1);
		return (g_stdout = open(name,  flags, 0644));
	}
	else
	{
		if (g_stdin > 2)
			ft_stdrst(0);
		return (g_stdin = open(name,  flags, 0644));
	}
}

short   gdirections(t_env **envlst, char **cmd)
{
	short   i;
	i = -1;

	while (cmd[++i])
	{
		if (cmd[i][0] == 27 && cmd[i][1] == '<')
		{
			if (ft_open(cmd[++i],  O_RDWR, 0) == -1)
				return (errthrow(cmd[i], ": ", strerror(errno), NULL));
		}
		else if (cmd[i][0] == 27 && cmd[i][1] == '>' && cmd[i][2] == '>')
		{
			if (ft_open(cmd[++i],  O_CREAT | O_RDWR | O_APPEND, 1) == -1)
				return (errthrow(cmd[i], ": ", strerror(errno), NULL));
		}
		else if (cmd[i][0] == 27 && cmd[i][1] == '>')
		{
			if (ft_open(cmd[++i],  O_CREAT | O_RDWR | O_TRUNC, 1) == -1)
				return (errthrow(cmd[i], ": ", strerror(errno), NULL));
		}
	}
	return ((cmd[0][0] == 27) ? 0 : fillfile(envlst, spltcmd(cmd)));
}
