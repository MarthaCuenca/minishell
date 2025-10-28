/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:36:09 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/28 15:54:26 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/wait.h>
#include <fcntl.h>

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

static void	print_signal_output(int sig_return)
{
	if (sig_return)
	{
		if (sig_return == 131)
			ft_putstr_fd("Quit (core dumped)", 1);
		else if (sig_return == 130)
			ft_putstr_fd("\n", 1);
	}
}

static void	print_if_error(int status, t_pipe_data *pipe_data, int pid)
{
	t_list	*lst_cmmd;
	t_cmmd	*cmmd;
	int		num_return;

	num_return = WEXITSTATUS(status);
	if (num_return == -1 || num_return == 127)
	{
		cmmd = NULL;
		lst_cmmd = pipe_data->lst_cmmd;
		while (lst_cmmd)
		{
			cmmd = (t_cmmd *)lst_cmmd->content;
			if (cmmd->pid == pid)
				break ;
			lst_cmmd = lst_cmmd->next;
		}
		if (cmmd)
			ft_putstr_fd(cmmd->cmmd[0], 2);
		if (num_return == -1)
			ft_putstr_fd(": memory fail\n", 2);
		if (num_return == 127)
			ft_putstr_fd(": command not found\n", 2);
	}
}

int	process_exit_status(t_pipe_data *pipe_data)
{
	int	status;
	int	wait_pid;
	int	last_return;
	int	sig_return;

	last_return = 0;
	sig_return = 0;
	wait_pid = wait(&status);
	while (wait_pid > 0)
	{
		if (WIFSIGNALED(status))
			sig_return = 128 + WTERMSIG(status);
		if (wait_pid == pipe_data->last_pid)
		{
			if (!WIFEXITED(status))
				last_return = sig_return;
			else
				last_return = WEXITSTATUS(status);
		}
		print_if_error(status, pipe_data, wait_pid);
		wait_pid = wait(&status);
	}
	print_signal_output(sig_return);
	return (last_return);
}

int	choose_outfile_flags(t_redir_type flags)
{
	if (flags == DIR_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (flags == APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (0);
}
