/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:55:50 by abahdir           #+#    #+#             */
/*   Updated: 2021/04/06 10:35:27 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ns;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	if (i < start)
		return (ft_strdup(""));
	i -= start;
	len = ft_ternint(i < len, i, len);
	ns = malloc(len * sizeof(char) + 1);
	if (ns == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
		ns[i++] = s[start++];
	ns[i] = '\0';
	return (ns);
}
