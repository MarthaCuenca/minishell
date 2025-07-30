/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_v3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:48:45 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/07/24 12:09:50 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

t_list	*env_dup(char **env)
{
	int		i;
	char	*dup_var;
	t_list	*new_nd;
	t_list	*head;

	if (!env)
		return (NULL);
	i = 0;
	head = NULL;
	while (env[i])
	{
		dup_var = ft_strdup(env[i]);
		if (!dup_var)
			return (ft_lstclear(&new_nd, del_char_ptr), NULL);
		new_nd = ft_lstnew(dup_var);
		if (!new_nd)
			return (ft_lstclear(&new_nd, del_char_ptr), NULL);
		if (!head)
			head = new_nd;
		else
			ft_lstadd_back(&head, new_nd);
		i++;
	}
	return (head);
}
