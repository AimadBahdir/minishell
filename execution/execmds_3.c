/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:07:26 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/26 12:12:57 by abahdir          ###   ########.fr       */
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

short   ft_pipe(short inp)
{
    if (inp)
    {
        t_stdorigin.stdoutpt = dup(STDOUT_FILENO);
        if (dup2(t_navpipe.next.inout[0], STDOUT_FILENO) < 0)
            return (errthrow("dup2: ", strerror(errno), NULL, NULL));
        close(t_navpipe.next.inout[0]);
        close(t_navpipe.next.inout[1]);
    }
    else
    {
        t_stdorigin.stdinpt = dup(STDIN_FILENO);
        if (dup2(t_navpipe.prev.inout[1], STDIN_FILENO) < 0)
            return (errthrow("dup2: ", strerror(errno), NULL, NULL));
        close(t_navpipe.prev.inout[0]);
        close(t_navpipe.prev.inout[1]);
        t_navpipe.prev.exist = 0;
    }
    return (1);
}