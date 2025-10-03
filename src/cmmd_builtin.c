/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faguirre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:35:13 by faguirre          #+#    #+#             */
/*   Updated: 2025/10/03 17:56:16 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	is_builtin(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "echo", 5) == 0 || \
		ft_strncmp(str, "cd", 3) == 0 || \
		ft_strncmp(str, "pwd", 4) == 0 || \
		ft_strncmp(str, "export", 7) == 0 || \
		ft_strncmp(str, "env", 4) == 0 || \
		ft_strncmp(str, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

void	choose_builtin(t_cmmd *cmmd, t_env *env)
{
	char	*str;

	str = (char *)cmmd->cmmd[0];
	if (ft_strcmp(str, "echo") == 0)
		env->r = builtin_echo(cmmd);
	else if (ft_strcmp(str, "cd") == 0)
		env->r = builtin_cd(env, cmmd->cmmd);
	else if (ft_strcmp(str, "pwd") == 0)
		env->r = builtin_pwd(env);
	else if (ft_strcmp(str, "export") == 0)
		env->r = builtin_export(env, cmmd->cmmd);
	else if (ft_strcmp(str, "unset") == 0)
		env->r = builtin_unset(env, cmmd->cmmd);
	else if (ft_strcmp(str, "env") == 0)
		env->r = builtin_env(env);
	else if (ft_strcmp(str, "exit") == 0)
		builtin_exit(env, NULL, cmmd);
}

int	exec_if_1builtin(t_list *lst_cmmd, t_env *env)
{
	t_cmmd	*cmmd;

	cmmd = (t_cmmd *)lst_cmmd->content;
	if (!lst_cmmd->next && is_builtin(cmmd->cmmd[0]))
	{
		manage_infile(cmmd);
		manage_outfile(cmmd);
		choose_builtin(cmmd, env);
		return (1);
	}
	return (0);
}
