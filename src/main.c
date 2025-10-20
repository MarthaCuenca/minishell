/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:04:03 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/19 21:05:46 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	clean_mng(t_env *mini_env, char **line, t_list **lex, t_list **pars)
{
	if (mini_env)
		ft_lstclear(&mini_env->vars, del_char_ptr);
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

int	init_expander_quorm_executor(t_env *mini_env, t_list **pars)
{
	int	state;

	state = expander(mini_env, pars);
	if (state == ST_ERR_MALLOC || state == ST_ERR)
		return (state);
	state = quote_removal(pars);
	if (state == ST_ERR_MALLOC || state == ST_ERR)
		return (state);
	state = excecutor(*pars, mini_env);
	if (!state)
		return (ST_ERR_MALLOC);
	clean_mng(NULL, NULL, NULL, pars);
	return (ST_OK);
}

int	init_lexer_parser(char **line, t_list **lex, t_list **pars)
{
	int	state;

	state = lexer(lex, *line);
	if (state == ST_ERR_MALLOC || state == ST_ERR)
		return (state);
	state = parser(pars, lex);
	if (state == ST_ERR_MALLOC || state == ST_ERR)
		return (state);
	clean_mng(NULL, line, lex, NULL);
	return (ST_OK);
}

void	minishell(t_env *mini_env, char **line, t_list **lex, t_list **pars)
{
	int	state;

	state = 0;
	while (1)
	{
		clean_mng(NULL, line, lex, pars);
		*line = readline("minishell-");
		if (!*line)
			return ;
		add_history(*line);
		state = init_lexer_parser(line, lex, pars);
		if (state == ST_ERR_MALLOC)
			return ;
		else if (state == ST_ERR)
			continue ;
		state = init_expander_quorm_executor(mini_env, pars);
		if (state == ST_ERR_MALLOC)
			return ;
		else if (state == ST_ERR)
			continue ;
	}
}

t_state	env_mng(t_env *mini_env, char **envp)
{
	if (!envp)
	{
		mini_env->vars = NULL;
		return (ST_OK);
	}
	mini_env->vars = env_dup(envp);
	if (!mini_env->vars)
		return (ST_ERR_MALLOC);
	mini_env->r = 0;
	return (ST_OK);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*lex;
	t_list	*pars;
	char	*line;
	t_env	mini_env;

	(void)argv;
	if (argc > 1)
		return (ft_putstr_fd("Error: minishell: too many arguments\n", 2), 1);
	line = NULL;
	lex = NULL;
	pars = NULL;
	if (env_mng(&mini_env, envp) == ST_ERR_MALLOC)
		return (1);
	minishell(&mini_env, &line, &lex, &pars);
	clean_mng(&mini_env, &line, &lex, &pars);
	rl_clear_history();
	return (1);
}
