/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:21:39 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/17 08:22:27 by abahdir          ###   ########.fr       */
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

typedef struct	s_inputs
{
	char			**command;
	short			pipe;
	struct s_inputs	*next;
}				t_inputs;

typedef struct	s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}				t_env;
int				g_cmdstat;

struct			s_pipe
{
	short	next;
	short	prev;
	int		nxtio[2];
	int		prvo;
	int		envio[2];
}				t_pipe;

struct			s_g
{
	char	**envp;
	char	*homepath;
	int		mystdout;
	int		mystdin;
	int		exstat;
	t_env	*explst;
}				t_g;

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
char			*ft_strlower(char *str);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(const char *s1, const char *set);
char			**ft_split(char const *s, char c);
short			ft_checkfor(char c, char *str);
short			ft_checkforstr(char *str, char **lst);
short			chk_directions(char **lst);
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
short			ft_execmd(t_env **lst, char **cmdargs);
short			ft_echo(char **args);
short			ft_env(t_env *e, char **args);
short			ft_pwd(t_env **e);
short			ft_export(t_env **e, char **args);
short			ft_exprint(void);
short			ft_unset(t_env **e, char **args);
short			ft_cd(t_env **e, char **args);
short			ft_exit(char **cmd);
short			ft_othercmd(t_env **lst, char **cmdargs);
short			ft_duptwo(int fd1, int fd2);
short			ft_pipe(void);
short			ft_setenvar(t_env *envlst, char **cmd);
void			ft_resetenv(t_env *lst);
char			**spltcmd(char **cmd);
short			gdirections(t_env **envlst, char **cmd);
short			ft_chkambigs(t_env *envlst, char **cmd,
							int pos, char **vars);
int				fillfile(t_env **envlst, char **cmd);
int				retfreetwo(char **tmp1, int ret);
int				retfree(char *tmp1, char *tmp2, int ret);
#endif
