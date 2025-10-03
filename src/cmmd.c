/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:35:33 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/03 17:02:57 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void	manage_pipes(t_pipe_data *pipe_data, int is_last)
{
	if (pipe_data->pid == 0)
	{
		if (pipe_data->fd_prev >= 0)
		{
			dup2(pipe_data->fd_prev, 0);
			close(pipe_data->fd_prev);
		}
		if (!is_last)
		{
			close(pipe_data->pipefd[0]);
			dup2(pipe_data->pipefd[1], 1);
			close(pipe_data->pipefd[1]);
		}
		return ;
	}
	if (pipe_data->fd_prev >= 0)
		close(pipe_data->fd_prev);
	if (!is_last)
	{
		close(pipe_data->pipefd[1]);
		pipe_data->fd_prev = pipe_data->pipefd[0];
	}
	else
		pipe_data->last_pid = pipe_data->pid;
}

void	manage_infile(t_cmmd *cmmd)
{
	int	fd;
	int	i;
	int	n;

	n = count_files(cmmd->redir, DIR_IN) + count_files(cmmd->redir, HEREDOC);
	i = -1;
	while (cmmd->redir[++i].file && n > 0)
	{
		if (cmmd->redir[i].type == DIR_IN || cmmd->redir[i].type == HEREDOC)
		{
			--n;
			fd = open(cmmd->redir[i].file, O_RDONLY);
			if (fd < 0)
			{
				perror("open infile");
				exit(1);
			}
			if (n == 0)
				dup2(fd, 0);
			close(fd);
		}
	}
}

void	manage_outfile(t_cmmd *cmmd)
{
	int	fd;
	int	i;
	int	n;

	n = count_files(cmmd->redir, DIR_OUT) + count_files(cmmd->redir, APPEND);
	i = -1;
	while ((cmmd->redir[++i].file && n > 0) && \
		(cmmd->redir[i].type == DIR_OUT || cmmd->redir[i].type == APPEND))
	{
		--n;
		if (cmmd->redir[i].type == DIR_OUT)
			fd = open(cmmd->redir[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(cmmd->redir[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("open outfile");
			exit(1);
		}
		if (n == 0)
			dup2(fd, 1);
		close(fd);
	}
}

int	exec_cmmd_node(t_list *lst_cmmd, t_pipe_data *pipe_data, t_env *env)
{
	t_cmmd	*cmmd;

	cmmd = (t_cmmd *)lst_cmmd->content;
	if (lst_cmmd->next)
		if (!pipe_e(pipe_data->pipefd, env))
			return (0);
	pipe_data->pid = fork();
	if (!fork_e(pipe_data->pid, env))
		return (0);
	if (pipe_data->pid == 0)
	{
		manage_pipes(pipe_data, lst_cmmd->next == NULL);
		manage_infile(cmmd);
		manage_outfile(cmmd);
		if (is_builtin(cmmd->cmmd[0]))
		{
			choose_builtin(cmmd, env);
			exit(env->r);
		}
		execve_e(cmmd, env);
	}
	else
		manage_pipes(pipe_data, lst_cmmd->next == NULL);
	return (1);
}

int	exec_cmmd(t_list *lst_cmmd, t_env *env)
{
	t_pipe_data	pipe_data;

	pipe_data.fd_prev = -1;
	pipe_data.last_pid = -1;
	if (exec_if_1builtin(lst_cmmd, env))
		return (1);
	while (lst_cmmd)
	{
		if (!exec_cmmd_node(lst_cmmd, &pipe_data, env))
			return (1);
		lst_cmmd = lst_cmmd->next;
	}
	process_exit_status(&pipe_data, env);
	return (1);
}
