/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:15:49 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/07/06 13:58:02 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

int ft_count_env_vars(char **env, char **env_cp)
{
	int i;
	int j;

	i = 0;
	while (env[i] != NULL)
		i++;
	j = 0;
	while (env_cp[j] != NULL)
		j++;
	if (i != j)
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char **env_cp;

	(void)argc;
	(void)argv;
	/*COUNT ENV VARS*/
	env_cp = ft_env_dup(env);
	if (!ft_count_env_vars(env, env_cp))
		return (1);
	return (0);
}
