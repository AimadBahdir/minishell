/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:30:43 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/24 15:09:40 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short   errthrow(char *erp1, char *erp2, char *erp3, char *erp4)
{
    write(2, "bash: ", strlen("bash: "));
    if (erp1)
        write(2, erp1, ft_strlen(erp1));
    if (erp2)
        write(2, erp2, ft_strlen(erp2));
    if (erp3)
        write(2, erp3, ft_strlen(erp3));
    if (erp4)
        write(2, erp4, ft_strlen(erp4));
    write(2, "\n", 1);
    return (-1);
}

void ft_stdrst(int fd)
{
	if (fd == 1 && g_stdout != STDOUT_FILENO)
	{
		close(g_stdout);
		g_stdout = STDOUT_FILENO;
	}
	if (fd == 0 && g_stdin != STDIN_FILENO)
	{
		close(g_stdin);
		g_stdin = STDIN_FILENO;
	}
}

void    ft_duptwo(int fd1, int fd2)
{
    if (dup2(fd1, fd2) < 0)
        errthrow(strerror(errno), NULL, NULL, NULL);
}