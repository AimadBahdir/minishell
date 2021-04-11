/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_click.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 13:18:30 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/08 17:24:48 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*button_enter(int *up_dwn, t_stack **stk, t_cargs **arg2, t_cargs **arg)
{
	if (*up_dwn <= get_len_list_stack(*stk) && *up_dwn != 0)
	{
		t_params.temp = get_word_free(arg2);
		if (*arg != NULL)
			free_t_cargs(arg);
	}
	else
	{
		t_params.temp = get_word_free(arg);
		if (*arg2 != NULL)
			free_t_cargs(arg2);
	}
	if (t_params.input != 0)
	{
		ft_lststackadd_back(stk, ft_lststacknew(t_params.temp, t_params.i++));
		*up_dwn = t_params.i;
		t_params.input = 0;
		return (ft_strdup(t_params.temp));
	}
	else
	{
		retfree(t_params.temp, NULL, 0);
		t_params.input = 0;
		return (ft_strdup(""));
	}
}

void	button_down(int *up_dwn, t_stack **stack, t_cargs **arg2, t_cargs **arg)
{
	if (*up_dwn < get_len_list_stack(*stack))
	{
		*up_dwn += 1;
		while (t_params.input > 0)
		{
			t_params.input--;
			delete_change();
		}
		free_t_cargs(arg2);
		t_params.input = print_node(stack, *up_dwn, arg2);
	}
	else if (*up_dwn == get_len_list_stack(*stack))
	{
		*up_dwn += 1;
		while (t_params.input > 0)
		{
			t_params.input--;
			delete_change();
		}
		free_t_cargs(arg2);
		t_params.temp = get_word_t_cargs(arg);
		write_string(t_params.temp);
		t_params.input = ft_strlen(t_params.temp);
		retfree(t_params.temp, NULL, 0);
	}
}

void	button_remove(int *up_dwn, t_stack **stack,
t_cargs **args2, t_cargs **args)
{
	if (t_params.input > 0)
	{
		if (*up_dwn <= get_len_list_stack(*stack) && *up_dwn != 0)
			lastnodedeletion(args2);
		else
			lastnodedeletion(args);
		delete_change();
		t_params.input--;
	}
}

void	button_up(int *up_dwn, t_stack **stack, t_cargs **args2)
{
	*up_dwn -= 1;
	while (t_params.input > 0)
	{
		t_params.input--;
		delete_change();
	}
	free_t_cargs(args2);
	t_params.input = print_node(stack, *up_dwn, args2);
}

void	button_character(int *up_dwn, t_stack **stack,
t_cargs **args2, t_cargs **args)
{
	t_params.input += write(1, &t_params.c, 1);
	if (*up_dwn <= get_len_list_stack(*stack) && *up_dwn != 0)
	{
		ft_lstcargsadd_back(args2, ft_lstcargsnew(t_params.c));
	}
	else
	{
		ft_lstcargsadd_back(args, ft_lstcargsnew(t_params.c));
	}
}
