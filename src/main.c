//42header

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/*** *** *** *** *** *** *** *** *PARSER * *** *** *** *** *** *** *** *** ***/
int	main(int argc, char **argv, char **env)
{
	char	*cmmd;
	t_list	*env_cp;
	t_list	*lex;
	t_list	*pars;
	t_cmmd	*return_value_nd;

	if (argc != 1)
		return (0);
	(void)argv;
	env_cp = env_dup(env);
	lex = NULL;
	pars = NULL;
	return_value_nd = NULL;
	if (!env_cp)
		return (1);
	while (1)
	{
		cmmd = readline("minishell>");
		if (!cmmd)
			break ;
		lex = lexer(cmmd);
		if (!lex)
			break ;
		if (!expander(&lex, env_cp, return_value_nd)) 
		{
			ft_lstclear(&lex, del_t_token);
			break ;
		}
		pars = parser(&lex);
		if (!pars)
			break ;
		print_tokens(lex, TRUE, 0);
		//return_value_nd  = aqui iria exc, guardamo el ultimo cmmmd por su return_value
		//change_return_value_exc()
		ft_lstclear(&lex, del_t_token);
		ft_lstclear(&pars, del_t_token);
		if (ft_strncmp(cmmd, "exit", 5) == 0)
			break ;
		free(cmmd);
	}
	printf("exit");
	if (cmmd)
		free(cmmd);
	del_t_cmmd(return_value_nd);
	ft_lstclear(&pars, &del_t_cmmd);
	ft_lstclear(&env_cp, del_char_ptr);
	rl_clear_history();
	return (0);

}

/*** *** *** *** *** *** *** *** *EXPANDER *** *** *** *** *** *** *** *** ***/

/*static t_list	*fake_return_value_cmmd()
{	
	t_list	*nd;
	t_cmmd	*cmmd_nd;

	cmmd_nd = (t_cmmd *)malloc(sizeof(t_cmmd));
	if (!cmmd_nd)
		return (NULL);
	cmmd_nd->r = 8;
	nd  = ft_lstnew(cmmd_nd);
	if (!nd)
		return (ft_lstclear(&nd, &del_t_cmmd), NULL);
		//return (NULL);//
	return (nd);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmmd;
	t_list	*env_cp;
	t_list	*lex;
	t_list	*fake_cmmd;

	if (argc != 1)
		return (0);
	(void)argv;
	env_cp = env_dup(env);
	if (!env_cp)
		return (1);
	fake_cmmd = fake_return_value_cmmd();
	if (!fake_cmmd)
		return (ft_lstclear(&env_cp, del_char_ptr), 1);
	while (1)
	{
		cmmd = readline("minishell>");//Hay que proteger el readline? Hay que liberar readline?
		if (!cmmd)
			break ;
		lex = lexer(cmmd);
		if (!lex)
			break ;
		//if (!expander(&lex, env_cp, NULL))//
		if (!expander(&lex, env_cp, (t_cmmd *)fake_cmmd->content))
		{
			ft_lstclear(&lex, del_t_token);
			break ;
		}
		ft_lstclear(&lex, del_t_token);
		if (ft_strncmp(cmmd, "exit", 5) == 0)
			break ;
		free(cmmd);
	}
	printf("exit");
	if (cmmd)
		free(cmmd);
	ft_lstclear(&fake_cmmd, &del_t_cmmd);
	ft_lstclear(&env_cp, del_char_ptr);
	rl_clear_history();
	return (0);

}*/

/*** *** *** *** *** *** *** *** * LEXER * *** *** *** *** *** *** *** *** ***/
/*int	main(int argc, char **argv, char **env)
{
	char	*cmmd;
	t_list	*env_cp;
	t_list	*lex;

	if (argc != 1)
		return (0);
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
		print_tokens(lex, TRUE, 0);
		ft_lstclear(&lex, del_t_token);
		if (ft_strncmp(cmmd, "exit", 5) == 0)
			break ;
		free(cmmd);
	}
	printf("exit");
	if (cmmd)
		free(cmmd);
	ft_lstclear(&env_cp, del_char_ptr);
	rl_clear_history();
	return (0);

}*/

/*** *** *** *** *** *** *** *** *** ENV *** *** *** *** *** *** *** *** ***/
/*int	main(int argc, char **argv, char **env)
{
	t_list	*env_cp;
	t_list	*tmp;

	if (!env_cp)
		return (1);
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
	ft_lstclear(&env_cp, del_char_ptr);
}*/
