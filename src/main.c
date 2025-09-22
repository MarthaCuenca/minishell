/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:04:03 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/22 11:15:40 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	fake_exec(t_env *mini_env, t_list **pars)
{
	char	**mini_env_arr;

	if (!expander(mini_env, pars))
		return (0);
	if (!quote_removal(pars))
		return (0);
	mini_env_arr = env_to_array(mini_env);
	if (!mini_env_arr)
		return (0);
	ft_free_2p(mini_env_arr);
	return (1);
}

void	clean_mng(char **cmmd, t_list **lex, t_list **pars)
{
	if (*lex)
		ft_lstclear(lex, &del_t_token);
	if (*pars)
		ft_lstclear(pars, &del_t_cmmd);
	if (*cmmd)
		free(*cmmd);
}

void	init_minishell(t_env *mini_env, char **cmmd, t_list **lex, t_list **pars)
{
	while (1)
	{
		*cmmd = readline("minishell-");
		if (!*cmmd)
			return ;
		add_history(*cmmd);
		*lex = lexer(*cmmd);
		if (!*lex)
			return ;
		*pars = parser(lex);
		if (!*pars)
			return ;
		mini_env->r = fake_exec(mini_env, pars);
		if (!mini_env->r)
			return ;
		if (ft_strncmp(*cmmd, "exit", 5) == 0)//
			break ;//
		clean_mng(cmmd, lex, pars);
	}
}

t_bool	env_mng(t_env *mini_env, char **envp)
{
	mini_env->vars = env_dup(envp);
	if (!mini_env->vars)
		return (malloc_err(), FALSE);
	mini_env->r = 0;
	return (TRUE);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*lex;
	t_list	*pars;
	char	*cmmd;
	t_env	mini_env;

	(void)argv;
	if (starter_err(argc, envp))
		return (1);
	lex = NULL;
	pars = NULL;
	if (!env_mng(&mini_env, envp))
		return (1);
	init_minishell(&mini_env, &cmmd, &lex, &pars);
	clean_mng(&cmmd, &lex, &pars);//
	ft_lstclear(&mini_env.vars, del_char_ptr);
	rl_clear_history();
	return (0);
}
