/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:48:45 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/24 17:26:18 by mcuenca-         ###   ########.fr       */
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
	long int	lvl;
	char		b[12];
	char		*new_lvl;

	if (shell_var == NULL || (shell_var && is_overflow(shell_var)))
		lvl = 0;
	else
	{
		lvl = ft_atoi(shell_var + 6);
		if (lvl + 1 > 2147483647 || lvl < 0)
			lvl = 0;
		else
			lvl++;
	}
	ft_static_itoa(b, 12, lvl);
	new_lvl = ft_strjoin("SHLVL=", b);
	if (!new_lvl)
		return (malloc_err(), NULL);
	return (new_lvl);
}

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

t_list	*is_not_shlvl(t_list **head, t_bool *shlvl_founded)
{
	t_list	*new_nd;
	char	*shlvl;

	shlvl = create_content_env_nd(NULL, 0, shlvl_founded);
	if (!shlvl)
		return (NULL);
	new_nd = ft_lstnew(shlvl);
	if (!new_nd)
		return (ft_lstclear(&new_nd, del_char_ptr), NULL);
	add_env_var(head, new_nd);
	return (new_nd);
}

t_list	*is_env(char **envp, t_bool *shlvl_founded)
{
	int		i;
	char	*tmp;
	t_list	*new_nd;
	t_list	*head;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		tmp = create_content_env_nd(envp, &i, shlvl_founded);
		if (!tmp)
			return (ft_lstclear(&new_nd, del_char_ptr), NULL);
		new_nd = ft_lstnew(tmp);
		if (!new_nd)
			return (ft_lstclear(&new_nd, del_char_ptr), NULL);
		add_env_var(&head, new_nd);
		i++;
	}
	return (head);
}

t_list	*env_dup(char **envp)
{
	t_list	*head;
	t_bool	shlvl_founded;

	head = NULL;
	shlvl_founded = FALSE;
	if (envp)
	{
		head = is_env(envp, &shlvl_founded);
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
