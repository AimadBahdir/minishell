/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:12:49 by wben-sai          #+#    #+#             */
/*   Updated: 2021/03/12 11:24:07 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "gnl/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h> 


typedef struct s_inputs
{
	char **command;
	short  pipe;
	struct s_inputs *next;
}           t_inputs;

typedef struct s_gargs
{
	int start;
	int  end;
	int vld_der;
	struct s_gargs *next;
}           t_gargs;

typedef struct s_cargs
{
	char c;
	struct s_cargs *next;
}           t_cargs;

struct s_params
{
    char **args;
	char *error_text;
	int vld_der;
}	t_params;


int			len_without_speac(char *line);
char		*ft_trim(char *line);


int 		ft_alpha(char c);
int 		ft_isnumber(char c);
int			checkpath_apostrophe(t_cargs **args, char *s, int i);
int			checkpath_backslash(t_cargs **args, char *s, int i, int in_quotation);
int			checkpath_quotation(t_cargs **args, char *s, int i);
int			checkpath_question_mark(t_cargs **args, int i);
int			checkpath_dollar(t_cargs **args, char *s, int i);
char		*checkpath(char *s);
void		free_table_args(void);
char		*get_word_free(t_cargs **args);
int			error_msg(void);
int			check_syntax_redirection(char *line, int i);
int			get_end_index(char *line, int i);
int			check_syntax(char *line);
int			check_syntax_line(char *line, int i);
int			greater_less(int start_arg, char *line);
int			cut_apostrophe(int start, char *line, int end);
int			cut_outher(int start_arg, char *line, int end, int *i);
int			cut_quotation(int start, char *line, int end);
void		gestion_fill_arg(t_gargs *gargs, char *line, int len);
int			get_start_and_end_args(char *lne, t_inputs **list_shell);
int			get_end_arg(int start_arg, char *line, int end);
int			gestion_args(char *line, int start, int end, t_gargs **gargs);
char		*fill_arg(int len, int start, char *line, int vldder);
int			get_args(char *line, int start, int end, int norm);
void		check_more(t_gargs *gargs, char *line, int len, int norm);
int			lsh_split_line(char *line, t_inputs **list_shell);
int			get_param_list_shell(char *line, int start, int end);
int			new_check(char **line2);
int			join_new_line_check_read_more(char **line, char **line2);
int			read_more(char **line);
int			lsh_read_line_and_trim(char **line);
int			check_line(char **line, t_inputs **list_shell);
int 		number_of_words_in_table(char **s);
int			is_nbr_car(char c);
void		write_string(char *s);
int			pass_spe(char *line, int i);
t_cargs		*ft_lstcargsnew(char c);
void		ft_lstcargsadd_back(t_cargs **list_shell, t_cargs *new);
t_inputs	*ft_lstnew(char **command, short pipe);
t_gargs 	*ft_lstnew_args(int start ,int  end, int vld_der);
void		ft_lstadd_back(t_inputs **list_shell, t_inputs *new);
void		ft_lstadd_back_arg(t_gargs **list_shell, t_gargs *new);
void		change_position(t_gargs **gargs, int i);
void		echonge_list_args(t_gargs **lst);
void		echonge(int *start1, int *end1, int *start2, int *end2);
int			get_len_list(t_cargs *lst);
void		echongevld_der(int *vld_der, int *vld_der2);
int			get_number_args(t_gargs **gargs);
int			check_syntax_list(t_inputs *list_shell);
int			valid_option(char *line, int start);
void		lsh_loop(void);
void		exe_list(t_inputs *list_shell);

#endif
