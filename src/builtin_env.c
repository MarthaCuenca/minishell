/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:25:45 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/10 17:05:34 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	builtin_env(t_env *mini_env)
{
	t_list	*tmp;
	char	*equal_char;

	if (!mini_env && mini_env->vars)
		return (1);
	tmp = mini_env->vars;
	while (tmp)
	{
		equal_char = ft_strchr((char *)tmp->content, '=');
		if (equal_char && equal_char[1])
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}
