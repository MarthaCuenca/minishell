/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:04:03 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/27 10:41:41 by mcuenca-         ###   ########.fr       */
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
	int		bi_value;
	char	**mini_env_arr;
	t_list	*tmp;

	bi_value = 0;
	tmp = *pars;
	if (!expander(mini_env, pars))
		return (-1);
	if (!quote_removal(pars))
		return (-1);
	mini_env_arr = env_to_array(mini_env);
	if (!mini_env_arr)
		return (-1);
	while (tmp)
	{
		bi_value = builtin_mng(mini_env, pars, ((t_cmmd *)tmp->content));
		if (bi_value < 0)
			return (-1);
		tmp = tmp->next;
	}
	ft_free_2p(mini_env_arr);
	return (bi_value);
}

void	clean_mng(t_env *mini_env, char **line, t_list **lex, t_list **pars)
{
	if (mini_env)
		ft_lstclear(&mini_env->vars, del_char_ptr);
		//del_(mini_env->vars);
	if (lex && *lex)
		ft_lstclear(lex, &del_t_token);
	if (pars && *pars)
		ft_lstclear(pars, &del_t_cmmd);
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
}

void	init_minishell(t_env *mini_env, char **line, t_list **lex, t_list **pars)
{
	while (1)
	{
		*line = readline("minishell-");
		if (!*line)
			//return ;
		add_history(*line);
		*lex = lexer(*line);
		if (!*lex)
			return ;
		*pars = parser(lex);
		if (!*pars)
			return ;
		clean_mng(NULL, line, lex, NULL);
		mini_env->r = fake_exec(mini_env, pars);
		if (mini_env->r < 0)
			return ;
		//if (ft_strncmp(*line, "exit", 5) == 0)//
		//	return ;//
		clean_mng(NULL, NULL, NULL, pars);
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
	char	*line;
	t_env	mini_env;

	(void)argv;
	if (starter_err(argc, envp))
		return (1);
	lex = NULL;
	pars = NULL;
	if (!env_mng(&mini_env, envp))
		return (1);
	init_minishell(&mini_env, &line, &lex, &pars);
	clean_mng(&mini_env, &line, &lex, &pars);//
	//ft_lstclear(&mini_env.vars, del_char_ptr);
	rl_clear_history();
	return (0);
}
