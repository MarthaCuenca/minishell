/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:34:29 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/16 13:52:44 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*create_filename(char *str_name, int counter, t_env *env)
{
	char	*filename;
	char	*str_num;

	str_num = ft_itoa(counter);
	if (!str_num)
		return (get_error_chr(env, ST_ERR_MALLOC, NULL));
	filename = ft_strjoin(str_name, str_num);
	if (!filename)
		return (get_error_chr(env, ST_ERR_MALLOC, NULL));
	free(str_num);
	return (filename);
}

void	close_heredocs(t_list *lst_cmmd)
{
	int		i;
	t_cmmd	*cmmd;

	while (lst_cmmd)
	{
		cmmd = (t_cmmd *)lst_cmmd->content;
		i = -1;
		while (cmmd->redir[++i].file)
			if (cmmd->redir[i].type == HEREDOC)
				unlink(cmmd->redir->file);
		lst_cmmd = lst_cmmd->next;
	}
}

static int	write_heredoc(char *str_stop, int fd, t_env *env)
{
	char	*next_line;
	int		n;

	n = ft_strlen(str_stop);
	next_line = NULL;
	ft_putstr_fd("heredoc> ", 1);
	next_line = get_next_line(0);
	while (next_line)
	{
		if (!ft_strncmp(next_line, str_stop, n) && next_line[n] == '\n')
			break ;
		if (!exp_mng(env, &next_line, TRUE))
		{
			free(next_line);
			return (get_error(env, ST_ERR_MALLOC, NULL));
		}
		ft_putstr_fd("heredoc> ", 1);
		if (ft_putstr_fd(next_line, fd) == 0)
			{
				free(next_line);
			return (get_error(env, ST_ERR_FD, NULL));
		}
		free(next_line);
		next_line = NULL;
		next_line = get_next_line(0);
	}
	if (next_line)
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
		env->r = -2;
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
			if (cmmd->redir[i].type == HEREDOC)
				if (!create_heredoc(cmmd->redir + i, &count_heredoc, env))
					return (0);
		lst_cmmd = lst_cmmd->next;
	}
	return (1);
}
