/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmmd_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:39:58 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 19:40:56 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	fill_arg_array(t_list *lex, char **array)
{
	int		j;
	t_list	*tmp;
	t_token	*tk;

	j = 0;
	tmp = lex;
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
	{
		tk = (t_token *)tmp->content;
		if (tk->type == REDIR)
			tmp = tmp->next;
		else if (tk->type == WORD || tk->type == EXP)
		{
			ft_swap_str(&array[j], &tk->token);
			j++;
		}
		tmp = tmp->next;
	}
	array[j] = NULL;
}

t_bool	create_arg_array(t_list *lex, char ***arg_arr, int n_arg)
{
	*arg_arr = (char **)ft_calloc((n_arg + 1), sizeof(char *));
	if (!arg_arr)
		return (malloc_err(), FALSE);
	fill_arg_array(lex, *arg_arr);
	return (TRUE);
}

