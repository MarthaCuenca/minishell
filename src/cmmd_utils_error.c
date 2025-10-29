/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd_utils_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:36:24 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/29 16:54:56 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	pipe_e(int pipefd[2], t_env *env)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		env->r = -4;
		return (0);
	}
	return (1);
}

void	execve_e(t_cmmd *cmmd, t_env *env)
{
	char	**arr_env;

	arr_env = env_to_array(env);
	if (!arr_env)
		env->r = -1;
	else if (cmmd->cmmd[0])
	{
		if (ft_strchr(cmmd->cmmd[0], '/'))
			execve(cmmd->cmmd[0], cmmd->cmmd, arr_env);
		env->r = 127;
	}
	else
	{
		env->r = 0;
	}
	if (arr_env)
		ft_free_split(arr_env);
}

int	fork_e(pid_t pid, t_env *env)
{
	if (pid < 0)
	{
		perror("fork");
		env->r = -4;
		return (0);
	}
	return (1);
}

int	fix_exit(int status)
{
	if (status < 0)
		return (1);
	else
		return (status);
}
