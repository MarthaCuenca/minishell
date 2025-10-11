/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 10:45:36 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/11 16:41:33 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	builtin_pwd(t_env *mini_env)
{
	t_list	*tmp;
	char	*value;

	tmp = check_env_var("PWD", 3, mini_env->vars);
	value = ft_strchr((char *)tmp->content, '=') + 1;
	printf("%s\n", value);
	return (0);
}
