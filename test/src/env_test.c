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
#include "test_utils.h"
#include <stdlib.h>
#include <string.h>

static int	compare_n_env(char **env, char **env_cp)
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

static int	compare_env(char **env, char **env_cp)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		if (strcmp(env[i], env_cp[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char	verbose;
	int	test_result;
	char	**env_cp;

	(void)argc;
	verbose = argv[1][0];
	env_cp = ft_env_dup(env);
	// Compare number of env variables
	test_result = compare_n_env(env, env_cp);
	eval_result(test_result, verbose, "env: compare number of variables");
	// Compare env variables
	test_result = compare_env(env, env_cp);
	eval_result(test_result, verbose, "env: compare variables one to one");
	return (0);
}
