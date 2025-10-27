/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:19:06 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 18:05:48 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static t_bool	syntax(t_list *lex)
{
	if (!lex)
		return (FALSE);
	if (!pipe_syntax(lex))
		return (FALSE);
	if (!inequality_symbols_syntax(lex))
		return (FALSE);
	return (TRUE);
}

int	parser(t_list **pars, t_list **lex)
{
	t_list	*cmmd_list;

	if (!*lex)
		return (ST_ERR);
	cmmd_list = NULL;
	if (!syntax(*lex))
		return (ST_ERR);
	cmmd_list = save_cmmd(lex);
	if (!cmmd_list)
		return (ST_ERR_MALLOC);
	*pars = cmmd_list;
	return (ST_OK);
}
