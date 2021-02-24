/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:07:26 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/23 12:41:47 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_rplchome(t_env *e, char *path)
{
	char *tmp;

	tmp = path;
	if (path == NULL)
		path = g_homepath;
	else if (path[0] == '~')
		path = ft_strjoin(g_homepath, (path + 1));
	free(tmp);
	return (path);
}

short	ft_cd(t_env **e, char **args)
{
	char *pwd;
	char *path;

	path = args[1];
	if (!path || path[0] == '~')
		path = ft_rplchome(*e, path);
	if (chdir(path) == -1)
		return (errthrow("cd: ", path, ": ", strerror(errno)));
	if (!(pwd = getcwd(NULL, 0)))
		return (-1);
	if (getenval(*e, "PWD"))
		setenval(e, "PWD", pwd);
	return (1);
}