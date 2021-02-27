/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/27 18:17:28 by abahdir          ###   ########.fr       */
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
        if (execve(ft_strjoin("/bin/",cmdargs[0]), cmdargs, t_g.envp) == -1)
            exit(errthrow(strerror(errno), NULL, NULL, NULL) + 1);
        exit(1);
    }
    return (1);
}

short   ft_execmd(t_env **lst, char **cmdargs)
{
	char    *cmd;
    short   res;

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
    
    return (1);
}

short   ft_exchild(t_env **envlst, char **cmd)
{
    if (!ft_pipe())
        return (1);
    if (chk_directions(cmd))
    {
        if (gdirections(envlst, cmd) <= 0)
            return (1);
    }
    else
    {
        if (ft_execmd(envlst, cmd) <= 0)
            return (1);
    }
    return (0);
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
                return (errthrow(strerror(errno), NULL, NULL, NULL));
        if ((pid = fork()) < 0)
            exit(errthrow(strerror(errno), NULL, NULL, NULL) + 2);
        if (pid == 0)
            exit(ft_exchild(envlst, head->command));
        else
        {
            wait(NULL);
            if (t_pipe.next)
            {
                if ((t_pipe.prvo = dup(t_pipe.nxtio[0])))
                    return (-1);
                t_pipe.prev = 1;
            }
        }
        head = head->next;
    }
    return (1);
}