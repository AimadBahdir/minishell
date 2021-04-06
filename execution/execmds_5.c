/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 10:51:59 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/06 10:50:23 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	novalidentif(short cmd, char *identif)
{
	char	*tmp;
	int		err;

	if (cmd)
		tmp = ft_strdup("export: `");
	else
		tmp = ft_strdup("unset: `");
	err = errthrow(tmp, identif, "=': not a valid identifier.", 1);
	return (retfree(tmp, NULL, err));
}

short	ft_exportelem(t_env **envlst, char *key, char *val, short exl)
{
	char	*k;
	char	*v;
	char	*tmp;

	k = NULL;
	v = NULL;
	if (ft_strnormed(key) != -1)
		return (novalidentif(1, key));
	if (!exl)
	{
		k = ft_strdup(key);
		v = ft_strdup(val);
		tmp = getenval(*envlst, k);
		if (tmp == NULL)
			envaddelm(envlst, newenvelm(k, v));
		else
			setenval(envlst, k, v);
		retfree(tmp, NULL, 0);
	}
	tmp = getenval(t_g.explst, key);
	if (tmp == NULL)
		envaddelm(&t_g.explst, newenvelm(key, val));
	else
		setenval(&t_g.explst, key, val);
	return (retfree(tmp, NULL, 0));
}

short	ft_export(t_env **e)
{
	char	*noval;

	t_g.indx = 0;
	t_g.err = 0;
	if (ft_lentwop(t_g.cmd) < 2)
		return (ft_exprint());
	while (t_g.cmd[++t_g.indx])
	{
		if (ft_checkfor('=', t_g.cmd[t_g.indx]) > 0)
		{
			t_g.kl = ft_lento(t_g.cmd[t_g.indx], '=') + 1;
			t_g.err = ft_exportelem(e, ft_substr(t_g.cmd[t_g.indx], 0,
						t_g.kl - 1), ft_substr(t_g.cmd[t_g.indx], t_g.kl,
						(ft_strlen(t_g.cmd[t_g.indx]) - t_g.kl)), 0);
		}
		else if (ft_strnormed(t_g.cmd[t_g.indx]) == -1)
		{
			noval = ft_strdup(" ");
			noval[0] = 16;
			ft_exportelem(&t_g.explst, ft_strdup(t_g.cmd[t_g.indx]), noval, 1);
		}
		else
			t_g.err = novalidentif(1, t_g.cmd[t_g.indx]);
	}
	return (t_g.err);
}

short	ft_unset(t_env **e)
{
	short	i;
	int		err;

	i = 0;
	err = 0;
	if (ft_lentwop(t_g.cmd) <= 1)
		return (1);
	while (t_g.cmd[++i])
	{
		if (ft_strnormed(t_g.cmd[i]) != -1)
			err = novalidentif(0, t_g.cmd[i]);
		else
		{
			rmenval(e, t_g.cmd[i]);
			rmenval(&t_g.explst, t_g.cmd[i]);
		}
	}
	return (err);
}

short	ft_setoldcmd(t_env **lst, char *cmdpath)
{
	char	*cmd;

	cmd = ft_strdup(cmdpath);
	ft_strlower(cmd);
	if (ft_strcmp(cmd, "sort"))
		t_g.iscmd = 1;
	else
		t_g.iscmd = 2;
	free(cmd);
	cmd = ft_strdup(cmdpath);
	setenval(lst, ft_strdup("_"), cmd);
	cmd = ft_strdup(cmdpath);
	setenval(&t_g.explst, ft_strdup("_"), cmd);
	return (127);
}
