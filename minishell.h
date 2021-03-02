/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:21:39 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/02 10:50:49 by abahdir          ###   ########.fr       */
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
# include <errno.h>

typedef struct s_inputs
{
	char			**command;
	short			pipe;
	struct s_inputs	*next;
}				t_inputs;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}				t_env;
int				g_cmdstat;

struct s_pipe
{
	short	next;
	short	prev;
	int		nxtio[2];
	int		prvo;
}		t_pipe;

struct	s_g
{
	char	**envp;
	char	*homepath;
	int		stdinpt;
	int		stdoutpt;
	int		mystdout;
	int		mystdin;
	int		exstat;
}		t_g;


size_t			ft_strlen(const char *s);
size_t			ft_lento(char *s, char c);
size_t			ft_lentwop(char **s);
size_t			ft_inputslen(t_inputs *lst);
size_t			ft_envlen(t_env *lst);
short			ft_strcmp(char *s1, char *s2);
void			ft_putstr(char *str);
void			ft_putmstr(char **mstr, char spr);
short			ft_strnormed(char *str);
char			*ft_strlower(char *str);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
short			ft_checkfor(char c, char *str);
short			ft_checkforstr(char *str, char **lst);
short			chk_directions(char **lst);
short			errthrow(char *erp1, char *erp2, char *erp3, int errcode);
void			ft_stdrst(int fd);
t_env			*newenvelm(char *key, char *val);
void			envaddelm(t_env **lst, t_env *newelm);
void			setenval(t_env **lst, char *key, char *val);
void			rmenval(t_env **lst, char *key);
void			ft_setenv(t_env **lst, char **envp);
char			*getenval(t_env *e, char *key);
short			ft_execute(t_env **envlst, t_inputs *cmdlst);
short			ft_execmd(t_env **lst, char **cmdargs);
short			ft_echo(char **args);
short			ft_env(t_env *e, char **args);
short			ft_pwd(t_env **e, char **args);
short			ft_export(t_env **e, char **args);
short			ft_exprint(t_env *head);
short			ft_unset(t_env **e, char **args);
short			ft_cd(t_env **e, char **args);
short			ft_duptwo(int fd1, int fd2);
short			ft_pipe(void);
short			gdirections(t_env **envlst, char **cmd);
int				fillfile(t_env **envlst, char **cmd);

#endif
