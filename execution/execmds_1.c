/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmds_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:37:58 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/05 16:30:59 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short   ft_execmd(t_env **lst, char **cmdargs)
{
	char *cmd;

	cmd = ft_strlower(cmdargs[0]);
    if (ft_strcmp(cmd, "echo"))
        return (ft_echo(cmdargs));
    else if (ft_strcmp(cmd, "cd"))
        return (ft_cd(lst, cmdargs));
	else if (ft_strcmp(cmd, "pwd"))
		return (ft_pwd(*lst));
	else if (ft_strcmp(cmd, "env"))
		return (ft_env(*lst));
    else if (ft_strcmp(cmd, "export"))
        return (ft_export(lst, cmdargs));
    else if (ft_strcmp(cmd, "unset"))
        return (ft_unset(lst, cmdargs));
    else
	    return(-1);
}

short    ft_echo(char **args)
{
    short cond;

    cond = (args[1][0] == '-' && ft_strcmp(args[1], "-n"));
    args += (cond) ? 2 : 1;
    ft_putmstr(args, ' ');
    if (!cond)
        write(STDOUT_FILENO, "\n", 1);
    return (1);
}

