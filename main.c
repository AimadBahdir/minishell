/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:21:26 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/15 11:34:58 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_list(t_env **envlst, t_inputs *list_shell)
{
	int			i;
	int			j;
	t_inputs	*ptr_list_shell;

	j = 0;
	// (void)envlst;
	ptr_list_shell = list_shell;
	while (ptr_list_shell != NULL)
	{
		j = 0;
		printf("command : ");
		while (ptr_list_shell->command[j] != NULL)
		{
			printf("%s ", ptr_list_shell->command[j]);
			j++;
		}
		printf("| pipe : %d", ptr_list_shell->pipe);
		ptr_list_shell = ptr_list_shell->next;
	}
	printf("\n------------------------------\n");
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

void	lsh_loop(t_env **envlst)
{
	char		*line;
	t_inputs	*list_shell;

	list_shell = NULL;
	while (1)
	{
		write_string("bash-1.0$ ");
		if (lsh_read_line_and_trim(&line) == -1)
			write_string("bash: syntax Error\n");
		else if (read_more(&line) == -1)
			write_string("bash: syntax Error\n");
		else if (line[0] != '\0')
		{
			if (check_line(envlst, &line, &list_shell) == 1)
				continue;
		}
		free(line);
	}
}

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
	argv = NULL;
	argc = 0;
	// signal(SIGINT, handel_c);
	// signal(SIGQUIT, handel_b);
	// int fdstdin;

	// fdstdin = dup(STDIN_FILENO);
	t_env *envlst;
	envlst = NULL;
	t_g.envp = NULL;
	ft_setenv(&envlst, envp);
	lsh_loop(&envlst);
	while (envlst)
	{
		free(envlst->key);
		free(envlst->val);
		envlst = envlst->next;
	}
	return (0);
}
