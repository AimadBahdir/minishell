/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:02:27 by wben-sai          #+#    #+#             */
/*   Updated: 2021/02/03 18:23:58 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	print_exit(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

int		read_fd(char **was_read, int *len_read, int fd)
{
	*was_read = malloc(BUFFER_SIZE + 1);
	if (*was_read == NULL)
		return (-1);
	*len_read = read(fd, *was_read, BUFFER_SIZE);
	was_read[0][*len_read] = '\0';
	t_params.temp = t_params.was_read;
	t_params.was_read = ft_strjoin(t_params.was_read, *was_read);
	free(t_params.temp);
	if (was_read[0][*len_read - 1] != '\n')
	{
		if (*len_read == 0 && !*t_params.was_read)
			print_exit();
		free(*was_read);
		*len_read += read_fd(was_read, len_read, fd);
	}
	t_params.temp = *was_read;
	*was_read = strdup(t_params.was_read);
	free(t_params.temp);
	if (*len_read == -1)
	{
		free(*was_read);
		*was_read = NULL;
		return (-1);
	}
	return (*len_read);
}
