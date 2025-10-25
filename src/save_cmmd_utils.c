/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:34:15 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 19:49:19 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	count_token_until_pipe(t_list *lex, t_token_type target_type)
{
	int				count;
	t_list			*tmp;
	t_token_type	curr_type;

	count = 0;
	tmp = lex;
	curr_type = ((t_token *)tmp->content)->type;
	while (tmp && curr_type != PIPE)
	{
		curr_type = ((t_token *)tmp->content)->type;
		if (curr_type == target_type)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

t_list	*next_pipe(t_list *tmp)
{
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp->next);
}
