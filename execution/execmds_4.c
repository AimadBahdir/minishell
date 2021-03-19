/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 09:46:48 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/19 12:20:32 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_open(char *name, int flags, short out)
{
	int file;

	if ((file = open(name, flags, 0644)) == -1)
		return (0);
	if (out)
	{
		close(t_g.mystdout);
		t_g.mystdout = dup(file);
		close(file);
	}
	else
	{
		close(t_g.mystdin);
		t_g.mystdin = dup(file);
		close(file);
	}
	return (1);
}

short	ft_creatfiles(char **cmd, int stop)
{
	short	i;

	i = -1;
	while (cmd[++i] && (i < stop || stop == -1))
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
	return (0);
}

char	*spltandgenv(t_env *envlst, char *cmd)
{
	char	*key;
	char	*suit;
	char	*res;
	char	*val;
	int		stop;

	if ((stop = ft_strnormed(cmd)) == -1)
	{
		key = ft_strdup(cmd);
		suit = ft_strdup("");
	}
	else
	{
		key = ft_substr(cmd, 0, stop);
		suit = ft_substr(cmd, stop, (ft_strlen(cmd) - stop));
	}
	if (!(val = getenval(envlst, key)))
		val = ft_strdup("");
	res = ft_strjoin(val, suit);
	free(key);
	free(val);
	free(suit);
	return (res);
}

short	ft_chkambigs(t_env *envlst, char **cmd, int pos, char **vars)
{
	char	*arg;
	char	*tmp;
	int		i;

	if ((i = (ft_lento(cmd[pos], 24) > 0)))
		arg = ft_strdup(vars[0]);
	else
		arg = ft_strdup("");
	if (pos > 0 && (cmd[pos - 1][0] == 14 || cmd[pos - 1][0] == 15))
	{
		while (vars[i])
		{
			tmp = arg;
			arg = ft_strjoin(arg, spltandgenv(envlst, vars[i++]));
			free(tmp);
		}
		if (ft_checkfor(' ', arg) != -1 || (arg != NULL && *arg == '\0'))
		{
			i = ft_creatfiles(cmd, pos - 1);
			return (ft_ternint(i == 0, errthrow("$",
					vars[(ft_lento(cmd[pos], 24) > 0)],
					": ambiguous redirect", retfree(arg, NULL, 1)), i));
		}
	}
	return (retfree(arg, NULL, 0));
}

short	gdirections(t_env **envlst, char **cmd)
{
	int		err;
	char	**splt;

	if ((err = ft_creatfiles(cmd, -1)) == 0)
	{
		if (cmd[0][0] == 14 || cmd[0][0] == 15)
			return (err);
		if ((splt = spltcmd(cmd)) != NULL)
		{
			err = ft_execmd(envlst, splt);
			return (retfreetwo(splt, err));
		}
	}
	return (err);
}
