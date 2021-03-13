/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:57:42 by wben-sai          #+#    #+#             */
/*   Updated: 2021/03/12 11:57:38 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../minishell.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

int		chr_bn(char *was_read);
int		get_next_line(int fd, char **line);
int		chck_save(char **save, char **line);
int		read_fd(char **was_read, int *len_read, int fd);
char	*join_last_cs(char **was_read, char **new_lin, char **save);
char	*new_line(int fd, char **was_read, int *len_read, char **save);
char	*last_cs_save(int *len_read, char **save, char **line, char **was_read);

#endif
