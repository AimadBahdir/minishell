/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:21:26 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/19 12:34:22 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	signals_handler(int sig)
{
	int exstat;

	if (t_g.iscmd == 0)
		write(1, "\b\b", 2);
	if (sig == SIGINT && !t_g.iscmd)
	{
		if (t_params.was_read != NULL)
		{
			free(t_params.was_read);
			t_params.was_read = NULL;
		}
		write_string("\nminibash-1.0$ ");
	}
	else if (sig == SIGQUIT && t_g.iscmd > 0)
	{
		wait(&exstat);
		if (WIFEXITED(exstat))
			t_g.exstat = WEXITSTATUS(exstat);
		if (t_g.iscmd == 2)
			ft_putstr("Quit: 3", 1);
	}
}


int		main(int argc, char **argv, char **envp)
{
	t_env		*envlst;
	t_inputs	*inpt;
	t_inputs	*inpt1;
	t_inputs	*inpt2;
	t_inputs	*inpt3;
	t_inputs	*inpt4;
	t_inputs	*inpt5;
	t_inputs	*inpt6;
	t_inputs	*inpt7;

	argv = NULL;
	argc = 0;
	signal(SIGINT, handel_c);
	signal(SIGQUIT, handel_b);
	envlst = NULL;
	t_g.envp = NULL;
	ft_setenv(&envlst, envp);
	inpt7 = malloc(sizeof(*inpt7));
	inpt7->command = malloc(2 * sizeof(char *));
	inpt7->command[0] = ft_strdup("pwd");
	inpt7->command[1] = NULL;
	inpt7->pipe = 0;
	inpt7->next = NULL;
	inpt6 = malloc(sizeof(*inpt6));
	inpt6->command = malloc(3 * sizeof(char *));
	inpt6->command[0] = ft_strdup("echo");
	inpt6->command[1] = ft_strdup("$?");
	inpt6->command[2] = NULL;
	inpt6->command[1][0] = 24;
	inpt6->pipe = 0;
	inpt6->next = inpt7;
	inpt5 = malloc(sizeof(*inpt5));
	inpt5->command = malloc(4 * sizeof(char *));
	inpt5->command[0] = ft_strdup("cd");
	inpt5->command[1] = ft_strdup("-");
	inpt5->command[2] = ft_strdup("123");
	inpt5->command[3] = NULL;
	inpt5->pipe = 0;
	inpt5->next = inpt6;
	inpt4 = malloc(sizeof(*inpt4));
	inpt4->command = malloc(5 * sizeof(char *));
	inpt4->command[0] = ft_strdup("echo");
	inpt4->command[1] = ft_strdup("ads$f2");
	inpt4->command[2] = ft_strdup("$f2");
	inpt4->command[3] = ft_strdup("-nnnnnnnn");
	inpt4->command[4] = NULL;
	inpt4->command[1][3] = 24;
	inpt4->command[2][0] = 24;
	inpt4->pipe = 0;
	inpt4->next = inpt5;
	inpt3 = malloc(sizeof(*inpt3));
	inpt3->command = malloc(9 * sizeof(char *));
	inpt3->command[0] = ft_strdup(">");
	inpt3->command[1] = ft_strdup("abc");
	inpt3->command[2] = ft_strdup(">");
	inpt3->command[3] = ft_strdup("def");
	inpt3->command[4] = ft_strdup(">");
	inpt3->command[5] = ft_strdup("asdf$f2");
	inpt3->command[6] = ft_strdup(">");
	inpt3->command[7] = ft_strdup("ijk");
	inpt3->command[8] = NULL;
	inpt3->command[0][0] = 14;
	inpt3->command[2][0] = 14;
	inpt3->command[4][0] = 14;
	inpt3->command[6][0] = 14;
	inpt3->command[5][4] = 24;
	inpt3->command[5][0] = 24;
	inpt3->pipe = 0;
	inpt3->next = inpt4;
	inpt2 = malloc(sizeof(*inpt2));
	inpt2->command = malloc(2 * sizeof(char *));
	inpt2->command[0] = ft_strdup("cd");
	inpt2->command[1] = NULL;
	inpt2->pipe = 0;
	inpt2->next = inpt5;
	inpt1 = malloc(sizeof(*inpt1));
	inpt1->command = malloc(4 * sizeof(char *));
	inpt1->command[0] = ft_strdup("chmod");
	inpt1->command[1] = ft_strdup("777");
	inpt1->command[2] = ft_strdup("aa.tst");
	inpt1->command[3] = NULL;
	inpt1->pipe = 0;
	inpt1->next = inpt2;
	inpt = malloc(sizeof(*inpt));
	inpt->command = malloc(4 * sizeof(char *));
	inpt->command[0] = ft_strdup("export");
	inpt->command[1] = ft_strdup("f=dsg");
	inpt->command[2] = ft_strdup("f2=");
	inpt->command[3] = NULL;
	// inpt->command[1][0] = 14;
	inpt->pipe = 0;
	inpt->next = inpt2;
	ft_execute(&envlst, inpt2);
}
