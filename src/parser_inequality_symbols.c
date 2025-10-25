/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_inequality_symbols.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:47:07 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 18:49:09 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_word_after_redir(t_list *lex)
{
	int		tk_ty[3];
	char	*str;
	t_list	*tmp;

	tmp = lex;
	while (tmp && tmp->next)
	{
		tk_ty[CURR] = ((t_token *)tmp->content)->type;
		tk_ty[NEXT] = ((t_token *)tmp->next->content)->type;
		str = ((t_token *)tmp->next->content)->token;
		if (tk_ty[CURR] == REDIR)
			if (tk_ty[NEXT] != WORD && tk_ty[NEXT] != EXP)
				return (syntax_err(2, str, '\0'), TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

t_bool	is_ineq_symbol_at_end(t_list *lex)
{
	char	*nd_tk;
	int		nd_type;
	t_token	*last_nd;

	last_nd = (t_token *)ft_lstlast(lex)->content;
	nd_type = last_nd->type;
	nd_tk = last_nd->token;
	if (nd_type == REDIR)
		return (syntax_err(2, nd_tk, '\0'), TRUE);
	return (FALSE);
}

t_bool	inequality_symbols_syntax(t_list *lex)
{
	if (!lex)
		return (FALSE);
	if (!lex)
		return (FALSE);
	if (is_ineq_symbol_at_end(lex))
		return (FALSE);
	if (is_word_after_redir(lex))
		return (FALSE);
	return (TRUE);
}
