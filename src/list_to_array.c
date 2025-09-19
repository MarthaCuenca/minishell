/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:26:49 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/17 16:50:17 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	**fill_env_array(t_list *og, int len)
{
	int		j;
	char	*dup;
	char	**new_env;
	t_list	*tmp;

	j = 0;
	new_env = (char **)ft_calloc(len + 1, sizeof(char *));
	tmp = og;
	if (!new_env)
		return (NULL);
	while (tmp)
	{
		dup = ft_strdup((char *)tmp->content);
		if (!dup)
			return (ft_free_2p(new_env), NULL);
		new_env[j] = dup;
		j++;
		tmp = tmp->next;
	}
	new_env[j] = NULL;
	return (new_env);
}

char	**env_to_array(t_env	*mini_env)
{
	int		len;
	char	**env_arr;
	t_list	*tmp;

	tmp = mini_env->vars;
	len = ft_lstsize(tmp);
	env_arr = fill_env_array(tmp, len);
	if (!env_arr)
		return (NULL);
	return (env_arr);
}
