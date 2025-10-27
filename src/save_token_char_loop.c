/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token_char_loop.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:17:15 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 18:56:56 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdlib.h>

/* validos: $, |, <, >, ~
 * prohibidos: \, &, *, #, \n, \t
 * dudosos: "", '', {}, [], () */
static t_bool	is_operand(char c, char next, int quo_st)
{
	if (quo_st == NO_QUOTE && (c == '&' || c == '*' || c == '#' || c == ';'
			|| c == '{' || c == '}' || c == '(' || c == ')'
			|| c == '[' || c == ']'))
		return (TRUE);
	if (quo_st != SIMPLE_QUOTE && c == '`')
		return (TRUE);
	else if (c == '\\' && (next == ' ' || !next) && quo_st != SIMPLE_QUOTE)
		return (TRUE);
	return (FALSE);
}

static int	check_char(char *cmmd, int *quote_state, int *i)
{
	char	c[3];

	c[CURR] = cmmd[*i];
	c[NEXT] = cmmd[*i + 1];
	if (is_operand(c[CURR], c[NEXT], *quote_state))
		return (syntax_err(1, NULL, c[CURR]), -1);
	if (c[CURR] == '\\')
	{
		if (c[NEXT] == '\'' || c[NEXT] == '\"')
			(*i)++;
		(*i)++;
	}
	return (1);
}

static int	std_char(t_list	**head, char *cmmd, int *range)
{
	int	i;
	int	quote_state;

	i = 0;
	quote_state = NO_QUOTE;
	while (cmmd[i] && cmmd[i] != ' ' && quote_state == NO_QUOTE)
	{
		if (check_char(cmmd, &quote_state, &i) <= 0)
			return (ST_ERR);
		quote_mng(cmmd, &quote_state, &range[END], &i);
		if (range[END] == -1)
			return (ST_ERR);
		i++;
	}
	if (range[END] == -1)
		return (ft_lstclear(head, &del_t_token), ST_ERR);
	if (!range[END] || range[END] != i)
		range[END] = i - 1;
	if (quote_state == NO_QUOTE)
		if (!new_token(head, cmmd, range[START], range[END]))
			return (ft_lstclear(head, &del_t_token), ST_ERR_MALLOC);
	return (i);
}

static int	spc_char(char *cmmd)
{
	int	i;

	i = 0;
	while (cmmd[i] && (cmmd[i] == ' ' || cmmd[i] == '\t' || cmmd[i] == '\n'))
		i++;
	return (i);
}

int	cmmd_loop(t_list **head, char *cmmd, int *i)
{
	int	tmp;
	int	range[2];

	range[START] = 0;
	range[END] = 0;
	tmp = 0;
	if (!cmmd || !i)
		return (ST_ERR);
	if (cmmd[*i] == ' ')
		tmp = spc_char(&cmmd[*i]);
	else
		tmp = std_char(head, &cmmd[*i], range);
	if (tmp == ST_ERR || tmp == ST_ERR_MALLOC)
		return (ft_lstclear(head, &del_t_token), tmp);
	*i += tmp;
	return (ST_OK);
}
