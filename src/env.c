/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:48:45 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 18:24:09 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*create_content_env_nd(char **envp, int *i, t_bool *shlvl_founded)
{
	char	*dup_var;

	dup_var = NULL;
	if ((envp && ft_strncmp(envp[*i], "SHLVL=", 6) == 0) || !envp)
	{
		if (envp)
			dup_var = increase_shell_level(envp[*i]);
		else
			dup_var = increase_shell_level(NULL);
		*shlvl_founded = TRUE;
	}
	else
		dup_var = ft_strdup(envp[*i]);
	if (!dup_var)
		return (NULL);
	return (dup_var);
}

t_list	*is_env(char **envp, t_list **head, t_bool *shlvl_founded)
{
	int		i;
	char	*tmp;
	t_list	*new_nd;

	i = 0;
	while (envp[i])
	{
		tmp = create_content_env_nd(envp, &i, shlvl_founded);
		if (!tmp)
			return (ft_lstclear(&new_nd, del_char_ptr), NULL);
		new_nd = ft_lstnew(tmp);
		if (!new_nd)
			return (ft_lstclear(&new_nd, del_char_ptr), NULL);
		if (!*head)
			*head = new_nd;
		else
			ft_lstadd_back(head, new_nd);
		i++;
	}
	return (*head);
}

t_list	*env_dup(char **envp)
{
	t_list	*head;
	t_bool	shlvl_founded;

	head = NULL;
	shlvl_founded = FALSE;
	if (envp)
	{
		is_env(envp, &head, &shlvl_founded);
		if (!head)
			return (NULL);
	}
	if (shlvl_founded == FALSE || !envp)
	{
		is_not_shlvl(&head, &shlvl_founded);
		if (!head)
			return (NULL);
	}
	return (head);
}

t_state	env_mng(t_env *mini_env, char **envp)
{
	mini_env->vars = env_dup(envp);
	if (!mini_env->vars)
		return (ST_ERR_MALLOC);
	mini_env->r = 0;
	return (ST_OK);
}
