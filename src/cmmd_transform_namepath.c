/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd_transform_namepath.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:35:58 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/03 17:03:13 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static int	free_return(char **split, int result)
{
	ft_free_split(split);
	return (result);
}

static char	**split_envpath(void)
{
	char	*path_str;
	char	**path_split;

	path_str = getenv("PATH");
	if (!path_str)
		return (NULL);
	path_split = ft_split(path_str, ':');
	if (!path_split)
		return (NULL);
	return (path_split);
}

static int	correct_namepath(char **cmmd_2ptr)
{
	char	**path_split;
	char	*cmmd_joined;
	char	*cmmd_name;
	int		i;

	cmmd_name = *cmmd_2ptr;
	path_split = split_envpath();
	if (!path_split)
		return (0);
	i = -1;
	while (path_split[++i])
	{
		cmmd_joined = ft_join_path(path_split[i], cmmd_name);
		if (!cmmd_joined)
			return (free_return(path_split, 0));
		if (access(cmmd_joined, F_OK) == 0)
		{
			free(cmmd_name);
			*cmmd_2ptr = cmmd_joined;
			return (free_return(path_split, 1));
		}
		free(cmmd_joined);
	}
	free(path_split);
	return (1);
}

int	correct_cmmd_namepath(t_list *lst_cmmd)
{
	t_cmmd	*cmmd;

	while (lst_cmmd)
	{
		cmmd = (t_cmmd *)lst_cmmd->content;
		if (cmmd->cmmd[0])
		{
			if (is_builtin(cmmd->cmmd[0]) || ft_strchr(cmmd->cmmd[0], '/'))
				;
			else if (!correct_namepath(cmmd->cmmd))
				return (0);
		}
		lst_cmmd = lst_cmmd->next;
	}
	return (1);
}
