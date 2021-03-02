/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/02 11:50:17 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short   ft_othercmd(char **cmdargs)
{
    int pid;
    char *cmd;

    pid = fork();
    if (pid < 0)
        return (errthrow("Error", "in", "Forking", 1));
    if (pid == 0)
    {
        cmd = ft_strjoin("/bin/", cmdargs[0]);
        if (execve(cmd, cmdargs, t_g.envp) == -1)
            exit(errthrow(strerror(errno), NULL, NULL, errno));
        free(cmd);
        exit(0);
    }
    else
        wait(NULL);
    return (1);
}

short   ft_execmd(t_env **lst, char **cmdargs)
{
	char    *cmd;
    short   err;

    cmd = ft_strlower(cmdargs[0]);
    if (ft_strcmp(cmd, "echo"))
        err = ft_echo(cmdargs);
    else if (ft_strcmp(cmd, "cd"))
        err = ft_cd(lst, cmdargs);
    else if (ft_strcmp(cmd, "pwd"))
        err = ft_pwd(lst, cmdargs);
    else if (ft_strcmp(cmd, "env"))
        err = ft_env(*lst, cmdargs);
    else if (ft_strcmp(cmd, "export"))
        err = ft_export(lst, cmdargs);
    else if (ft_strcmp(cmd, "unset"))
        err = ft_unset(lst, cmdargs);
    else
        err = ft_othercmd(cmdargs);
    return (err);
}

short   chk_directions(char **lst)
{
    int i;

    i = -1;
    if (!lst)
        return (-1);
    while (lst[++i])
        if (lst[i][0] == 27)
            return (1);
    return (0);
}

short   ft_exchild(t_env **envlst, char **cmd)
{
    int err;

    err = 0;
    if ((err = ft_pipe()) > 0)
        return (err);
    if (chk_directions(cmd))
    {   
        if ((err = gdirections(envlst, cmd)) > 0)
            return (err);
    }
    else
    {
        if ((err = ft_execmd(envlst, cmd)) > 0)
            return (err);
    }
    return (err);
}

short   ft_execute(t_env **envlst, t_inputs *cmdlst)
{
    t_inputs    *head;
    int         pid;

    head = cmdlst;
    t_pipe.prev = 0;
    while (head)
    {
        if ((t_pipe.next = head->pipe) == 1)
            if (pipe(t_pipe.nxtio) < 0)
                exit(errthrow(strerror(errno), NULL, NULL, 1));
        if ((pid = fork()) < 0)
            exit(errthrow(strerror(errno), NULL, NULL, 1));
        else if (pid == 0)
            exit(ft_exchild(envlst, head->command));
        else
        {
            wait(NULL);
            t_pipe.prev = 0;
            if (t_pipe.next)
            {
                if ((t_pipe.prvo = dup(t_pipe.nxtio[0])) < 0)
                    return (-1);
                close(t_pipe.nxtio[0]);
                t_pipe.prev = 1;
            }
        }
        head = head->next;
    }
    return (1);
}