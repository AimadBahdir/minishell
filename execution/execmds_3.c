/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:07:26 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/27 17:56:15 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_rplchome(t_env *e, char *path)
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
		path = ft_rplchome(*e, path);
	if (chdir(path) == -1)
		return (errthrow("cd: ", path, ": ", strerror(errno)));
	if (!(pwd = getcwd(NULL, 0)))
		return (-1);
	if (getenval(*e, "PWD"))
		setenval(e, "PWD", pwd);
	return (1);
}

short   ft_pipe(void)
{
    if (t_pipe.next)
    {
    	close(t_pipe.nxtio[0]);
        if (!ft_duptwo(t_pipe.nxtio[1], STDOUT_FILENO))
			return (0);
		close(t_pipe.nxtio[1]);
    }
    if (t_pipe.prev)
    {
        if (!ft_duptwo(t_pipe.prvo, STDIN_FILENO))
			return (0);
    	close(t_pipe.prvo);
    }
    return (1);
}