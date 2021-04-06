/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 09:46:48 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/05 17:25:09 by abahdir          ###   ########.fr       */
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
	if (ft_checkfor(' ', (t_params.temp = ft_strtrim(val, "\t "))) != -1)
		t_g.haspace = 1;
	res = ft_strjoin(val, suit);
	retfree(key, val, 0);
	retfree(t_params.temp, suit, 0);
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

void	ft_setcmdvar(char *arg, int *pos)
{
	char	*tmp;
	char	**oldcmd;
	int		len;
	int		j;
	int		i;

	tmp = t_g.cmd[*pos];
	oldcmd = t_g.cmd;
	len = ft_lentwop(t_g.cmd);
	if (*pos == 0 && !*arg)
	{
		i = 0;
		j = *pos;
		t_g.cmd = malloc(len * sizeof(char *));
		while (oldcmd[++j])
			t_g.cmd[i++] = ft_strdup(oldcmd[j]);
		t_g.cmd[j - 1] = 0;
		*pos -= 1;
		retfreetwo(oldcmd, 0);
	}
	else
	{
		t_g.cmd[*pos] = ft_strdup(arg);
		free(tmp);
	}
}

short	ft_chkambigs(t_env *envlst, int *pos, char **vars)
{
	char	*arg;
	int		err;

	err = 0;
	arg = ft_getvar(envlst, vars, t_g.cmd[*pos][0] == 24);
	if (t_g.haspace)
	{
		t_g.haspace = 0;
		if (pos > 0 && (t_g.cmd[*pos - 1][0] == 14
			|| t_g.cmd[*pos - 1][0] == 15))
		{
			err = ft_creatfiles(t_g.cmd, *pos - 1);
			return (ft_ternint((err == 0), errthrow("$", vars[(
				ft_lento(t_g.cmd[*pos], 24) > 0)],
				": ambiguous redirect", retfree(arg, NULL, 1)), err));
		}
		else
			ft_rplcmd(arg, *pos);
	}
	else
	{
		ft_setcmdvar(arg, pos);
		return (retfree(arg, NULL, 0));
	}
	return (retfree(arg, NULL, 0));
}
