/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_one_token_v3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:04:50 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/13 14:05:40 by mcuenca-         ###   ########.fr       */
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

static void	is_inequality_symbols(char *str, int *quote_state, int *end, int *i)
{
	char	*tmp;

	tmp = 0;
	if (*quote_state != NO_QUOTE)
		return ;
	if (ft_strstr(&str[*i], "<<<") || ft_strstr(&str[*i], ">>>"))
		*end = -1;
	else
	{
		if (ft_strrstr(&str[*i], "<<") || ft_strstr(&str[*i], ">>"))
			(*i)++;
		(*i)++;
		*end = *i - 1;
	}
}

t_bool	is_c_symbol(char c, char *symbols)
{
	int	i;

	if (!symbols)
		return (FALSE);
	i = 0;
	while (symbols[i] && c != symbols[i])
		i++;
	if (c == symbols[i])
		return (TRUE);
	return (FALSE);
}

void	is_underscore(char *str, int *end, int *i)
{
	if (str[*i] == '|')
		(*i)++;
	*end = *i - 1;
}

void	is_other(char *str, int *quote_state, int *end, int *i)
{
	while (str[*i] && str[*i] != '<' && str[*i] != '>' && str[*i] != '|')
	{
		if (str[*i] == '\'' || str[*i] == '\"')
			quote_mng(str, quote_state, end, i);
		if (*end == -1)
			return ;
		(*i)++;
	}
	*end = *i - 1;
}

int	start_end_amalgam(char *str, int *quote_state, int *sd, int *i)
{
	sd[START] = *i;
	if (str[*i] == '<' || str[*i] == '>')
		is_inequality_symbols(str, quote_state, &sd[END], i);
	else if (str[*i] == '|')
		is_underscore(str, &sd[END], i);
	else
		is_other(str, quote_state, &sd[END], i);
	if (sd[END] == -1)
		return (-1);
	return (1);
}

t_list	*split_amalgam(t_list *tk)
{
	int		i;
	int		sd[2];
	int		quote_state;
	char	*str;
	t_list	*head;

	i = 0;
	quote_state = NO_QUOTE;
	str = ((t_token *)tk->content)->token;
	head = NULL;
	sd[START] = 0;
	sd[END] = 0;
	while (str[i])
	{
		start_end_amalgam(str, &quote_state, sd, &i);
		if (sd[END] == -1)
			return (NULL);
		if (!new_token(&head, str, sd[START], sd[END]))
			return (ft_lstclear(&head, &del_t_token), NULL);
	}
	return (head);
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

t_list	*split_one_token(t_list **token_list)
{
	t_list	*tmp;
	t_list	*next;
	t_list	*add;

	if (!*token_list)
		return (NULL);
	tmp = *token_list;
	next = NULL;
	add = NULL;
	while (tmp)
	{
		if (is_amalgam((t_token *)tmp->content))
		{
			next = tmp->next;
			add = split_amalgam(tmp);
			if (!add)
				return (ft_lstclear(token_list, del_t_token), NULL);
			rm_and_link(token_list, tmp, add, del_t_token);
			tmp = next;
		}
		else
			tmp = tmp->next;
	}
	return (*token_list);
}
