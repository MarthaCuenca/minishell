/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_mng.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:39:02 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/11 16:38:55 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_mng(t_env *mini_env, t_list **pars, t_cmmd *nd)
{
	int		re_val;
	char	*str;

	re_val = 0;
	str = (char *)nd->cmmd[0];
	if (ft_strcmp(str, "echo") == 0)
		re_val = builtin_echo(nd);
	else if (ft_strcmp(str, "cd") == 0)
		re_val = builtin_cd(mini_env, nd->cmmd);
	else if (ft_strcmp(str, "pwd") == 0)
		re_val = builtin_pwd(mini_env);
	else if (ft_strcmp(str, "export") == 0)
		re_val = builtin_export(mini_env, nd->cmmd);
	else if (ft_strcmp(str, "unset") == 0)
		re_val = builtin_unset(mini_env, nd->cmmd);
	else if (ft_strcmp(str, "env") == 0)
		re_val = builtin_env(mini_env);
	else if (ft_strcmp(str, "exit") == 0)
		builtin_exit(mini_env, pars, nd);
	return (re_val);
}
