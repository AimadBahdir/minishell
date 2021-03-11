/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 22:08:10 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/11 09:32:45 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	ft_lento(char *s, char c)
{
	size_t len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

size_t	ft_lentwop(char **s)
{
	size_t len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	ft_inputslen(t_inputs *lst)
{
	size_t len;

	len = 0;
	while (lst)
		len++;
	return (len);
}
