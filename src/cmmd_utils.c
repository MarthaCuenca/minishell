/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:36:09 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/19 18:13:08 by faguirre         ###   ########.fr       */
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
		ft_putstr_fd("\n", 1);
	}
}

static void	print_if_error(int result, t_pipe_data *pipe_data)
{
	if (result == -1)
	{
		ft_putstr_fd(pipe_data->cmmd_name, 2);
		ft_putstr_fd(": memory fail\n", 2);
	}
	else if (result == 127)
	{
		ft_putstr_fd(pipe_data->cmmd_name, 2);
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
		print_if_error(WEXITSTATUS(status), pipe_data);
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
