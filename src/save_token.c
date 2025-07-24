/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:13:08 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/07/24 18:51:03 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

#define I 2
#define BOOL 3

static int	token_type(t_token *nd)
{
	if (ft_strncmp(nd->token, "<<", 2) == 0 && nd->quote_type == NO_QUOTE)
		return (HEREDOC);
	else if (ft_strncmp(nd->token, ">>", 2) == 0 && nd->quote_type == NO_QUOTE)
		return (APPEND);
	else if (ft_strncmp(nd->token, "<", 1) == 0 && nd->quote_type == NO_QUOTE)
		return (DIR_IN);
	else if (ft_strncmp(nd->token, ">", 1) == 0 && nd->quote_type == NO_QUOTE)
		return (DIR_OUT);
	else if (ft_strncmp(nd->token, "|", 1) == 0 && nd->quote_type == NO_QUOTE)
		return (PIPE);
	else if (ft_strncmp(nd->token, "$", 1) == 0
			|| (nd->quote_type == DOUBLE_QUOTE && ft_strchr(nd->token, '$')))
		return (EXP);
	return (WORD);
}

static t_token *token_data(char *cmmd, int *util)
{
	char	*new_str;
	t_token	*new_token;

	if (cmmd[util[START]]  == '\'' || cmmd[util[START]] == '\"')
		new_str = ft_substr(cmmd, util[START] + 1, (util[END] - util[START] - 1));
	else
		new_str = ft_substr(cmmd, util[START], (util[END] - util[START] + 1));
	if (!new_str)
		return (NULL);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (free(new_str), NULL);
	new_token->token = new_str;
	if (cmmd[START] == '\'')
		new_token->quote_type = SIMPLE_QUOTE;
	else if (cmmd[START] == '\"')
		new_token->quote_type = DOUBLE_QUOTE;
	else
		new_token->quote_type = NO_QUOTE;
	new_token->type = token_type(new_token);
	return (new_token);
}

static void	*token(t_list **head, char *cmmd, int *util)
{
	t_list	*new_nd;
	t_token	*nd_data;

	nd_data = token_data(cmmd, util);
	if (!nd_data)
	{
		if (!head)
			return (NULL);
		else
			return (ft_lstclear(head, &del_t_token), NULL);
	}
	new_nd = ft_lstnew(nd_data);/*(op) antes de meter al token hacer parser?*/
	if (!new_nd)
		return (ft_lstclear(head, &del_t_token), NULL);
	if (!*head)
		*head = new_nd;
	else
		ft_lstadd_back(head, new_nd);
	util[START] = -1;
	util[END] = -1;
	return (*head);
}

static void	no_quote(char *cmmd, int *quote_state, int *util)
{
	if (cmmd[util[I]] == '\'')
	{
		util[START] = util[I];
		*quote_state = SIMPLE_QUOTE;
	}
	else if (cmmd[util[I]] == '\"')
	{
		util[START] = util[I];
		*quote_state = DOUBLE_QUOTE;
	}
	else
	{
		if (cmmd[util[I]] == ' ' && util[BOOL] == FALSE)
		{
			util[END] = util[I] - 1;
			util[BOOL] = TRUE;
		}
		else if (!cmmd[util[I] + 1])
		{
			if (cmmd[util[I]] != ' ')
			{
				if (util[BOOL] == TRUE)
				{
					util[START] = util[I];
					util[BOOL] = FALSE;
				}
				util[END] = util[I];
				util[BOOL] = TRUE;
			}
		}
		else
		{
			if (cmmd[util[I]] != ' ' && util[BOOL] == TRUE)
			{
				util[START] = util[I];
				util[BOOL] = FALSE;
			}
		}
	}
	util[I]++;
}

static void	sim_quote(char *cmmd, int *quote_state, int *util)
{
	while (cmmd[util[I]] && cmmd[util[I]] != 39)
		util[I]++;
	if (cmmd[util[I]] == 39)
	{
		*quote_state = NO_QUOTE;
		util[END] = util[I] - 1;
		util[I]++;
		util[BOOL] = TRUE;
	}
}

static void	dou_quote(char *cmmd, int *quote_state, int *util)
{
	while (cmmd[util[I]] && cmmd[util[I]] != 34)
		util[I]++;
	if (cmmd[util[I]] == 34)
	{
		*quote_state = NO_QUOTE;
		util[END] = util[I];
		util[I]++;
		util[BOOL] = TRUE;
	}
}

t_list	*save_token(char *cmmd)
{
	int		quote_state;
	int		util[4];
	t_list	*head;

	if (!cmmd)
		return (0);
	quote_state = NO_QUOTE;
	util[START] = -1;
	util[END] = -1;
	util[BOOL] = TRUE;
	util[I] = 0;
	head = NULL;
	while (cmmd[util[I]])
	{
		if (quote_state == SIMPLE_QUOTE)//si abro ' da igual cualquier otra comilla, 
										//espero a cerrarla con '
			sim_quote(cmmd, &quote_state, util);
		else if (quote_state == DOUBLE_QUOTE)
			dou_quote(cmmd, &quote_state, util);
		else
			no_quote(cmmd, &quote_state, util);
		if (util[START] != -1 && util[END] != -1)
		{
			token(&head, cmmd, util);
			if (!head)
				return (NULL);
		}
	}
	if (quote_state != NO_QUOTE)
		return (ft_lstclear(&head, &del_t_token), NULL);
	return (head);
}
