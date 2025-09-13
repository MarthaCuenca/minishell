/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:19:06 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/13 18:24:21 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_x_symbol(int x, int *symbols, int len)
{
	int	i;

	if (!symbols)
		return (FALSE);
	i = 0;
	while (i < len && x != symbols[i])
		i++;
	if (x == symbols[i])
		return (TRUE);
	return (FALSE);
}

t_bool	is_double_word_after_ineq_symbol(t_list *lex)
{
	int		tk_ty[3];
	t_list	*tmp;

	tmp = lex;
	while (tmp && tmp->next)
	{
		tk_ty[CURR] = ((t_token *)tmp->content)->type;
		tk_ty[NEXT] = ((t_token *)tmp->next->content)->type;
		if (tk_ty[CURR] == REDIR)
			if (tk_ty[NEXT] != WORD && tk_ty[NEXT] != EXP)
				return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

t_bool	is_ineq_symbol_at_end(t_list *lex)
{
	int	last_nd;

	last_nd = ((t_token *)ft_lstlast(lex)->content)->type;
	if (last_nd == REDIR)
		return (TRUE);
	return (FALSE);
}

t_bool	inequality_symbols_syntax(t_list *lex)
{
	t_list	*tmp;

	if (!lex)
		return (FALSE);
	if (!lex)
		return (FALSE);
	tmp = lex;
	if (is_ineq_symbol_at_end(lex))
		return (FALSE);
	if (is_double_word_after_ineq_symbol(lex))
		return (FALSE);
	return (TRUE);
}

t_bool	is_pipe_misplaced(t_list *lex)
{
	int		tk_ty[3];
	t_list	*tmp;

	tmp = lex;
	while (tmp->next)
	{
		tk_ty[CURR] = ((t_token *)tmp->content)->type;
		tk_ty[NEXT] = ((t_token *)tmp->next->content)->type;
		if (tk_ty[CURR] == PIPE)
			if ((tk_ty[NEXT] != REDIR && tk_ty[NEXT] != WORD)
				&& tk_ty[PREV] != WORD)
				return (TRUE);
		tk_ty[PREV] = tk_ty[CURR];
		tmp = tmp->next;
	}
	return (FALSE);
}

t_bool	is_pipe_at_start_or_end(t_list *lex)
{
	int	first_nd;
	int	last_nd;

	if (!lex)
		return (TRUE);
	first_nd = ((t_token *)lex->content)->type;
	last_nd = ((t_token *)ft_lstlast(lex)->content)->type;
	if (first_nd == PIPE)
		return (TRUE);
	else if (last_nd == PIPE)
		return (TRUE);
	return (FALSE);
}

t_bool	pipe_syntax(t_list *lex)
{
	if (!lex)
		return (FALSE);
	if (is_pipe_at_start_or_end(lex))
		return (FALSE);
	if (is_pipe_misplaced(lex))
		return (FALSE);
	return (TRUE);
}

t_bool	syntax(t_list *lex)
{
	if (!lex)
		return (FALSE);
	if (!pipe_syntax(lex))
		return (FALSE);
	if (!inequality_symbols_syntax(lex))
		return (FALSE);
	return (TRUE);
}

t_list	*parser(t_list **lex)
{
	t_list	*pars;

	if (!*lex)
		return (NULL);
	pars = NULL;
	if (!syntax(*lex))
		return (NULL);
	pars = save_cmmd(lex);
	if (!pars)
		return (NULL);
	return (pars);
}
