/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 10:45:36 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 13:20:12 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*get_pwd(t_env *mini_env, t_bool *is_alloc)
{
	char	*value;

	value = obtain_env_var_value(mini_env, NULL, "PWD");
	*is_alloc = FALSE;
	if (!value || (value && value[0] == '\0'))
	{
		value = getcwd(NULL, 0);
		if (!value)
			return (NULL);
		*is_alloc = TRUE;
	}
	return (value);
}

int	builtin_pwd(t_env *mini_env)
{
	char	*value;
	t_bool	is_alloc;

	value = get_pwd(mini_env, &is_alloc);
	printf("%s\n", value);
	if (is_alloc == TRUE)
		free(value);
	return (0);
}
