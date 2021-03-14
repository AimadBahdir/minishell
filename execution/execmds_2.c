/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:49:18 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/14 10:54:22 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	ft_env(t_env *e, char **args)
{
	if (ft_lentwop(args) > 1)
	{
		return (errthrow("env: ", args[1],
			": No such file or directory", 127));
	}
	while (e)
	{
		ft_putstr(e->key, 0);
		write(t_g.mystdout, "=", 1);
		ft_putstr(e->val, 1);
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
	ft_putstr(pwd, 1);
	path = getenval(*e, "PWD");
	if (path != NULL && !ft_strcmp(path, pwd))
		setenval(e, "PWD", pwd);
	return (0);
}
