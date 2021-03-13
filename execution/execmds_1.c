/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/13 15:51:04 by abahdir          ###   ########.fr       */
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

int		ft_open(char *name, int flags, short out)
{
	if (out)
	{
		if (t_g.mystdout > 2)
		{
			close(t_g.mystdout);
			t_g.mystdout = STDOUT_FILENO;
		}
		return (t_g.mystdout = open(name, flags, 0644));
	}
	else
	{
		if (t_g.mystdin > 2)
		{
			close(t_g.mystdin);
			t_g.mystdin = dup(STDIN_FILENO);
		}
		return (t_g.mystdin = open(name, flags, 0644));
	}
}

short	gdirections(t_env **envlst, char **cmd)
{
	short	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i][0] == 15 && ft_open(cmd[++i], O_RDWR, 0) == -1)
			return (errthrow(cmd[i], ": ", strerror(errno), 1));
		else if (cmd[i][0] == 14 && cmd[i][1] == '>' && ft_open(cmd[++i],
			O_CREAT | O_RDWR | O_APPEND, 1) == -1)
			return (errthrow(cmd[i], ": ", strerror(errno), 1));
		else if (cmd[i][0] == 14 && ft_open(cmd[++i],
			O_CREAT | O_RDWR | O_TRUNC, 1) == -1)
			return (errthrow(cmd[i], ": ", strerror(errno), 1));
	}
	if (cmd[0][0] == 14 || cmd[0][0] == 15)
		return (0);
	return (ft_execmd(envlst, spltcmd(cmd)));
}

short ft_isnum(char *str)
{
	int i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
		if (str[i] > '9' || str[i] < '0')
			return (0);
	return (1);
}

short	ft_exit(char **cmd)
{
	int excod;

	excod = t_g.exstat;
	if (cmd[1])
	{
		if (ft_isnum(cmd[1]))
		{
			if (ft_lentwop(cmd) > 2)
				return (errthrow("exit: ", "too many arguments", NULL, !t_pipe.next));
			excod = ft_atoi(cmd[1]);
		}
		else
		{
			ft_putstr("exit", 1);
			excod = errthrow("exit: ", cmd[1], ": numeric argument required", 255);
		}
	}
	ft_putstr("exit", 1);
	if (t_pipe.next)
		return (0);
	exit(excod);
	return (excod);
}
