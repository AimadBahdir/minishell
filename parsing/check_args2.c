/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:07:44 by wben-sai          #+#    #+#             */
/*   Updated: 2021/03/11 16:08:08 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*checkpath(char *s)
{
	t_cargs	*args;
	int		i;

	i = 0;
	args = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			i = checkpath_apostrophe(&args, s, i + 1);
		else if (s[i] == '\\')
			i = checkpath_backslash(&args, s, i + 1, 0);
		else if (s[i] == '\"')
			i = checkpath_quotation(&args, s, i + 1);
		else if (s[i] == '$')
			i = checkpath_dollar(&args, s, i + 1);
		else
			ft_lstcargsadd_back(&args, ft_lstcargsnew(s[i]));
		i++;
	}
	return (get_word_free(&args));
}

void	free_table_args(void)
{
	int i;

	i = 0;
	if (t_params.args != NULL)
	{
		while (t_params.args[i] != NULL)
			free(t_params.args[i++]);
		free(t_params.args);
	}
}

char	*get_word_free(t_cargs **args)
{
	t_cargs *ptr_args;
	t_cargs *ptr_args2;
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
	ptr_args2 = *args;
	while (ptr_args2 != NULL)
	{
		ptr_args = ptr_args2;
		ptr_args2 = ptr_args2->next;
		free(ptr_args);
	}
	return (ptr);
}
