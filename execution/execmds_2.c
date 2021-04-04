/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:49:18 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/04 13:20:21 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	ft_env(t_env *e)
{
	if (ft_lentwop(t_g.cmd) > 1)
	{
		return (errthrow("env: ", t_g.cmd[1],
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

short	ft_pwd(t_env **e, short get)
{
	char	*path;
	char	*pwd;

	if (!(pwd = getcwd(NULL, 0)))
		return (errthrow(strerror(errno), NULL, NULL, errno));
	path = getenval(*e, "PWD");
	if (get)
		ft_putstr(pwd, 1);
	if (path != NULL)
	{
		setenval(e, "PWD", ft_strdup(pwd));
		setenval(&t_g.explst, "PWD", ft_strdup(pwd));
	}
	else if (!get)
	{
		envaddelm(e, newenvelm(ft_strdup("PWD"), ft_strdup(pwd)));
		envaddelm(&t_g.explst, newenvelm(ft_strdup("PWD"), ft_strdup(pwd)));
	}
	return (retfree(path, pwd, 0));
}
