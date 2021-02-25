/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/25 11:42:44 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short    ft_echo(char **args)
{
    short cond;
    short i;

    if (!args[1])
        return (write(STDOUT_FILENO, "\n", 1));
    cond = (args[1][0] == '-' && ft_strcmp(args[1], "-n"));
    args += (cond) ? 2 : 1;
    i = -1;
    while (args[++i])
    {
        ft_putstr(args[i]);
        if (args[i + 1])
            write(STDOUT_FILENO, " ", 1);
    }
    if (!cond)
        write(STDOUT_FILENO, "\n", 1);
    return (1);
}

short   ft_othercmd(char **cmdargs)
{
    int pid;

    pid = fork();
    if (pid < 0)
        return (errthrow("Error", "in", "Forking", NULL));
    if (pid == 0)
    {
        if (execve(ft_strjoin("/bin/",cmdargs[0]), cmdargs, g_envp) == -1)
            exit(errthrow(strerror(errno), NULL, NULL, NULL) + 1);
        exit(1);
    }
    return (1);
}

short   ft_execmd(t_env **lst, char **cmdargs)
{
	char    *cmd;

    cmd = ft_strlower(cmdargs[0]);
    if (ft_strcmp(cmd, "echo"))
        return (ft_echo(cmdargs));
    else if (ft_strcmp(cmd, "cd"))
        return (ft_cd(lst, cmdargs));
    else if (ft_strcmp(cmd, "pwd"))
        return (ft_pwd(lst));
    else if (ft_strcmp(cmd, "env"))
        return (ft_env(*lst));
    else if (ft_strcmp(cmd, "export"))
        return (ft_export(lst, cmdargs));
    else if (ft_strcmp(cmd, "unset"))
        return (ft_unset(lst, cmdargs));
    else
        return(ft_othercmd(cmdargs));
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

short   ft_pipe(short inp)
{
    if (inp)
    {
        if (dup2(t_pipe.fds[0], STDOUT_FILENO) < 0)
            return (errthrow(strerror(errno), NULL, NULL, NULL));
        t_pipe.nxtpipe = 1;
    }
    else
    {
        if (dup2(t_pipe.fds[1], STDIN_FILENO) < 0)
            return (errthrow(strerror(errno), NULL, NULL, NULL));
        t_pipe.prvpipe = 1;
    }
    close(t_pipe.fds[0]);
    close(t_pipe.fds[1]);
    return (1);
}

void    ft_expipe(t_env **envlst, char **cmd)
{
    int     pid;
    short   prvp;
    short   nxtp;

    if (pipe(t_pipe.fds) < 0)
        errthrow(strerror(errno), NULL, NULL, NULL);
    if ((pid = fork()) < 0)
        errthrow(strerror(errno), NULL, NULL, NULL);
    else if (pid == 0)
    {
        if (t_pipe.nxtpipe)
            nxtp = ft_pipe(1);
        else
            prvp = ft_pipe(0);
        if (chk_directions(cmd))
            gdirections(envlst, cmd);
        else
            ft_execmd(envlst, cmd);
        if (prvp == 1)
            t_pipe.prvpipe = 0;
        if (nxtp == 1)
            t_pipe.prvpipe = 1;
        exit(0);
    }
    wait(NULL);
    close(t_pipe.fds[0]);
    close(t_pipe.fds[1]);
}

short   ft_execute(t_env **envlst, t_inputs *cmdlst)
{
    t_inputs    *head;

    head = cmdlst;
    t_pipe.nxtpipe = 0;
    t_pipe.prvpipe = 0;
    while (head)
    {
        if ((t_pipe.nxtpipe = head->pipe) || t_pipe.prvpipe)
            ft_expipe(envlst, head->command);
        else if (chk_directions(head->command))
            gdirections(envlst, head->command);
        else
            ft_execmd(envlst, head->command);
        head = head->next;
    }
    return (1);
}