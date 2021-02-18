/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:07:26 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/17 15:50:50 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_rplchome(t_env *e, char *path)
{
	char *tmp;
	char *home;

	tmp = path;
	if(!(home = getenval(e, "HOME")))
		home = ft_strdup("");
	if (path == NULL)
		path = home;
	else if (path[0] == '~')
		path = ft_strjoin(home, (path + 1));
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
		return (errthrow(strerror(errno), " > cd: ", path, NULL));
	if (!(pwd = getcwd(NULL, 0)))
		return (-1);
	if (getenval(*e, "PWD"))
		setenval(e, "PWD", pwd);
	return (1);
}