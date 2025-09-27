/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:00:50 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/27 12:21:32 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int	check_arg_bi_exit(char **cmmd)
{
	int	num;

	if (cmmd[2])
		return (127);
	else if (!ft_str_isdigit(cmmd[1]) || is_overflow(cmmd[1]))
		return (2);
	else
		num = ft_atoi(cmmd[1]);
	if (num > 255)
		num = num % 256;
	return (num);
}

int	dir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		printf("Error: %s: No such file or directory\n", file);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	append_dir_out(char *file, t_redir_type type)
{
	int	fd;

	if (type == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	check_redir_bi_exit(t_redir *dir)
{
	int		i;
	int		status;
	t_redir	*tmp;

	i = 0;
	tmp = dir;
	while (tmp[i].file)
	{
		if (tmp[i].type == APPEND || tmp[i].type == DIR_OUT)
			status = append_dir_out(tmp[i].file, tmp[i].type);//cambiar por la funcion de Cesc
		else if (tmp[i].type == DIR_IN)
			status = dir_in(tmp[i].file);
		i++;
	}
	return (status);
}

void	builtin_exit(t_env *mini_env, t_list **pars, t_cmmd *nd)
{
	int		status;
	t_cmmd	*tmp;

	status = 0;
	tmp = nd;
	if (tmp->dir)
		status = check_redir_bi_exit(tmp->dir);
	if (status == 1)
	{
		mini_env->r = status;
		return ;
	}
	if (tmp->cmmd[1])
		status = check_arg_bi_exit(tmp->cmmd);
	clean_mng(mini_env, NULL, NULL, pars);
	exit(status);
}

/*int	check_redir_bi_exit(t_redir *dir)
{
	int		i;
	int		status;
	t_redir	*tmp;

	i = 0;
	tmp = dir;
	while (tmp[i].file)
	{
		if (tmp[i].type == HEREDOC)
			printf("HERE! Doc... :p Jaja XD\n");
			//status = heredoc(tmp[i].file);
		i++;
	}
	i = 0;
	while (tmp[i].file)
	{
		if (tmp[i].type == APPEND || tmp[i].type == DIR_OUT)
			status = append_dir_out(tmp[i].file, tmp[i].type);
		else if (tmp[i].type == DIR_IN)
			status = dir_in(tmp[i].file);
		i++;
	}
	return (status);
}*/

/*void	one_node(t_env *mini_env, t_list **pars)
{
	int		status;
	t_cmmd	*tmp;

	status = 0;
	tmp = (t_cmmd *)(*pars)->content;
	if (tmp->dir)
		status = check_redir_bi_exit(tmp->dir);
	if (status == 1)
	{
		mini_env->r = status;
		return ;
	}
	if (tmp->cmmd[1])
		status = check_arg_bi_exit(tmp->cmmd);
	clean_mng(mini_env, NULL, NULL, pars);
	exit(status);
}*/

/*void	builtin_exit(t_env *mini_env, t_list **pars)
{
	int		len;

	len = ft_lstsize(*pars);
	if (len == 1)
	one_node(mini_env, pars);
	else
		printf("Is comming...\n");
		//many_node(mini_env, pars);
}*/
	//else
	//{
	//if pipe funciona
	//status = mini_env->r;
	//if pipe falla
	//status = 127;
