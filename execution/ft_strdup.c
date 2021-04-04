/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 13:30:26 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/04 13:22:30 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *str)
{
	char	*ns;
	int		i;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	if (!(ns = malloc((i * sizeof(char)) + 1)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		ns[i] = str[i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}

short	ft_dupcmd(char **str)
{
	char	**oldp;
	int		i;

	if (!str)
		return (0);
	oldp = t_g.cmd;
	i = ft_lentwop(str);
	if (!(t_g.cmd = malloc((i + 1) * sizeof(char *))))
		return (0);
	i = -1;
	while (str[++i])
		t_g.cmd[i] = ft_strdup(str[i]);
	t_g.cmd[i] = NULL;
	return (retfreetwo(oldp, 1));
}

short	ft_duptwo(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		return (errthrow("dup2: ", strerror(errno), NULL, errno));
	return (0);
}
