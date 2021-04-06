/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:12:49 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/06 10:57:00 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <term.h>
# include <termcap.h>

typedef struct s_inputs
{
	char			**command;
	short			pipe;
	struct s_inputs	*next;
}	t_inputs;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

struct s_pipe
{
	short	next;
	short	prev;
	int		nxtio[2];
	int		prvo;
	int		envio[2];
}	t_pipe;

struct s_g
{
	char	**envp;
	char	*homepath;
	int		mystdout;
	int		mystdin;
	int		exstat;
	short	iscmd;
	int		indx;
	int		err;
	char	**cmd;
	char	*path;
	int		kl;
	char	*tmp;
	char	*oldpwd;
	char	*pwd;
	short	haspace;
	t_env	*explst;
}	t_g;

typedef struct s_gargs
{
	int				start;
	int				end;
	int				vld_der;
	struct s_gargs	*next;
}	t_gargs;

typedef struct s_cargs
{
	char			c;
	struct s_cargs	*next;
}	t_cargs;

struct s_params
{
	char	**args;
	char	*error_text;
	int		vld_der;
	char	*was_read;
	char	*temp;
	int		c;
	int		i;
	int		input;
	int		ud_down;
	t_cargs	*str_c;
	t_cargs	*str_c2;
	int		total;
	int		check;
	int		index;
}	t_params;

typedef struct s_stack
{
	char			*line;
	int				i;
	struct s_stack	*next;
}	t_stack;

int				checkpath_apostrophe(t_cargs **args, char *s, int i);
int				checkpath_backslash(t_cargs **args, char *s, int i,
					int in_quotation);
int				checkpath_quotation(t_cargs **args, char *s, int i);
int				checkpath_question_mark(t_cargs **args, int i);
int				checkpath_dollar(t_cargs **args, char *s, int i);
char			*checkpath(char *s);
void			free_table_args(void);
char			*get_word_free(t_cargs **args);
int				error_msg(void);
int				check_syntax_redirection(char *line, int i);
int				get_end_index(char *line, int i);
int				check_syntax(char *line);
int				check_syntax_line(char *line, int i);
int				greater_less(int start_arg, char *line);
int				cut_apostrophe(int start, char *line, int end);
int				cut_outher(int start_arg, char *line, int end, int *i);
int				cut_quotation(int start, char *line, int end);
void			gestion_fill_arg(t_gargs *gargs, char *line, int len);
int				get_start_and_end_args(char *lne, t_inputs **list_shell);
int				get_end_arg(int start_arg, char *line, int end);
int				gestion_args(char *line, int start, int end, t_gargs **gargs);
char			*fill_arg(int len, int start, char *line, int vldder);
int				get_args(char *line, int start, int end, int norm);
void			check_more(t_gargs *gargs, char *line, int len, int norm);
int				lsh_split_line(char *line, t_inputs **list_shell);
int				get_param_list_shell(char *line, int start, int end);
int				new_check(char **line2);
int				join_new_line_check_read_more(char **line, char **line2);
int				lsh_read_line_and_trim(char **line, t_stack **stack);
int				check_line(t_env **envlst, char **line, t_inputs **list_shell);
int				number_of_derc_in_table(char **s);
int				is_nbr_car(char c);
void			write_string(char *s);
int				pass_spe(char *line, int i);
t_cargs			*ft_lstcargsnew(char c);
void			ft_lstcargsadd_back(t_cargs **list_shell, t_cargs *new);
t_inputs		*ft_lstnew(char **command, short pipe);
t_gargs			*ft_lstnew_args(int start, int end, int vld_der);
void			ft_lstadd_back(t_inputs **list_shell, t_inputs *new);
void			ft_lstadd_back_arg(t_gargs **list_shell, t_gargs *new);
void			change_position(t_gargs **gargs, int i);
void			echonge_list_args(t_gargs **lst);
void			echonge(int *start1, int *end1, int *start2, int *end2);
int				get_len_list(t_cargs *lst);
void			echongevld_der(int *vld_der, int *vld_der2);
int				get_number_args(t_gargs **gargs);
int				check_syntax_list(t_inputs *list_shell);
int				valid_option(char *line, int start);
void			lsh_loop(t_env **envlst);
void			exe_list(t_env **envlst, t_inputs *list_shell);
char			*get_line(t_stack **stack);
t_stack			*ft_lststacknew(char *line, int i);
void			ft_lststackadd_back(t_stack **list_shell, t_stack *new);
int				get_len_list_stack(t_stack *lst);
void			lastnodedeletion(t_cargs **lst);
void			free_t_cargs(t_cargs **args);
char			*get_word_t_cargs(t_cargs **args);
int				print_node(t_stack **list_shell, int i, t_cargs **args2);
int				get_char(t_cargs **args, t_cargs **args2);
int				ft_puts(int d);
void			delete_change(void);
char			*button_enter(int *ud_down, t_stack **stack,
					t_cargs **args2, t_cargs **args);
void			button_down(int *ud_down, t_stack **stack,
					t_cargs **args2, t_cargs **args);
void			button_remove(int *ud_down, t_stack **stack,
					t_cargs **args2, t_cargs **args);
void			button_up(int *ud_down, t_stack **stack, t_cargs **args2);
void			button_character(int *ud_down, t_stack **stack,
					t_cargs **args2, t_cargs **args);
int				ft_isnumber(char c);
int				ft_alpha(char c);
char			*ft_trim(char *line);
size_t			ft_strlen(const char *s);
size_t			ft_lento(char *s, char c);
size_t			ft_lentwop(char **s);
size_t			ft_inputslen(t_inputs *lst);
short			ft_strcmp(char *s1, char *s2);
void			ft_putstr(char *str, short nl);
void			ft_putmstr(char **mstr, char spr);
short			ft_strnormed(char *str);
int				ft_isalpha(int c);
char			*ft_itoa(int n);
short			ft_isnum(char *str);
int				ft_atoi(const char *str);
void			ft_strlower(char *str);
char			*ft_strdup(const char *s1);
short			ft_dupcmd(char **str);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(const char *s1, const char *set);
char			**ft_split(char const *s, char c);
short			ft_checkfor(char c, char *str);
short			ft_checkforstr(char *str, char **lst);
short			chk_directions(void);
short			ft_creatfiles(char **cmd, int stop);
int				ft_open(char *name, int flags, short out);
short			errthrow(char *erp1, char *erp2, char *erp3, int errcode);
int				ft_ternint(short cond, int iftrue, int iffalse);
char			*ft_ternchar(short cond, char *iftrue, char *iffalse);
void			ft_stdrst(int fd);
t_env			*newenvelm(char *key, char *val);
void			envaddelm(t_env **lst, t_env *newelm);
void			setenval(t_env **lst, char *key, char *val);
void			rmenval(t_env **lst, char *key);
void			ft_setenv(t_env **lst, char **envp);
char			*getenval(t_env *e, char *key);
short			ft_setoldcmd(t_env **lst, char *cmdpath);
short			ft_execute(t_env **envlst, t_inputs *cmdlst);
short			ft_execmd(t_env **lst);
short			ft_echo(void);
short			ft_env(t_env *e);
short			ft_pwd(t_env **e, short get);
void			ft_setoldpwd(t_env **e);
short			ft_export(t_env **e);
short			ft_exprint(void);
short			ft_unset(t_env **e);
short			ft_cd(t_env **e);
short			ft_exit(void);
short			ft_othercmd(t_env **lst);
short			ft_duptwo(int fd1, int fd2);
short			ft_pipe(void);
short			ft_setenvar(t_env *envlst, char **cmd);
void			ft_resetenv(t_env *lst);
char			**spltcmd(void);
short			gdirections(t_env **envlst);
short			ft_chkambigs(t_env *envlst, int *pos, char **vars);
char			*spltandgenv(t_env *envlst, char *cmd);
int				fillfile(t_env **envlst);
int				retfreetwo(char **tmp1, int ret);
int				retfree(char *tmp1, char *tmp2, int ret);
char			*ft_getvar(t_env *envlst, char **spltd, short first);
void			signals_handler(int sig);
void			ft_closestd(void);
#endif
