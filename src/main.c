/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:04:03 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/19 14:07:33 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

t_bool	fake_exec(t_env *mini_env, t_list **pars)
{
	char	**mini_env_arr;

	if (!expander(mini_env, pars))
		return (FALSE);
	if (!quote_removal(pars))
		return (FALSE);
	mini_env_arr = env_to_array(mini_env);
	if (!mini_env_arr)
		return (FALSE);
	ft_free_2p(mini_env_arr);
	return (TRUE);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmmd;
	t_env	mini_env;
	t_list	*lex;
	t_list	*pars;

	if (starter_err(argc, envp))
		return (1);
	(void)argv;
	mini_env.vars = env_dup(envp);
	if (!mini_env.vars)
		return (malloc_err(), 1);
	mini_env.r = 0;
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
		if (!fake_exec(&mini_env, &pars))
			break ;
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
	ft_lstclear(&mini_env.vars, del_char_ptr);
	rl_clear_history();
	return (0);
}

/*** *** *** *** *** *** *** *** *EXPANDER *** *** *** *** *** *** *** *** ***/

/*t_bool fake_exec(t_env *mini_env, t_list **pars)
{
	char	**mini_env_arr;

	if  (!expander(mini_env, pars))
		return (FALSE);
	if (!quote_removal(pars))
		return (FALSE);
	mini_env_arr = env_to_array(mini_env);
	if (!mini_env_arr)
		return (FALSE);
	ft_free_2p(mini_env_arr);
	return (TRUE);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmmd;
	t_env	mini_env;
	t_list	*lex;
	t_list	*pars;

	if (argc != 1)
		return (1);//starter_error
	if (!envp)
		return (1);//starter_error
	(void)argv;
	mini_env.vars = env_dup(envp);
	if (!mini_env.vars)
		return (1);//msg
	mini_env.r = 0;
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
		print_tokens(lex, TRUE, 0);
		ft_lstclear(&lex, &del_t_token);
		printf("\n***\n");
		if (!fake_exec(&mini_env, &pars))
			break ;
		print_cmmds(pars, TRUE, 0);
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
	ft_lstclear(&mini_env.vars, del_char_ptr);
	rl_clear_history();
	return (0);
}*/

/*** *** *** *** *** *** *** *** *PARSER * *** *** *** *** *** *** *** *** ***/

/*int	main(int argc, char **argv, char **envp)
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
}*/

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
		cmmd = readline("minishell>");
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
