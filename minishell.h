/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:12:49 by wben-sai          #+#    #+#             */
/*   Updated: 2021/03/08 11:58:25 by wben-sai         ###   ########.fr       */
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
	char **env;
	int question_nbr;
	char *error_text;
	int i;
	int type_cute_line;
	int vld_der;
}	t_params;

typedef struct  s_env
{
    char            *key;
    char            *val;	
    struct s_env    *next;
}               t_env;

void		lsh_loop();
int		lsh_read_line_and_trim(char **line);
void		write_string(char *s);
char		*ft_trim(char *line);
int 		len_without_speac(char *line);
char		**ft_split(char *s, char c);
char		*getword(char const *s, char c, int *i, char **sp);
int			wordlen(char const *s, char c, int start);
int			lenwords(char const *s, char c);
int 		number_of_words_in_table(char **s);
void		ft_lstadd_back(t_inputs **list_shell, t_inputs *new);
t_inputs	*ft_lstnew(char **command, short pipe);
void		ft_lstadd_back_arg(t_gargs **list_shell, t_gargs *new);
t_gargs 	*ft_lstnew_args(int start ,int  end, int vld_der);
void		echonge_list_args(t_gargs **lst);
void		echonge(int *start1, int *end1, int *start2, int *end2);
int 		get_number_args(t_gargs **gargs);
void		ft_lstcargsadd_back(t_cargs **list_shell, t_cargs *new);
t_cargs			*ft_lstcargsnew(char c);
t_env           *newenvelm(char *key, char *val);
void            envaddelm(t_env **lst, t_env *newelm);
void            ft_setenv(t_env **lst, char **envp);
char            *getenval(t_env *e, char *key);
size_t          ft_strlen(const char *s);
size_t          ft_lento(char *s, char c);
short           ft_strcmp(char *s1, char *s2);
void            ft_putstr(char *str);
void            ft_putmstr(char **mstr, char spr);
char            *ft_strlower(char *str);
char            *ft_strdup(const char *s1);
char            *ft_strjoin(char const *s1, char const *s2);
char            *ft_substr(char const *s, unsigned int start, size_t len);
int	get_len_list(t_cargs *lst);
int ft_isnumber(char c);
int cut_apostrophe(int start_arg, char *line, int end);
int cut_quotation(int start_arg, char *line, int end);
int greater_less(int start_arg, char *line);
int valid_option(char *line , int start);
int cut_outher(int start_arg, char *line, int end, int *i);
char		*ft_itoa(int n);
char *fill_arg(int len, int start, char *line, int vld_der);
void free_table_args();
void	echongevld_der(int *vld_der, int *vld_der2);
void gestion_fill_arg(t_gargs *gargs, char *line, int len);
int ft_alpha(char c);
char *checkpath(char *s);
int checkpath_dollar(t_cargs **args, char *s, int i);
int check_syntax(char *line);
#endif
