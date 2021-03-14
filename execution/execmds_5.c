/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 10:51:59 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/14 11:03:17 by abahdir          ###   ########.fr       */
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

short	ft_exportelem(t_env **envlst, char *key, char *val)
{
	if (!ft_strnormed(key))
		return (novalidentif(1, key));
	else if (getenval(*envlst, key) == NULL)
	{
		envaddelm(envlst, newenvelm(key, val));
	}
	else
		setenval(envlst, key, val);
	return (0);
}

short	ft_export(t_env **e, char **args)
{
	int		keylen;
	int		err;
	short	i;

	i = 0;
	if (!(err = 0) && ft_lentwop(args) < 2)
		return (ft_exprint(*e));
	while (args[++i])
	{
		if (ft_checkfor('=', args[i]) > 0)
		{
			keylen = ft_lento(args[i], '=') + 1;
			err = ft_exportelem(e, ft_substr(args[i], 0, keylen - 1),
					ft_substr(args[i], keylen, (ft_strlen(args[i]) - keylen)));
		}
		else if (!ft_strnormed(args[i]))
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
		if (!ft_strnormed(args[i]))
			err = novalidentif(0, args[i]);
		else
			rmenval(e, args[i]);
	}
	return (err);
}
