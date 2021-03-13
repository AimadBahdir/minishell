/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:21:26 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/13 16:39:48 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handel_c(int i)
{
	printf("(%d) ctrl + c\n", i);
}

void	handel_d(int i)
{
	printf("(%d) ctrl + d\n", i);
}

void	handel_b(int i)
{
	printf("(%d) ctrl + \\\n", i);
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
	inpt7->command[0] = ft_strdup("cat");
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
	inpt6->next = NULL;
	inpt5 = malloc(sizeof(*inpt5));
	inpt5->command = malloc(4 * sizeof(char *));
	inpt5->command[0] = ft_strdup("exit");
	inpt5->command[1] = ft_strdup("123");
	inpt5->command[2] = ft_strdup("123");
	inpt5->command[3] = NULL;
	inpt5->pipe = 0;
	inpt5->next = inpt6;
	inpt4 = malloc(sizeof(*inpt4));
	inpt4->command = malloc(5 * sizeof(char *));
	inpt4->command[0] = ft_strdup("echo");
	inpt4->command[1] = ft_strdup("$f2");
	inpt4->command[2] = ft_strdup("$f2");
	inpt4->command[3] = ft_strdup("-nnnnnnnn");
	inpt4->command[4] = NULL;
	inpt4->command[1][0] = 14;
	inpt4->command[2][0] = 14;
	inpt4->pipe = 0;
	inpt4->next = inpt5;
	inpt3 = malloc(sizeof(*inpt3));
	inpt3->command = malloc(3 * sizeof(char *));
	inpt3->command[0] = ft_strdup(">");
	inpt3->command[1] = ft_strdup("$f2$f2");
	inpt3->command[2] = NULL;
	inpt3->command[0][0] = 14;
	inpt3->command[1][3] = 24;
	inpt3->command[1][0] = 24;
	inpt3->pipe = 0;
	inpt3->next = inpt5;
	inpt2 = malloc(sizeof(*inpt2));
	inpt2->command = malloc(2 * sizeof(char *));
	inpt2->command[0] = ft_strdup("a.out/");
	inpt2->command[1] = NULL;
	inpt2->pipe = 0;
	inpt2->next = inpt3;
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
	ft_execute(&envlst, inpt);
}
