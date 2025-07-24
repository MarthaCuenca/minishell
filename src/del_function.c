/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:06:07 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/07/24 16:59:45 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	del_char_ptr(void *content)
{
	char	*tmp;

	tmp = (char *)content;
	free(tmp);
}

void	del_t_token(void *token_nd)
{
	t_token	*tmp;

	if (!token_nd)
		return ;
	tmp = (t_token *)token_nd;
	if (tmp->token)
		free(tmp->token);
	free(tmp);
}
