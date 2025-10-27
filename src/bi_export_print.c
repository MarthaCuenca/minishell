/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:54:33 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 13:08:22 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static void	declare_print(char **env_arr)
{
	int		j;
	char	**tmp;

	j = 0;
	tmp = env_arr;
	while (env_arr[j])
		printf("declare -x %s\n", tmp[j++]);
}

static void	ft_sort_ascii(char **env_arr, int count)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	while (j < count)
	{
		i = j + 1;
		len = env_key_len(env_arr[j], '=');
		while (i < count)
		{
			if (ft_strncmp(env_arr[j], env_arr[i], len) > 0)
				ft_swap_str(&env_arr[j], &env_arr[i]);
			i++;
		}
		j++;
	}
}

t_state	builtin_export_print(t_env	*mini_env)
{
	int		count;
	char	**tmp;

	count = ft_lstsize(mini_env->vars);
	tmp = env_to_array(mini_env);
	if (!tmp)
		return (ST_ERR_MALLOC);
	ft_sort_ascii(tmp, count);
	declare_print(tmp);
	ft_free_2p(tmp);
	return (ST_OK);
}
