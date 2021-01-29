/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:48:58 by wben-sai          #+#    #+#             */
/*   Updated: 2019/11/18 11:44:16 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		chck_save(char **save, char **line)
{
	char	*temp;
	int		i;
	int		j;

	j = -1;
	i = chr_bn(*save);
	*line = malloc((sizeof(char) * i) + 1);
	if (*line == NULL)
		return (-1);
	while (i > ++j)
		line[0][j] = save[0][j];
	line[0][j] = '\0';
	if (save[0][i + 1] == '\0')
	{
		free(*save);
		*save = NULL;
	}
	else
	{
		temp = *save;
		*save = ft_strjoin("", *save + i + 1);
		free(temp);
	}
	return (1);
}

char	*join_last_cs(char **was_read, char **new_lin, char **save)
{
	char *temp;

	if (chr_bn(*was_read) != -1)
	{
		temp = *save;
		*save = ft_strjoin("", *was_read + chr_bn(*was_read) + 1);
		free(temp);
	}
	if (chr_bn(*was_read) != -1)
		was_read[0][chr_bn(*was_read)] = '\0';
	temp = *new_lin;
	*new_lin = ft_strjoin(*new_lin, *was_read);
	free(temp);
	free(*was_read);
	*was_read = NULL;
	return (*new_lin);
}

char	*new_line(int fd, char **was_read, int *len_read, char **save)
{
	char *new_lin;
	char *temp;

	new_lin = malloc(sizeof(char));
	new_lin[0] = '\0';
	while (chr_bn(*was_read) == -1 && *len_read != 0)
	{
		temp = new_lin;
		new_lin = ft_strjoin(new_lin, *was_read);
		free(temp);
		free(*was_read);
		*was_read = NULL;
		if (BUFFER_SIZE != *len_read)
		{
			*len_read = 0;
			return (new_lin);
		}
		if (read_fd(was_read, len_read, fd) == -1)
			return (NULL);
	}
	return (join_last_cs(was_read, &new_lin, save));
}

char	*last_cs_save(int *len_read, char **save, char **line, char **was_read)
{
	char *temp;

	*line = malloc(sizeof(char));
	*line[0] = '\0';
	if (*len_read == 0)
	{
		if (*save != NULL)
		{
			temp = *line;
			*line = ft_strjoin(*line, *save);
			free(temp);
			free(*save);
			*save = NULL;
		}
		*len_read = 0;
		if (*was_read != NULL)
			free(*was_read);
		return (*line);
	}
	free(*save);
	*len_read = -1;
	if (*was_read != NULL)
		free(*was_read);
	return (*line);
}

int		get_next_line(int fd, char **line)
{
	static char	*save;
	char		*was_read;
	int			len_read;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE < 0 || line == NULL)
		return (-1);
	if (chr_bn(save) != -1 && save != NULL)
		return (chck_save(&save, line));
	if (read_fd(&was_read, &len_read, fd) > 0)
	{
		if (save != NULL)
		{
			temp = was_read;
			was_read = ft_strjoin(save, was_read);
			free(temp);
			free(save);
			save = NULL;
		}
		*line = new_line(fd, &was_read, &len_read, &save);
		len_read = (*line == NULL) ? -1 : len_read;
		return ((len_read == 0) ? 0 : 1);
	}
	*line = last_cs_save(&len_read, &save, line, &was_read);
	return (len_read);
}
