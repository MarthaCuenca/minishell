/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:34:29 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/16 15:11:07 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	write_line(char **line, t_env *env, int fd)
{
	if (!exp_mng(env, line))
		return (get_error(env, ST_ERR_MALLOC, NULL));
	if (ft_putstr_fd(*line, fd) == 0)
		return (get_error(env, ST_ERR_FD, NULL));
	return (0);
}

static int	write_heredoc(char *str_stop, int fd, t_env *env)
{
	char	*next_line;
	int		n;
	int		res_write_line;

	n = ft_strlen(str_stop);
	next_line = NULL;
	ft_putstr_fd("> ", 1);
	next_line = get_next_line(0);
	while (next_line && \
		!(!ft_strncmp(next_line, str_stop, n) && next_line[n] == '\n'))
	{
		res_write_line = write_line(&next_line, env, fd);
		free(next_line);
		next_line = NULL;
		if (res_write_line != 0)
			return (res_write_line);
		ft_putstr_fd("> ", 1);
		next_line = get_next_line(0);
	}
	if (!next_line && g_signal == 0)
		ft_putstr_fd("\nwarning: heredoc end because Ctrl+D\n", 2);
	else
		free(next_line);
	return (1);
}

static int	create_heredoc(t_redir *redir, int *counter, t_env *env)
{
	int		fd;
	char	*filename;

	filename = create_filename("heredoc", *counter, env);
	if (!filename)
		return (0);
	fd = open(\
		filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!fd || !write_heredoc(redir->file, fd, env))
	{
		free(filename);
		close(fd);
		return (0);
	}
	close(fd);
	free(redir->file);
	redir->file = filename;
	(*counter)++;
	return (1);
}

int	create_heredocs(t_list *lst_cmmd, t_env *env)
{
	int		i;
	int		count_heredoc;
	t_cmmd	*cmmd;

	count_heredoc = 0;
	while (lst_cmmd)
	{
		cmmd = (t_cmmd *)lst_cmmd->content;
		i = -1;
		while (cmmd->redir[++i].file)
		{
			if (cmmd->redir[i].type == HEREDOC)
			{
				if (!create_heredoc(cmmd->redir + i, &count_heredoc, env))
					return (0);
				if (!update_heredoc(env, lst_cmmd))
					return (0);
			}
		}
		lst_cmmd = lst_cmmd->next;
	}
	return (1);
}
