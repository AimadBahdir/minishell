/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 13:30:26 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/11 09:29:51 by abahdir          ###   ########.fr       */
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

short	ft_duptwo(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		return (errthrow("dup2: ", strerror(errno), NULL, errno));
	return (0);
}
