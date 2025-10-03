/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:16:27 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/03 15:59:01 by faguirre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

const char	*redir_type_to_str(t_redir_type rt)
{
	switch (rt)
	{
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

const char	*token_type_to_str(t_token_type tt)
{
	switch (tt)
	{
		case WORD:
			return ("WORD");
		case EXP:
			return ("EXP");
		case PIPE:
			return ("PIPE");
		case REDIR:
			return ("REDIR");
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
				token_type_to_str(((t_token *)(tmp->content))->type));
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
				token_type_to_str(((t_token *)(tmp->content))->type));
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
	while (array[j] != NULL)
	{
		printf ("%s\n", array[j]);
		j++;
	}
}

void	print_redir(t_redir *array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	printf("---[REDIR]:\n");
	while (array[i].file)
	{	
		printf("---%s  %s\n", redir_type_to_str(array[i].type), array[i].file);
		i++;
	}
}

void	print_cmmds(t_list *cmmds, t_bool all, int n)
{
	int		i;
	t_list	*tmp;
	t_cmmd	*nd;

	if (!cmmds)
		return ;
	i = 0;
	tmp = cmmds;
	if (all == FALSE && n)
	{
		while (tmp && n > i)
		{
			nd = (t_cmmd *)tmp->content;
			printf("[CMMD]:\n");
			print_array_2p(nd->cmmd);
			print_redir(nd->redir);
			i++;
			tmp = tmp->next;
		}
	}
	else if (all == TRUE)
	{
		while (tmp)
		{
			nd = (t_cmmd *)tmp->content;
			printf("\n[CMMD]:\n");
			print_array_2p(nd->cmmd);
			print_redir(nd->redir);
			tmp = tmp->next;
		}
	}
	printf("\n/* ************************************************************************** */\n");
}
