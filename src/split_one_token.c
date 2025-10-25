/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_one_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:04:50 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 19:59:52 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	rm_and_link(t_list **lst, t_list *nd_rm,
		t_list *add, void (*del)(void *))
{
	t_list	*anchor;

	if (!*lst && !nd_rm && !del)
		return ;
	anchor = *lst;
	if (*lst == nd_rm)
		anchor = nd_rm;
	else
		while (anchor && anchor->next != nd_rm)
			anchor = anchor->next;
	ft_lstlink(&anchor, add);
	if (nd_rm == *lst)
	{
		*lst = add;
		ft_lstdelone(nd_rm, del);
	}
	else
		ft_lstunlink(lst, nd_rm, del);
}

t_bool	is_amalgam(t_token *tk)
{
	if (!tk)
		return (FALSE);
	if (tk->type == WORD
		&& tk->quote_type != SIMPLE_QUOTE && tk->quote_type != DOUBLE_QUOTE)
	{
		if (ft_strchr(tk->token, '|'))
			return (TRUE);
		else if (ft_strstr(tk->token, "<<"))
			return (TRUE);
		else if (ft_strstr(tk->token, ">>"))
			return (TRUE);
		else if (ft_strstr(tk->token, "<"))
			return (TRUE);
		else if (ft_strstr(tk->token, ">"))
			return (TRUE);
		else if (tk->quote_type != NO_QUOTE)
			return (TRUE);
	}
	return (FALSE);
}

t_state	split_one_token(t_list **token_list)
{
	t_list	*tmp;
	t_list	*next;
	t_list	*add;
	t_state	state;

	tmp = *token_list;
	next = NULL;
	while (tmp)
	{
		if (is_amalgam((t_token *)tmp->content))
		{
			next = tmp->next;
			add = NULL;
			state = split_amalgam(tmp, &add);
			if (state == ST_ERR_MALLOC || state == ST_ERR)
				return (ft_lstclear(token_list, del_t_token), state);
			rm_and_link(token_list, tmp, add, del_t_token);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
	return (ST_OK);
}
