/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:49:18 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/10 10:13:23 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	ft_env(t_env *e, char **args)
{
	if (ft_lentwop(args) > 1)
		return (errthrow("env: ", args[1],
				": No such file or directory", 127));
	while (e)
	{
		ft_putstr(e->key);
		write(t_g.mystdout, "=", 1);
		ft_putstr(e->val);
		write(t_g.mystdout, "\n", 1);
		e = e->next;
	}
	return (0);
}

short	ft_pwd(t_env **e)
{
	char	*path;
	char	*pwd;

	if (!(pwd = getcwd(NULL, 0)))
		return (errthrow(strerror(errno), NULL, NULL, errno));
	ft_putstr(pwd);
	path = getenval(*e, "PWD");
	if (path != NULL && !ft_strcmp(path, pwd))
		setenval(e, "PWD", pwd);
	return (0);
}

short	ft_export(t_env **e, char **args)
{
	char	*key;
	int		klen;
	int		err;
	short	i;

	i = 0;
	if (!(err = 0) && ft_lentwop(args) < 2)
		return (ft_exprint(*e));
	while (args[++i])
	{
		if (ft_checkfor('=', args[i]) > 0)
		{
			klen = ft_lento(args[i], '=') + 1;
			key = ft_substr(args[i], 0, (klen - 1));
			if (!ft_strnormed(key))
				err = errthrow("export: `", key, "=': not a valid identifier.", 1);
			else if (!getenval(*e, key))
				envaddelm(e, newenvelm(ft_substr(args[i], 0, (klen - 1)),
				ft_substr(args[i], klen,(ft_strlen(args[i]) - klen))));
			else
				setenval(e, key, ft_substr(args[i], klen,
						(ft_strlen(args[i]) - klen)));
		} else if (!ft_strnormed(args[i]))
			err = errthrow("export: `", args[i], "': not a valid identifier.", 1);
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
		if (!ft_strnormed(args[i]))
			err = errthrow("unset: `", args[i], "': not a valid identifier.", 1);
		else
			rmenval(e, args[i]);
	}
	return (err);
}
