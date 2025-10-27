/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmmd_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:41:34 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 18:15:10 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	fill_dir_array(t_list *lex, t_redir	*array)
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
		{
			array[j].type = redir_type(tk);
			tmp = tmp->next;
			tk = (t_token *)tmp->content;
			ft_swap_str(&array[j].file, &tk->token);
			j++;
		}
		if (tmp)
			tmp = tmp->next;
	}
	array[j].file = NULL;
}

t_bool	create_dir_array(t_list *lex, t_redir **dir_array, int n_dir)
{
	*dir_array = (t_redir *)ft_calloc((n_dir + 1), sizeof(t_redir));
	if (!dir_array)
		return (malloc_err(), FALSE);
	fill_dir_array(lex, *dir_array);
	return (TRUE);
}
