/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/02 10:56:50 by abahdir          ###   ########.fr       */
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
	int err;

	err = 0;
	if (t_g.mystdout != STDOUT_FILENO)
		if ((err = ft_duptwo(t_g.mystdout, STDOUT_FILENO)) > 0)
			return (err);
	if (t_g.mystdin != STDIN_FILENO)
		if ((err = ft_duptwo(t_g.mystdin, STDIN_FILENO)) > 0)
			return (err);
	if ((err = ft_execmd(envlst, cmd)) > 0)
		return (err);
	return (err);
}

int		ft_open(char *name, int flags, short out)
{
	if (out)
	{
		if (t_g.mystdout > 2)
			ft_stdrst(1);
		return (t_g.mystdout = open(name,  flags, 0644));
	}
	else
	{
		if (t_g.mystdin > 2)
			ft_stdrst(0);
		return (t_g.mystdin = open(name,  flags, 0644));
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
				return (errthrow(cmd[i], ": ", strerror(errno), errno));
		}
		else if (cmd[i][0] == 27 && cmd[i][1] == '>' && cmd[i][2] == '>')
		{
			if (ft_open(cmd[++i],  O_CREAT | O_RDWR | O_APPEND, 1) == -1)
				return (errthrow(cmd[i], ": ", strerror(errno), errno));
		}
		else if (cmd[i][0] == 27 && cmd[i][1] == '>')
		{
			if (ft_open(cmd[++i],  O_CREAT | O_RDWR | O_TRUNC, 1) == -1)
				return (errthrow(cmd[i], ": ", strerror(errno), errno));
		}
	}
	return ((cmd[0][0] == 27) ? 0 : fillfile(envlst, spltcmd(cmd)));
}
