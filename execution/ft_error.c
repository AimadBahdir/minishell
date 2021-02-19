/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:30:43 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/19 10:55:38 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short   errthrow(char *erp1, char *erp2, char *erp3, char *erp4)
{
    write(2, "bash: ", strlen("bash: "));
    if (erp1)
        write(2, erp1, ft_strlen(erp1));
    if (erp2)
        write(2, erp2, ft_strlen(erp2));
    if (erp3)
        write(2, erp3, ft_strlen(erp3));
    if (erp4)
        write(2, erp4, ft_strlen(erp4));
    write(2, "\n", 1);
    return (-1);
}