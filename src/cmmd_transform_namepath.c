/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd_transform_namepath.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:35:58 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/16 17:02:40 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static int	free_return(char **split, int result, t_env *env)
{
	if (result == 0)
		get_error(env, ST_ERR_MALLOC, NULL);
	ft_free_split(split);
	return (result);
}

static int	split_envpath(t_env *env, char ***path_split)
{
	char	*path_str;

	path_str = obtain_env_var_value(env, "$PATH");
	if (!path_str)
		get_error(env, ST_ERR, "Error: env $PATH not found");
	*path_split = ft_split(path_str, ':');
	free(path_str);
	if (!path_split)
		return (get_error(env, ST_ERR_MALLOC, NULL));
	return (1);
}

static int	correct_namepath(char **cmmd_2ptr, t_env *env)
{
	char	**path_split;
	char	*cmmd_joined;
	int		i;

	path_split = NULL;
	if (!split_envpath(env, &path_split))
		return (0);
	i = -1;
	while (path_split[++i])
	{
		cmmd_joined = ft_join_path(path_split[i], *cmmd_2ptr);
		if (!cmmd_joined)
			return (free_return(path_split, 0, env));
		if (access(cmmd_joined, F_OK) == 0)
		{
			free(*cmmd_2ptr);
			*cmmd_2ptr = cmmd_joined;
			return (free_return(path_split, 1, env));
		}
		free(cmmd_joined);
	}
	return (free_return(path_split, 1, env));
}

int	correct_cmmd_namepath(t_list *lst_cmmd, t_env *env)
{
	t_cmmd	*cmmd;

	while (lst_cmmd)
	{
		cmmd = (t_cmmd *)lst_cmmd->content;
		if (cmmd->cmmd[0])
		{
			if (is_builtin(cmmd->cmmd[0]) || ft_strchr(cmmd->cmmd[0], '/'))
				;
			else if (!correct_namepath(cmmd->cmmd, env))
				return (0);
		}
		lst_cmmd = lst_cmmd->next;
	}
	return (1);
}
