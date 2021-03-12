/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:26:39 by wben-sai          #+#    #+#             */
/*   Updated: 2021/03/12 10:44:42 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_list(t_inputs *list_shell)
{
	int			i;
	int			j;
	t_inputs	*ptr_list_shell;

	j = 0;
	//alo aimad han timlilay aya list_shell
	printf("**************************\n");
	ptr_list_shell = list_shell;
	while (ptr_list_shell != NULL)
	{
		printf("--------------------------\n");
		j = 0;
		while (ptr_list_shell->command[j] != NULL)
		{
			printf("command : |%s|\n", ptr_list_shell->command[j]);
			j++;
		}
		printf("pipe : %d\n", ptr_list_shell->pipe);
		printf("--------------------------\n");
		ptr_list_shell = ptr_list_shell->next;
	}
	printf("**************************\n");
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

void	lsh_loop(void)
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
			if (check_line(&line, &list_shell) == 1)
				continue;
		}
		free(line);
	}
}

int		main(int argc, char **argv, char **envp)
{
	lsh_loop();
	return (0);
}
