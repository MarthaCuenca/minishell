/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 20:15:31 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 13:46:58 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

/*static void	delete_empty_token(t_list **token_list)
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
}*/

int	save_token(t_list **token_list, char *cmmd)
{
	int		i;
	t_state	state;
	t_list	*head;

	if (!cmmd)
		return (ST_ERR);
	i = 0;
	head = NULL;
	while (cmmd[i])
	{
		state = cmmd_loop(&head, cmmd, &i);
		if ((state == ST_ERR_MALLOC || state == ST_ERR))
			return (ft_lstclear(&head, del_t_token), state);
	}
	*token_list = head;
	return (ST_OK);
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
	state = split_one_token(&token_list);
	if (state == ST_ERR_MALLOC || state == ST_ERR)
		return (state);
	*lex = token_list;
	return (ST_OK);
}
