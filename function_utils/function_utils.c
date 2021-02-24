/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 18:22:25 by wben-sai          #+#    #+#             */
/*   Updated: 2021/02/11 09:31:03 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int number_of_words_in_table(char **s)
{
    int i;

    i = 0;
    if(s != NULL)
    {
        while(s[i] != NULL)
            i++;
    }
    return(i);
}

int ft_isnumber(char c)
{
    if(c >= '0' && c <= '9')
        return (1);
    return(0);
}