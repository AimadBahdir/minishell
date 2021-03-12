/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:30:43 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/11 09:29:39 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	errthrow(char *erp1, char *erp2, char *erp3, int errcode)
{
	write(STDERR_FILENO, "bash: ", strlen("bash: "));
	if (erp1)
		write(STDERR_FILENO, erp1, ft_strlen(erp1));
	if (erp2)
		write(STDERR_FILENO, erp2, ft_strlen(erp2));
	if (erp3)
		write(STDERR_FILENO, erp3, ft_strlen(erp3));
	write(STDERR_FILENO, "\n", 1);
	return (errcode);
}

int		retfree(char *tmp1, char *tmp2, int ret)
{
	if (tmp1 != NULL)
	{
		free(tmp1);
		tmp1 = NULL;
	}
	if (tmp2 != NULL)
	{
		free(tmp2);
		tmp2 = NULL;
	}
	return (ret);
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

int		ft_ternint(short cond, int iftrue, int iffalse)
{
	if (cond)
		return (iftrue);
	else
		return (iffalse);
}

void	ft_closefds(void)
{
	close(t_g.mystdin);
	close(t_g.mystdout);
	if (!t_pipe.prev)
		close(t_pipe.prvo);
	if (!t_pipe.next)
	{
		close(t_pipe.nxtio[0]);
		close(t_pipe.nxtio[1]);
	}
}