//42header

#include "minishell.h"
#include "env.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	int		j;
	char	**env_cp;

	(void) argc;
	(void) argv;
	j = 0;
	env_cp = ft_env_dup(env);
	if (!env_cp)
		return (1);
	while (env_cp[j] != NULL)//
		printf("%s\n", env_cp[j++]);//
	ft_2p_free(env_cp);//
	return (0);
}
