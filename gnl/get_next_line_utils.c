/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:02:27 by wben-sai          #+#    #+#             */
/*   Updated: 2020/01/07 19:27:44 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	int		i;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	ptr = malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	if (ptr == NULL)
		return (NULL);
	while (len_s1 > 0 && s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	len_s1 = 0;
	while (len_s2 > 0 && s2[len_s1] != '\0')
		ptr[i++] = s2[len_s1++];
	ptr[i] = '\0';
	return (ptr);
}

int		ft_strlen(char *s)
{
	int x;

	x = 0;
	while (s[x] != '\0')
		x++;
	return (x);
}

int		chr_bn(char *was_read)
{
	int i;

	i = 0;
	if (was_read == NULL)
		return (-1);
	while (was_read[i] != '\0')
	{
		if (was_read[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		read_fd(char **was_read, int *len_read, int fd)
{
	*was_read = malloc(BUFFER_SIZE + 1);
	if (*was_read == NULL)
		return (-1);
	*len_read = read(fd, *was_read, BUFFER_SIZE);
	if (*len_read == -1)
	{
		free(*was_read);
		*was_read = NULL;
		return (-1);
	}
	was_read[0][*len_read] = '\0';
	return (*len_read);
}
