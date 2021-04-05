/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 09:46:48 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/05 11:38:15 by abahdir          ###   ########.fr       */
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
}

short	ft_chkambigs(t_env *envlst, int pos, char **vars)
{
	char	*arg;
	char	*tmp;

	t_g.err = 0;
	arg = ft_getvar(envlst, vars, t_g.cmd[pos][0] == 24);
	if (ft_checkfor(' ', (tmp = ft_strtrim(arg, "\t "))) != -1)
	{
		if (pos > 0 && (t_g.cmd[pos - 1][0] == 14 || t_g.cmd[pos - 1][0] == 15))
		{
			t_g.err = ft_creatfiles(t_g.cmd, pos - 1);
			return (ft_ternint((t_g.err == 0), errthrow("$", vars[(
				ft_lento(t_g.cmd[pos], 24) > 0)],
				": ambiguous redirect", retfree(arg, tmp, 1)), t_g.err));
		}
		else
			ft_rplcmd(arg, pos);
	}
	else
	{
		free(tmp);
		tmp = t_g.cmd[pos];
		t_g.cmd[pos] = ft_strdup(arg);
		return (retfree(tmp, arg, 0));
	}
	return (retfree(arg, tmp, 0));
}
