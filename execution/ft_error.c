/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:30:43 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/17 16:03:14 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short   errthrow(char *erp1, char *erp2, char *erp3, char *erp4)
{
    ft_putstr("bash: ");
    if (erp1)
        ft_putstr(erp1);
    if (erp2)
        ft_putstr(erp2);
    if (erp3)
        ft_putstr(erp3);
    if (erp4)
        ft_putstr(erp4);
    ft_putstr("\n");
    return (-1);
}