/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 20:15:31 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/13 13:52:03 by mcuenca-         ###   ########.fr       */
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

t_list	*lexer(char *cmmd)
{
	t_list	*token_list;

	if (!cmmd)
		return (NULL);
	token_list = save_token(cmmd);
	if (!token_list)
		return (NULL);
	if (!split_one_token(&token_list))
		return (NULL);
	if (!delete_empty_token(&token_list))
		return (NULL);
	return (token_list);
}
