/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:26:39 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/06 10:04:28 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_list(t_env **envlst, t_inputs *list_shell)
{
	int			i;
	int			j;
	t_inputs	*ptr_list_shell;

	j = 0;
	write_string("\n");
	ft_execute(envlst, list_shell);
	ptr_list_shell = list_shell;
	while (list_shell != NULL)
	{
		i = 0;
		while (list_shell->command[i] != NULL)
			free(list_shell->command[i++]);
		free(list_shell->command);
		ptr_list_shell = list_shell;
		list_shell = list_shell->next;
		free(ptr_list_shell);
	}
}

void	signals_handler(int sig)
{
	int	exstat;

	if (sig == SIGINT && !t_g.iscmd)
	{
		t_params.check = 1;
		t_params.input = 0;
		write_string("\nminibash-1.0$ ");
	}
	else if (sig == SIGQUIT && t_g.iscmd > 0)
	{
		wait(&exstat);
		if (WIFEXITED(exstat))
			t_g.exstat = WEXITSTATUS(exstat);
		if (t_g.iscmd == 2)
		{
			ft_putstr("Quit: 3", 1);
			t_g.exstat = 131;
		}
		else if (t_g.iscmd == 1)
			t_g.exstat = 255;
	}
}

void	lsh_loop(t_env **envlst)
{
	char		*line;
	t_inputs	*list_shell;
	t_stack		*stack;

	t_params.input = 0;
	t_params.ud_down = 0;
	t_params.i = 1;
	stack = NULL;
	list_shell = NULL;
	while (1)
	{
		t_g.iscmd = 0;
		write_string("minibash-1.0$ ");
		if (lsh_read_line_and_trim(&line, &stack) == -1)
			write_string("minibash: syntax Error\n");
		else if (line[0] != '\0')
		{
			if (check_line(envlst, &line, &list_shell) == 1)
				continue ;
		}
		else if (line[0] == '\0')
			write_string("\n");
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envlst;

	argv = NULL;
	argc = 0;
	t_g.haspace = 0;
	t_g.cmd = NULL;
	envlst = NULL;
	t_g.envp = NULL;
	t_params.str_c = NULL;
	t_params.str_c2 = NULL;
	ft_setenv(&envlst, envp);
	t_params.check = 0;
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, signals_handler);
	lsh_loop(&envlst);
	while (envlst)
	{
		free(envlst->key);
		free(envlst->val);
		envlst = envlst->next;
	}
	return (retfreetwo(t_g.envp, 0));
}
