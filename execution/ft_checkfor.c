/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkfor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 08:55:32 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/09 09:28:13 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short   ft_checkfor(char c, char *str)
{
    int i;

    i = -1;
    if (!str)
        return (-1);
    while (str[++i])
        if (str[i] == c)
            return (1);
    return (0);
}

short   ft_checkforstr(char *str, char **lst)
{
    int i;

    i = -1;
    if (!lst || !str)
        return (-1);
    while (lst[++i])
        if (ft_strcmp(str, lst[i]))
            return (1);
    return (0);
}