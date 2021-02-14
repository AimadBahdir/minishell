/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/13 15:18:47 by abahdir          ###   ########.fr       */
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
        if (ft_strcmp(cmd[stop], ">")
        || ft_strcmp(cmd[stop], ">>")
        || ft_strcmp(cmd[stop], "<"))
            break;
    if (!(args = malloc(sizeof(char *) * stop)))
        return (NULL);
    i = -1;
    args[stop] = NULL;
    while (++i < stop)
        args[i] = cmd[i];
    return (args);
}

// int   fillfile(char **cmd, int i)
// {
//     int fd;

//     if (ft_strcmp(cmd[i], ">"))
//     {
        
//     }
//     return 1;
// }

// short   gdirections(t_env **envlst, char **cmd)
// {
//     short   i;
//     int     pid;
//     int     fd;

//     i = -1;
//     fd = 0;
//     while (cmd[++i])
//     {
//         if (ft_strcmp(cmd[i], ">"))
//         {
//             fd = open(cmd[++i],  O_CREAT | O_RDWR | O_TRUNC, 0644);
             
//             close(fd);
//         }
//         else if (ft_strcmp(cmd[i], ">>"))
//         {
//             fd = open(cmd[++i],  O_CREAT | O_RDWR | O_APPEND, 0644);
//             close(fd);
//         }
//     }
//     return (0);
// }