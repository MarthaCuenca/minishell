/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:36:09 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/06 18:34:30 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	count_files(t_redir *redir, int type)
{
	int	n;
	int	i;

	n = 0;
	i = -1;
	while (redir[++i].file)
	{
		if ((int)redir[i].type == type)
			n++;
	}
	return (n);
}

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
	char  **arr_env;

	arr_env = env_to_array(env);
	if (!arr_env)
		env->r = -1;
	else if (cmmd->cmmd[0])
	{
		execve(cmmd->cmmd[0], cmmd->cmmd, arr_env);
		perror(cmmd->cmmd[0]);
		env->r = 127;
	}
	else
		env->r = 0;
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

void	process_exit_status(t_pipe_data *pipe_data, t_env *env)
{
	int	status;
	int	wait_pid;

	wait_pid = 1;
	while (wait_pid > 0)
	{
		wait_pid = wait(&status);
		if (wait_pid == pipe_data->last_pid)
		{
			if (WIFEXITED(status))
				env->r = WEXITSTATUS(status);
			else
				env->r = 128 + WTERMSIG(status);
		}
	}
}
