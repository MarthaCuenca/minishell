/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:45:39 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 18:07:09 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_pipe_misplaced(t_list *lex)
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
				|| tk_ty[PREV] != WORD)
				return (syntax_err(1, NULL, '|'), TRUE);
		tk_ty[PREV] = tk_ty[CURR];
		tmp = tmp->next;
	}
	return (FALSE);
}

static t_bool	is_pipe_at_start_or_end(t_list *lex)
{
	int	first_nd;
	int	last_nd;

	if (!lex)
		return (TRUE);
	first_nd = ((t_token *)lex->content)->type;
	last_nd = ((t_token *)ft_lstlast(lex)->content)->type;
	if (first_nd == PIPE)
		return (syntax_err(1, NULL, '|'), TRUE);
	else if (last_nd == PIPE)
		return (syntax_err(1, NULL, '|'), TRUE);
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
