//42header

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

/*** *** *** *** *** *** *** *** *** ENV *** *** *** *** *** *** *** *** ***/
int	main(int argc, char **argv, char **env)
{
	t_list	*env_cp;
	t_list	*tmp;

	(void)argc;
	(void)argv;
	env_cp = env_dup(env);
	if (!env_cp)
		return (1);
	tmp = env_cp;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&env_cp, del_content);
}
