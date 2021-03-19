/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 10:51:59 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/19 12:33:14 by abahdir          ###   ########.fr       */
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
	char *k;
	char *v;

	k = NULL;
	v = NULL;
	if (ft_strnormed(key) != -1)
		return (novalidentif(1, key));
	if (!exl)
	{
		k = ft_strdup(key);
		v = ft_strdup(val);
		if (getenval(*envlst, k) == NULL)
			envaddelm(envlst, newenvelm(k, v));
		else
			setenval(envlst, k, v);
	}
	if (getenval(t_g.explst, key) == NULL)
		envaddelm(&t_g.explst, newenvelm(key, val));
	else
		setenval(&t_g.explst, key, val);
	return (0);
}

short	ft_export(t_env **e, char **args)
{
	int		keylen;
	int		err;
	char	*noval;
	short	i;

	i = 0;
	if (!(err = 0) && ft_lentwop(args) < 2)
		return (ft_exprint());
	while (args[++i])
	{
		if (ft_checkfor('=', args[i]) > 0)
		{
			keylen = ft_lento(args[i], '=') + 1;
			err = ft_exportelem(e, ft_substr(args[i], 0, keylen - 1),
				ft_substr(args[i], keylen, (ft_strlen(args[i]) - keylen)), 0);
		}
		else if (ft_strnormed(args[i]) == -1)
		{
			noval = ft_strdup(" ");
			noval[0] = 16;
			ft_exportelem(&t_g.explst, ft_strdup(args[i]), noval, 1);
		}
		else
			err = novalidentif(1, args[i]);
	}
	return (err);
}

short	ft_unset(t_env **e, char **args)
{
	short	i;
	int		err;

	i = 0;
	err = 0;
	if (ft_lentwop(args) <= 1)
		return (1);
	while (args[++i])
	{
		if (ft_strnormed(args[i]) != -1)
			err = novalidentif(0, args[i]);
		else
		{
			rmenval(e, args[i]);
			rmenval(&t_g.explst, args[i]);
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
	setenval(lst, "_", cmd);
	cmd = ft_strdup(cmdpath);
	setenval(&t_g.explst, "_", cmd);
	return (127);
}
