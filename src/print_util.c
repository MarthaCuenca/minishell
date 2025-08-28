/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:16:27 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/08/28 19:12:51 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

const char	*quote_to_str(t_quote q)
{
	switch (q)
	{
		case NO_QUOTE:
			return ("NO_QUOTE");
		case SIMPLE_QUOTE:
			return ("SIMPLE_QUOTE");
		case DOUBLE_QUOTE:
			return ("DOUBLE_QUOTE");
		case SIMPLE_QUOTE_IN:
			return ("SIMPLE_QUOTE_IN");
		case DOUBLE_QUOTE_IN:
			return ("DOUBLE_QUOTE_IN");
		case MIXED_QUOTE:
			return ("MIXED_QUOTE");
		default :
			return ("UNKNOWN_QUOTE");
	}
}

const char	*type_to_str(t_token_type tt)
{
	switch (tt)
	{
		case WORD:
			return ("WORD");
		case EXP:
			return ("EXP");
		case PIPE:
			return ("PIPE");
		case DIR_IN:
			return ("DIR_IN");
		case DIR_OUT:
			return ("DIR_OUT");
		case APPEND:
			return ("APPEND");
		case HEREDOC:
			return ("HEREDOC");
		default :
			return ("UNKNOWN_TYPE");
	}
}

void	print_tokens(t_list *tokens, t_bool all, int n)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = tokens;
	if (all == FALSE && n)
	{
		while (tmp && i < n)
		{
			printf("[TOKEN]\n%s\n%i: %s\n%i: %s\n\n", ((t_token *)tmp->content)->token,
				((t_token *)(tmp->content))->quote_type,
				quote_to_str(((t_token *)tmp->content)->quote_type),
				((t_token *)(tmp->content))->type,
				type_to_str(((t_token *)(tmp->content))->type));
			tmp = tmp->next;
			i++;
		}
	}
	else if (all == TRUE)
	{
		while (tmp)
		{
			printf("[TOKEN]\n%s\n%i: %s\n%i: %s\n\n", ((t_token *)tmp->content)->token,
				((t_token *)(tmp->content))->quote_type,
				quote_to_str(((t_token *)tmp->content)->quote_type),
				((t_token *)(tmp->content))->type,
				type_to_str(((t_token *)(tmp->content))->type));
			tmp = tmp->next;
		}
	}
}

void	print_env(t_list *env)
{
	t_list	*tmp;

	if (!env)
		return ;
	tmp = env;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

void	print_array_2p(char **array)
{
	int	j;

	if (!array)
		return ;
	j = 0;
	while (array[j])
	{
		printf ("%s\n", array[j]);
		j++;
	}
}
