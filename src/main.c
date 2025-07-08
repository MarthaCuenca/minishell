//42header

#include "minishell.h"
#include "env.h"//
#include <stdio.h>//

int	main(int argc, char **argv, char **env)
{
	t_env	*env_cp;
	t_env	*tmp;

	(void)argc;
	(void)argv;
	env_cp = ft_env_dup(env);
	if (!env_cp)
		return (1);
	tmp = env_cp;
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
	ft_env_free(&env_cp);
	return (0);
}
