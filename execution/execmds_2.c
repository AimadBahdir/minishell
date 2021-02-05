/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:49:18 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/05 17:08:05 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	ft_env(t_env *e)
{
	while (e)
	{
		ft_putstr(e->key);
		write(1, "=", 1);
		ft_putstr(e->val);
		write(1, "\n", 1);
		e = e->next;
	}
	return (e == NULL);
}

short	ft_pwd(t_env *e)
{
	char *path;

	if (!(path = getenval(e, "pwd")))
		return (0);
	ft_putstr(path);
	return (1);
}

short	ft_export(t_env **e, char **args)
{
	char	*key;
	int		klen;
	short	i;

	i = 0;
	if (ft_lentwop(args) <= 1)
		return (0);
	while (args[++i])
	{
		if (ft_checkfor('=', args[i]))
		{
			klen = ft_lento(args[i], '=') + 1;
			key = ft_substr(args[i], 0, (klen - 1));
			if (!ft_strnormed(key))
				errthrow(ft_strjoin(ft_strjoin("export: '",
				args[i]),"' not a valid identifier."));
			else if (!getenval(*e, key))
				envaddelm(e, newenvelm(ft_substr(args[i], 0, (klen - 1)),
				ft_substr(args[i], klen,(ft_strlen(args[i]) - klen))));
			else
				setenval(e, key, ft_substr(args[i], klen,
						(ft_strlen(args[i]) - klen)));
		}
	}
	return (1);
}

short	ft_unset(t_env **e, char **args)
{
	short	i;

	i = 0;
	if (ft_lentwop(args) <= 1)
		return (0);
	while (args[++i])
	{
		if (!ft_strnormed(args[i]))
			errthrow(ft_strjoin(ft_strjoin("unset: '",
					args[i]),"' not a valid identifier."));
		else
			rmenval(e, args[i]);
	}
	return (1);
}
