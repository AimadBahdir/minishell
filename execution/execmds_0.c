/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/20 15:02:38 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short    ft_echo(char **args)
{
    short cond;
    short i;

    if (!args[1])
        return (-1);
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

short   ft_execmd(t_env **lst, char **cmdargs)
{
	char *cmd;


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
	    return(execve(ft_strjoin("/bin/",cmd), cmdargs, g_envp));
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

// short   ft_execute(t_env **envlst, t_inputs *cmdlst)
// {
//     t_inputs    *head;
    
//     head = cmdlst;
//     while (head)
//     {
//         if (chk_directions(head->command))
//             gdirections(envlst, head->command);
//         head = head->next;
//     }
    
// }