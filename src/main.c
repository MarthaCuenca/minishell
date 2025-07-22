//42header

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/*** *** *** *** *** *** *** *** * LEXER * *** *** *** *** *** *** *** *** ***/
int	main(int argc, char **argv, char **env)
{
	char	*cmmd;
	t_list	*env_cp;
	t_list	*lex;

	(void)argc;
	(void)argv;
	env_cp = env_dup(env);
	if (!env_cp)
		return (1);
	while (1)
	{
		cmmd = readline("minishell>");//Hay que proteger el readline? Hay que liberar readline?
		if (!cmmd)
			break ;
		lex = lexer(cmmd);
		ft_lstclear(&lex, del_content);
		if (ft_strncmp(cmmd, "exit", 5) == 0)
			break ;
		free(cmmd);
	}
	printf("exit");
	if (cmmd)
		free(cmmd);
	ft_lstclear(&env_cp, del_content);
	rl_clear_history();
	return (0);

}
/*** *** *** *** *** *** *** *** *** ENV *** *** *** *** *** *** *** *** ***/
/*int	main(int argc, char **argv, char **env)
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
}*/
