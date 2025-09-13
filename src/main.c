//42header

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/*** *** *** *** *** *** *** *** *EXPANDER *** *** *** *** *** *** *** *** ***/

/*int	main(int argc, char **argv, char *envp)
{
	//In the process
}*/

/*** *** *** *** *** *** *** *** *PARSER * *** *** *** *** *** *** *** *** ***/

int	main(int argc, char **argv, char **envp)
{
	char	*cmmd;
	t_env	minishell_env;
	t_list	*lex;
	t_list	*pars;

	if (argc != 1)
		return (1);//starter_error
	if (!envp)
		return (1);//starter_error
	(void)argv;
	minishell_env.vars = env_dup(envp);
	if (!minishell_env.vars)
		return (1);//msg
	minishell_env.r = 0;
	lex = NULL;
	pars = NULL;
	while (1)
	{
		cmmd = readline("minishell-");
		if (!cmmd)
			break ;
		lex = lexer(cmmd);
		if (!lex)
			break ;
		pars = parser(&lex);
		if (!pars)
			break ;
		ft_lstclear(&lex, &del_t_token);
		ft_lstclear(&pars, &del_t_cmmd);
		if (ft_strncmp(cmmd, "exit", 5) == 0)
			break ;
		free(cmmd);
	}
	printf("exit");
	if (cmmd)
		free(cmmd);
	ft_lstclear(&lex, &del_t_token);
	ft_lstclear(&pars, &del_t_cmmd);
	ft_lstclear(&minishell_env.vars, del_char_ptr);
	rl_clear_history();
	return (0);
}

/*** *** *** *** *** *** *** *** * LEXER * *** *** *** *** *** *** *** *** ***/
/*int	main(int argc, char **argv, char **env)
{
	char	*cmmd;
	t_list	*env_struct;
	t_list	*lex;

	if (argc != 1)
		return (0);
	(void)argv;
	env_struct = env_dup(env);
	if (!env_struct)
		return (1);
	while (1)
	{
		cmmd = readline("minishell>");//Hay que proteger el readline? Hay que liberar readline?
		if (!cmmd)
			break ;
		lex = lexer(cmmd);
		print_tokens(lex, TRUE, 0);
		ft_lstclear(&lex, del_t_token);
		if (ft_strncmp(cmmd, "exit", 5) == 0)
			break ;
		free(cmmd);
	}
	printf("exit");
	if (cmmd)
		free(cmmd);
	ft_lstclear(&env_struct, del_t_env);
	rl_clear_history();
	return (0);

}*/

/*** *** *** *** *** *** *** *** *** ENV *** *** *** *** *** *** *** *** ***/
/*int	main(int argc, char **argv, char **env)
{
	t_list	*env_struct;
	t_list	*tmp;

	if (!env_struct)
		return (1);
	(void)argv;
	env_struct = env_dup(env);
	if (!env_struct)
		return (1);
	tmp = env_struct;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&env_struct, del_t_env);
}*/
