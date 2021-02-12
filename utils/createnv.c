/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createnv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:20:19 by abahdir           #+#    #+#             */
/*   Updated: 2021/02/03 18:26:31 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getenval(t_env *e, char *key)
{
	while (e)
	{
		if (ft_strcmp(ft_strlower(e->key), ft_strlower(key)))
			return (e->val);
		e = e->next;
	}
	return (NULL);
}

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