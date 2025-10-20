/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:35:13 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/20 19:27:28 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

int	is_builtin_not_forkable(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "export", 5) == 0 || \
		ft_strncmp(str, "unset", 4) == 0 || \
		ft_strncmp(str, "cd", 4) == 0 || \
		ft_strncmp(str, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

int	is_builtin(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "echo", 5) == 0 || \
		ft_strncmp(str, "cd", 3) == 0 || \
		ft_strncmp(str, "pwd", 4) == 0 || \
		ft_strncmp(str, "export", 7) == 0 || \
		ft_strncmp(str, "unset", 5) == 0 || \
		ft_strncmp(str, "env", 4) == 0 || \
		ft_strncmp(str, "unset", 6) == 0 || \
		ft_strncmp(str, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

void	choose_builtin(t_cmmd *cmmd, t_env *env)
{
	int		state;
	char	*str;

	state = 0;
	str = (char *)cmmd->cmmd[0];
	if (ft_strcmp(str, "echo") == 0)
		state = builtin_echo(cmmd);
	else if (ft_strcmp(str, "cd") == 0)
		state = builtin_cd(env, cmmd->cmmd);
	else if (ft_strcmp(str, "pwd") == 0)
		state = builtin_pwd(env);
	else if (ft_strcmp(str, "export") == 0)
		state = builtin_export(env, cmmd->cmmd);
	else if (ft_strcmp(str, "unset") == 0)
		state = builtin_unset(env, cmmd->cmmd);
	else if (ft_strcmp(str, "env") == 0)
		state = builtin_env(env);
	else if (ft_strcmp(str, "exit") == 0)
		builtin_exit(env, NULL, cmmd);
	if (state != 0)
		state = 1;
	env->r = state;
}

int	exec_if_1builtin(t_list *lst_cmmd, t_env *env)
{
	t_cmmd	*cmmd;
	int		fd_stdout;

	cmmd = (t_cmmd *)lst_cmmd->content;
	if (!lst_cmmd->next && is_builtin_not_forkable(cmmd->cmmd[0]))
	{
		fd_stdout = dup(1);
		setup_signal_standard(SIG_DFL, SIG_DFL);
		manage_infile(cmmd, env);
		manage_outfile(cmmd, env);
		choose_builtin(cmmd, env);
		dup2(fd_stdout, 1);
		return (1);
	}
	return (0);
}
