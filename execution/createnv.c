/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createnv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:20:19 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/04 11:06:46 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env   *newenvelm(char *key, char *val)
{
	t_env   *newelm;

	if (!(newelm = malloc(sizeof(*newelm))))
		return (NULL);
    newelm->key = key;
    newelm->val = val;
	newelm->next = NULL;
	return (newelm);
}

void    envaddelm(t_env **lst, t_env *newelm)
{
	t_env   *e;

	if (*lst == NULL)
		*lst = newelm;
	else
	{
        e = *lst;
		while (e->next)
			e = e->next;
		e->next = newelm;
		newelm->next = NULL;
	}
}

void    ft_setenv(t_env **lst, char **envp)
{
    int i;
    int elen;
	int klen;

    i = -1;
    elen = 0;
	klen = 0;
    while (envp[++i])
    {
		elen = ft_strlen(envp[i]);
        klen = ft_lento(envp[i], '=') + 1;
        envaddelm(lst, newenvelm(ft_substr(envp[i], 0, (klen - 1)),
            ft_substr(envp[i], klen, (elen - klen))));
    }
}