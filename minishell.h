/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:12:49 by wben-sai          #+#    #+#             */
/*   Updated: 2021/01/28 11:44:56 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "gnl/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 


typedef struct s_inputs
{
	char *command;
	char *option;
	char **args;
	int  pipe;
	int	dir;
	struct s_inputs *next;
}           t_inputs;

typedef struct s_gargs
{
	int start;
	int  end;
	struct s_gargs *next;
}           t_gargs;

struct s_params
{
	char *command;
	char *option;
    char **args;
}	t_params;


void		lsh_loop();
void		lsh_read_line_and_trim(char **line);
void		write_string(char *s);
char		*ft_trim(char *line);
int 		len_without_speac(char *line);
char		**ft_split(char *s, char c);
char		*getword(char const *s, char c, int *i, char **sp);
int			wordlen(char const *s, char c, int start);
int			lenwords(char const *s, char c);
int 		number_of_words_in_table(char **s);
void		ft_lstadd_back(t_inputs **list_shell, t_inputs *new);
t_inputs	*ft_lstnew(char *command, char *option, char **args, int pipe);
void	ft_lstadd_back_arg(t_gargs **list_shell, t_gargs *new);
t_gargs *ft_lstnew_args(int start ,int  end);

#endif