/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:01:06 by wben-sai          #+#    #+#             */
/*   Updated: 2021/02/23 15:06:34 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int len_without_speac(char *line)
{
	int i;
	int j;
	int len_line;

	i = 1;
	j = 0;
	len_line = strlen(line); // skar tink a3za
	while(line[len_line - i++] == ' ')
		j++;
	if(line[len_line - j - 1] == '\\')
		if(valid_option(line, len_line - j - 1) == 1)
			if(line[len_line - j] == ' ')
				j--;
	i = 0;
	while(line[i] != '\0' && line[i] == ' ')
		i++;
	return(len_line - j - i);
}


char		*ft_trim(char *line)
{
	int i;
	int len;
	int j;
	char *new_line;

	if(line == NULL)
		return(NULL);
	i = 0;
	len = len_without_speac(line);
	if(len < 0)
		len = 0;
	new_line = malloc(sizeof(char *) * len + 1);
	while(line[i] != '\0' && line[i] == ' ')
		i++;
	j = 0;
	while(len-- > 0)
	{
		new_line[j] = line[i];
		i++;
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}