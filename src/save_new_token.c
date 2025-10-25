/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_new_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:20:05 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 20:28:23 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static t_token	*token_data(char *cmmd, int start, int end)
{
	char	*new_str;
	t_token	*new_token;

	new_str = ft_substr(cmmd, start, end - start + 1);
	if (!new_str)
		return (malloc_err(), NULL);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		free(new_str);
		return (malloc_err(), NULL);
	}
	new_token->token = new_str;
	new_token->quote_type = token_quo_type(new_token->token);
	new_token->type = token_type(new_token);
	return (new_token);
}

void	*new_token(t_list **head, char *cmmd, int start, int end)
{
	t_list	*new_nd;
	t_token	*nd_data;

	nd_data = token_data(cmmd, start, end);
	if (!nd_data)
		return (NULL);
	new_nd = ft_lstnew(nd_data);
	if (!new_nd)
		return (malloc_err(), del_t_token(nd_data), NULL);
	if (!*head)
		*head = new_nd;
	else
		ft_lstadd_back(head, new_nd);
	start = 0;
	end = 0;
	return (*head);
}
