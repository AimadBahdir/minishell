/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/26 12:16:32 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
    short   res;

    if (t_navpipe.next.exist)
        ft_pipe(1);
    if (t_navpipe.prev.exist)
        ft_pipe(0);
    cmd = ft_strlower(cmdargs[0]);
    if (ft_strcmp(cmd, "echo"))
        res = ft_echo(cmdargs);
    else if (ft_strcmp(cmd, "cd"))
        res = ft_cd(lst, cmdargs);
    else if (ft_strcmp(cmd, "pwd"))
        res = ft_pwd(lst);
    else if (ft_strcmp(cmd, "env"))
        res = ft_env(*lst);
    else if (ft_strcmp(cmd, "export"))
        res = ft_export(lst, cmdargs);
    else if (ft_strcmp(cmd, "unset"))
        res = ft_unset(lst, cmdargs);
    else
        res = ft_othercmd(cmdargs);
    return (res);
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

short    ft_setprev(void)
{
    if(dup2(t_navpipe.prev.inout[0], t_navpipe.next.inout[0]) < 0)
        return (errthrow("dup2: ", strerror(errno), NULL, NULL));
    if(dup2(t_navpipe.prev.inout[1], t_navpipe.next.inout[1]) < 0)
        return (errthrow("dup2: ", strerror(errno), NULL, NULL));
    close(t_navpipe.next.inout[1]);
    close(t_navpipe.next.inout[0]);
    if (dup2(t_stdorigin.stdinpt, STDIN_FILENO))
        return (errthrow("dup2: ", strerror(errno), NULL, NULL));
    if (dup2(t_stdorigin.stdoutpt, STDOUT_FILENO))
        return (errthrow("dup2: ", strerror(errno), NULL, NULL));
    t_navpipe.prev.exist = 1;
    return (1);
}

short   ft_execute(t_env **envlst, t_inputs *cmdlst)
{
    t_inputs    *head;

    head = cmdlst;
    t_navpipe.next.exist = 0;
    t_navpipe.prev.exist = 0;
    while (head)
    {
        if ((t_navpipe.next.exist = head->pipe) == 1)
            if (pipe(t_navpipe.next.inout) < 0)
                return (errthrow(strerror(errno), NULL, NULL, NULL));
        if (chk_directions(head->command))
            gdirections(envlst, head->command);
        else
            ft_execmd(envlst, head->command);
        if (head->pipe)
            if (ft_setprev() < 0)
                return (0);
        head = head->next;
    }
    return (1);
}