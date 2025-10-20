/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:48:45 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/20 17:35:48 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	add_env_var(t_list **head, t_list *new_nd)
{
	if (!*head)
		*head = new_nd;
	else
		ft_lstadd_back(head, new_nd);
}

char	*increase_shell_level(char *shell_var)
{
	int		lvl;
	char	*tmp;
	char	*new_lvl;

	lvl = ft_atoi(shell_var + 6);
	lvl++;
	tmp = ft_itoa(lvl);
	if (!tmp)
		return (malloc_err(), NULL);
	new_lvl = ft_strjoin("SHLVL=", tmp);
	if (!new_lvl)
		return (malloc_err(), NULL);
	free(tmp);
	return (new_lvl);
}

t_list	*env_dup(char **envp)
{
	int		i;
	char	*dup_var;
	t_list	*new_nd;
	t_list	*head;

	if (!envp)
		return (NULL);
	i = 0;
	head = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			dup_var = increase_shell_level(envp[i]);
		else
			dup_var = ft_strdup(envp[i]);
		if (!dup_var)
			return (ft_lstclear(&new_nd, del_char_ptr), NULL);
		new_nd = ft_lstnew(dup_var);
		if (!new_nd)
			return (ft_lstclear(&new_nd, del_char_ptr), NULL);
		add_env_var(&head, new_nd);
		i++;
	}
	return (head);
}
