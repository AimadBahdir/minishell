/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createnv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:20:19 by abahdir           #+#    #+#             */
/*   Updated: 2021/03/18 08:42:12 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*newenvelm(char *key, char *val)
{
	t_env	*newelm;

	if (!(newelm = malloc(sizeof(*newelm))))
		return (NULL);
	if (ft_strcmp(key, "HOME"))
		t_g.homepath = ft_strdup(val);
	newelm->key = ft_strdup(key);
	newelm->val = ft_strdup(val);
	newelm->next = NULL;
	free(key);
	free(val);
	return (newelm);
}

void	envaddelm(t_env **lst, t_env *newelm)
{
	t_env	*e;

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

void	ft_setenv(t_env **lst, char **envp)
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
		envaddelm(&t_g.explst, newenvelm(ft_substr(envp[i], 0, (klen - 1)),
			ft_substr(envp[i], klen, (elen - klen))));
	}
}

void	ft_resetenv(t_env *lst)
{
	int		len;
	t_env	*head;
	char	*tmp;

	head = lst;
	len = 0;
	while (head && ++len)
		head = head->next;
	// if (t_g.envp != NULL)
	// 	retfreetwo(t_g.envp, 0);
	t_g.envp = malloc(sizeof(char *) * (len + 1));
	len = -1;
	while (lst)
	{
		tmp = ft_strjoin(lst->key, "=");
		t_g.envp[++len] = ft_strjoin(tmp, lst->val);
		free(tmp);
		lst = lst->next;
	}
	t_g.envp[++len] = 0;
}
