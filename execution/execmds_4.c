/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 09:46:48 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/04 13:27:07 by abahdir          ###   ########.fr       */
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

void	ft_rplcmd(char *arg, int pos)
{
	char	**oldarg;
	char	**argsplt;
	int		len;
	int		i;
	int		j;

	oldarg = t_g.cmd;
	argsplt = ft_split(arg, ' ');
	len = ft_lentwop(t_g.cmd) + ft_lentwop(argsplt);
	t_g.cmd = malloc(len * sizeof(char *));
	free(oldarg);
	i = -1;
	j = -1;
	while (oldarg[++j] && ++i < pos)
		t_g.cmd[i] = ft_strdup(oldarg[j]);
	j = -1;
	while (argsplt[++j])
		t_g.cmd[i++] = ft_strdup(argsplt[j]);
	j = pos;
	while (oldarg[++j])
		t_g.cmd[i++] = ft_strdup(oldarg[j]);
	t_g.cmd[i] = 0;
	// retfreetwo(oldarg, 0);
}

short	ft_chkambigs(t_env *envlst, int pos, char **vars)
{
	char	*arg;
	char	*tmp;
	int		i;

	if ((i = (ft_lento(t_g.cmd[pos], 24) > 0)))
		arg = ft_strdup(vars[0]);
	else
		arg = ft_strdup("");
	while (vars[i])
	{
		tmp = arg;
		arg = ft_strjoin(arg, spltandgenv(envlst, vars[i++]));
		free(tmp);
	}
	if (ft_checkfor(' ', arg) != -1)
	{
		if (pos > 0 && (t_g.cmd[pos - 1][0] == 14 || t_g.cmd[pos - 1][0] == 15))
		{
			i = ft_creatfiles(t_g.cmd, pos - 1);
			return (ft_ternint(i == 0, errthrow("$",vars[(ft_lento(t_g.cmd[pos],
				24) > 0)], ": ambiguous redirect", retfree(arg, NULL, 1)), i));
		}
		else
			ft_rplcmd(arg, pos);
	}
	else
	{
		tmp = t_g.cmd[pos];
		t_g.cmd[pos] = ft_strdup(arg);
		return (retfree(arg, tmp, 0));
	}
	return (retfree(arg, NULL, 0));
}

short	gdirections(t_env **envlst)
{
	int		err;
	char	**splt;

	if ((err = ft_creatfiles(t_g.cmd, -1)) == 0)
	{
		if (t_g.cmd[0][0] == 14 || t_g.cmd[0][0] == 15)
			return (err);
		if ((splt = spltcmd()) != NULL)
		{
			if (ft_dupcmd(splt))
				err = ft_execmd(envlst);
			else
				err = 1;
			return (retfreetwo(splt, err));
		}
	}
	return (err);
}
