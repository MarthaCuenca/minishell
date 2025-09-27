/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:15:49 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/07/28 18:10:28 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "test_utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int	compare_n_env(char **env, t_list *env_cp)
{
	int i;
	int j;

	i = 0;
	while (env[i] != NULL)
		i++;
	j = ft_lstsize(env_cp);
	if (i != j)
		return (0);
	return (1);
}

static int	compare_env(char **env, t_list *env_cp)
{
	int i;
	t_list	*tmp;

	i = 0;
	tmp = env_cp;
	while (env[i] != NULL)
	{
		//printf("%s\n, %s\n\n\n", env[i], (char *)env_cp->content);
		if (strcmp(env[i], (char *)env_cp->content) != 0)
			return (0);
		i++;
		tmp = tmp->next;
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char	verbose;
	int		test_result;
	t_list	*env_cp;

	(void)argc;
	verbose = argv[1][0];
	env_cp = env_dup(env);
	// Compare number of env variables
	test_result = compare_n_env(env, env_cp);
	eval_result(test_result, verbose, "env: compare number of variables");
	// Compare env variables
	test_result = compare_env(env, env_cp);
	eval_result(test_result, verbose, "env: compare variables one to one");
	return (0);
}
