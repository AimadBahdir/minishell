/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:49:18 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/26 12:13:57 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short    ft_echo(char **args)
{
    short cond;
    short i;

    if (!args[1])
        return (write(STDOUT_FILENO, "\n", 1));
    cond = (args[1][0] == '-' && ft_strcmp(args[1], "-n"));
    args += (cond) ? 2 : 1;
    i = -1;
    while (args[++i])
    {
        ft_putstr(args[i]);
        if (args[i + 1])
            write(STDOUT_FILENO, " ", 1);
    }
    if (!cond)
        write(STDOUT_FILENO, "\n", 1);
    return (1);
}

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

short	ft_pwd(t_env **e)
{
	char	*path;
	char	*pwd;

	if (!(pwd = getcwd(NULL, 0)))
		return (errthrow(strerror(errno), NULL, NULL, NULL));
	ft_putstr(pwd);
	path = getenval(*e, "PWD");
	if (path != NULL && !ft_strcmp(path, pwd))
		setenval(e, "PWD", pwd);
	return (1);
}

short	ft_export(t_env **e, char **args)
{
	char	*key;
	int		klen;
	short	i;

	i = 0;
	if (ft_lentwop(args) < 2)
		return (ft_exprint(*e));
	while (args[++i])
	{
		if (ft_checkfor('=', args[i]) > 0)
		{
			klen = ft_lento(args[i], '=') + 1;
			key = ft_substr(args[i], 0, (klen - 1));
			if (!ft_strnormed(key))
				errthrow("export: `", key, "=': not a valid identifier.", NULL);
			else if (!getenval(*e, key))
				envaddelm(e, newenvelm(ft_substr(args[i], 0, (klen - 1)),
				ft_substr(args[i], klen,(ft_strlen(args[i]) - klen))));
			else
				setenval(e, key, ft_substr(args[i], klen,
						(ft_strlen(args[i]) - klen)));
		} else if (!ft_strnormed(args[i]))
			errthrow("export: `", args[i], "': not a valid identifier.", NULL);
	}
	return (1);
}

short	ft_unset(t_env **e, char **args)
{
	short	i;

	i = 0;
	if (ft_lentwop(args) <= 1)
		return (-1);
	while (args[++i])
	{
		if (!ft_strnormed(args[i]))
			errthrow("unset: `", args[i], "': not a valid identifier.", NULL);
		else
			rmenval(e, args[i]);
	}
	return (1);
}
