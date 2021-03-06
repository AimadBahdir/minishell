/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:30:43 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/06 10:31:24 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	errthrow(char *erp1, char *erp2, char *erp3, int errcode)
{
	write(2, "bash: ", strlen("bash: "));
	if (erp1)
		write(2, erp1, ft_strlen(erp1));
	if (erp2)
		write(2, erp2, ft_strlen(erp2));
	if (erp3)
		write(2, erp3, ft_strlen(erp3));
	write(2, "\n", 1);
	return (errcode);
}

short	ft_duptwo(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		return (errthrow("dup2: ", strerror(errno), NULL, errno));
	return (0);
}

int		retfreetwo(char **tmp1, int ret)
{
	int i;

	i = 0;
	if (tmp1)
	{
		while (tmp1[i] != 0)
		{
			free(tmp1[i]);
			tmp1[i] = NULL;
			i++;
		}
		free(tmp1);
		tmp1 = NULL;
	}
	return (ret);
}

int	ft_ternint(short cond, int iftrue, int iffalse)
{
	if (cond)
		return (iftrue);
	else
		return (iffalse);
}
