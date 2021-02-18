/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/17 14:27:20 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char    **spltcmd(char **cmd)
{
    char    **args;
    short   i;
    short   stop;

    stop = -1;
    while (cmd[++stop])
        if (cmd[stop][0] == 27)
            break;
    if (!(args = malloc(sizeof(char *) * stop)))
        return (NULL);
    i = -1;
    args[stop] = NULL;
    while (++i < stop)
        args[i] = cmd[i];
    return (args);
}

int   fillfile(t_env **envlst, char **cmd, int fd)
{
    int pid;
    int file;
    int err;

    dup2(fd, STDOUT_FILENO);
    err = ft_execmd(envlst, cmd);
    return 1;
}

short   gdirections(t_env **envlst, char **cmd)
{
    short   i;
    int     pid;
    int     fd;

    i = -1;
    fd = 0;
    while (cmd[++i])
    {
        
        if (cmd[i][0] == 27
            && cmd[i][1] == '>'
            && cmd[i][2] == '>')
        {
            fd = open(cmd[++i],  O_CREAT | O_RDWR | O_APPEND, 0644);
            if (cmd[i + 1] == NULL)
                fillfile(envlst, spltcmd(cmd), fd);
            close(fd);
        }
        else if (cmd[i][0] == 27
            && cmd[i][1] == '>')
        {
            fd = open(cmd[++i],  O_CREAT | O_RDWR | O_TRUNC, 0644);
            if (cmd[i + 1] == NULL)
                fillfile(envlst, spltcmd(cmd), fd);
            close(fd);
        }
    }
    return (0);
}