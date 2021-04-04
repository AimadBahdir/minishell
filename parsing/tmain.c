/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 08:17:04 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/04 13:54:43 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		print_node(t_stack **list_shell, int i, t_cargs **args2)
{
	t_stack	*ptr_list_shell;
	int		x;

	x = -1;
	ptr_list_shell = *list_shell;
	if (i > 0 && *list_shell != NULL)
	{
		while (ptr_list_shell)
		{
			if (i == ptr_list_shell->i)
			{
				while (ptr_list_shell->line[++x] != '\0')
					ft_lstcargsadd_back(args2,
					ft_lstcargsnew(ptr_list_shell->line[x]));
				write_string(ptr_list_shell->line);
				return (ft_strlen(ptr_list_shell->line));
			}
			ptr_list_shell = ptr_list_shell->next;
		}
	}
	return (0);
}

char	*get_word_t_cargs(t_cargs **args)
{
	t_cargs	*ptr_args;
	int		i;
	char	*ptr;

	i = 0;
	ptr = malloc(sizeof(char) * get_len_list(*args) + 1);
	ptr_args = *args;
	while (ptr_args != NULL)
	{
		ptr[i++] = ptr_args->c;
		ptr_args = ptr_args->next;
	}
	ptr[i] = '\0';
	return (ptr);
}

int		get_char(t_cargs **args, t_cargs **args2)
{
	char			c;
	int				total;
	struct termios	term;
	struct termios	init;

	tcgetattr(0, &term);
	tcgetattr(0, &init);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	total = 0;
	while (read(0, &c, 1) <= 0)
		;
	total += c;
	while (read(0, &c, 1) > 0)
		total += c;
	tcsetattr(0, TCSANOW, &init);
	if (t_params.check == 1)
	{
		t_params.input = 0;
		free_t_cargs(args);
		free_t_cargs(args2);
	}
	t_params.check = 0;
	return (total);
}

void	delete_change(void)
{
	char	*temp;

	temp = tgetstr("le", NULL);
	tputs(temp, 1, ft_puts);
	temp = tgetstr("ce", NULL);
	tputs(temp, 1, ft_puts);
}

char	*get_line(t_stack **stack)
{
	t_cargs	*args;
	t_cargs	*args2;

	args = t_params.str_c;
	args2 = t_params.str_c2;
	tgetent(NULL, getenv("TERM"));
	while (1)
	{
		t_params.c = get_char(&args, &args2);
		if (t_params.c >= 32 && t_params.c < 127)
			button_character(&t_params.ud_down, stack, &args2, &args);
		else if (t_params.c == 127 && t_params.input > 0)
			button_remove(&t_params.ud_down, stack, &args2, &args);
		else if (t_params.c == 183 && t_params.ud_down > 1)
			button_up(&t_params.ud_down, stack, &args2);
		else if (t_params.c == 184)
			button_down(&t_params.ud_down, stack, &args2, &args);
		else if (t_params.c == 10)
			return (button_enter(&t_params.ud_down, stack, &args2, &args));
		else if(t_params.c == 4 && t_params.input == 0)
			exit(0);//bdal sa tink
	}
}
