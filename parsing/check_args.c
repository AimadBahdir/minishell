/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:58:53 by wben-sai          #+#    #+#             */
/*   Updated: 2021/04/08 17:17:40 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkpath_apostrophe(t_cargs **args, char *s, int i)
{
	while (s[i] != '\0' && s[i] != '\'')
	{
		ft_lstcargsadd_back(args, ft_lstcargsnew(s[i]));
		i++;
	}
	return (i);
}

int	checkpath_backslash(t_cargs **args, char *s, int i, int in_quotation)
{
	if (in_quotation == 1)
	{
		if (s[i] != '\"' && s[i] != '\\' && s[i] != '$')
			ft_lstcargsadd_back(args, ft_lstcargsnew('\\'));
	}
	ft_lstcargsadd_back(args, ft_lstcargsnew(s[i]));
	return (i);
}

int	checkpath_quotation(t_cargs **args, char *s, int i)
{
	while (1)
	{
		if (s[i] == '\"' && valid_option(s, i) == 1)
			break ;
		else if (s[i] == '\\')
			i = checkpath_backslash(args, s, i + 1, 1);
		else if (s[i] == '$')
			i = checkpath_dollar(args, s, i + 1);
		else
			ft_lstcargsadd_back(args, ft_lstcargsnew(s[i]));
		i++;
	}
	return (i);
}

int	checkpath_question_mark(t_cargs **args, int i)
{
	ft_lstcargsadd_back(args, ft_lstcargsnew(24));
	ft_lstcargsadd_back(args, ft_lstcargsnew('?'));
	return (i);
}

int	checkpath_dollar(t_cargs **args, char *s, int i)
{
	if (s[i] == '?')
		return (checkpath_question_mark(args, i));
	else if (ft_isnumber(s[i]) == 0 && ft_alpha(s[i]) == 0 && s[i] != '_')
	{
		ft_lstcargsadd_back(args, ft_lstcargsnew('$'));
		return (i - 1);
	}
	else if (ft_isnumber(s[i]) == 1)
		return (i);
	else if (ft_alpha(s[i]) == 1 || s[i] == '_')
		ft_lstcargsadd_back(args, ft_lstcargsnew(24));
	ft_lstcargsadd_back(args, ft_lstcargsnew(s[i]));
	return (i);
}
