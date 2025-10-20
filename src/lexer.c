/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 20:15:31 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/13 18:51:14 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

t_bool	delete_empty_token(t_list **token_list)
{
	int		len;
	t_list	**tmp;
	t_list	*next;

	tmp = token_list;
	while (*tmp)
	{
		len = ft_strlen(((t_token *)(*tmp)->content)->token);
		if (len == 2
			&& (ft_strncmp(((t_token *)(*tmp)->content)->token, "\"\"", 2) == 0
			|| ft_strncmp(((t_token *)(*tmp)->content)->token, "\'\'", 2) == 0))
		{
			next = (*tmp)->next;
			ft_lstunlink(tmp, *tmp, del_t_token);
			*tmp = next;
		}
		else
			tmp = &(*tmp)->next;
	}
	return (TRUE);
}

int	lexer(t_list **lex, char *cmmd)
{
	t_state	state;
	t_list	*token_list;

	if (!cmmd)
		return (ST_ERR);
	state = save_token(&token_list, cmmd);
	if (state == ST_ERR_MALLOC || state == ST_ERR)
		return (state);
	if (!split_one_token(&token_list))
		return (ST_ERR_MALLOC);
	if (!delete_empty_token(&token_list))
		return (ST_ERR_MALLOC);
	*lex = token_list;
	return (ST_OK);
}
