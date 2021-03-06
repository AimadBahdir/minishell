/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:07:26 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/06 12:29:27 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_rplchome(char *path)
{
	char *tmp;

	tmp = path;
	if (path == NULL)
		path = t_g.homepath;
	else if (path[0] == '~')
		path = ft_strjoin(t_g.homepath, (path + 1));
	free(tmp);
	return (path);
}

short	ft_cd(t_env **e, char **args)
{
	char *pwd;
	char *path;

	path = args[1];
	if (!path || path[0] == '~')
		path = ft_rplchome(path);
	if (chdir(path) == -1)
		return (errthrow(path, ": cd: ", strerror(errno), errno));
	if (!(pwd = getcwd(NULL, 0)))
		return (errthrow("cd: ", "pwd: ", strerror(errno), errno));
	if (getenval(*e, "PWD"))
		setenval(e, "PWD", pwd);
	return (0);
}

short   ft_pipe(void)
{
	int err;

	err = 0;
    if (t_pipe.next)
    {
        if ((err = ft_duptwo(t_pipe.nxtio[1], STDOUT_FILENO)) > 0)
			return (err);
		close(t_pipe.nxtio[1]);
    }
    if (t_pipe.prev)
    {
        if ((err = ft_duptwo(t_pipe.prvo, STDIN_FILENO)) > 0)
			return (err);
    	close(t_pipe.prvo);
    }
    return (err);
}