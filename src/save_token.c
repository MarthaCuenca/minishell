/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token_v3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:13:08 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/07/22 18:23:15 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>


static void *token(t_list **head, char *cmmd, int *util)
{
	char	*new_str;
	t_list	*new_nd;

	new_str = ft_substr(cmmd, util[START], (util[END] - util[START] + 1));
	if (!new_str)
		return (NULL);
	new_nd = ft_lstnew(new_str);//(opcional) antes de meter al token hacer parser
	if (!new_nd)
		return (ft_lstclear(head, del_content), NULL);
	if (!head)
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
		util[START] = util[I + 1];
		*quote_state = SIMPLE_QUOTE;
	}
	else if (cmmd[util[I]] == '\"')
	{	
		util[START] = util[I + 1];
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
			if (util[BOOL] == TRUE)
			{
				util[START] = util[I];
				util[BOOL] = FALSE;
			}
			util[END] = util[I];
			util[BOOL] = TRUE;
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
		util[BOOL] = FALSE;
	}
}

static void	dou_quote(char *cmmd, int *quote_state, int *util)
{
	while (cmmd[util[I]] && cmmd[util[I]] != 34)
		util[I]++;
	if (cmmd[util[I]] == 34)
	{
		*quote_state = NO_QUOTE;
		util[END] = util[I] - 1;
		util[I]++;
		util[BOOL] = FALSE;
	}
}

t_list	*save_token(char *cmmd)
{
	int	quote_state;
	int	util[4];
	t_list	*head;

	if (!cmmd)
		return (0);
	quote_state = NO_QUOTE;
	util[START] = -1;
	util[END] = -1;
	util[BOOL] = TRUE;
	util[I] = 0;
	head = NULL;
	while (6 < cmmd[util[I]] && 14 > cmmd[util[I]] && cmmd[util[I]] != 32)
		util[I]++;
	while (cmmd[util[I]])
	{
		if (quote_state == SIMPLE_QUOTE)//si abro ' da igual cualquier otra comilla, espero a cerrarla con '//
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
	return (head);
}
