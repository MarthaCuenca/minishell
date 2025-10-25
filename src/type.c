/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:49:32 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 19:49:55 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	redir_type(t_token *nd)
{
	char	*str;
	t_quote	quo;

	str = nd->token;
	quo = nd->quote_type;
	if (ft_strcmp(str, "<<") == 0 && quo == NO_QUOTE)
		return (HEREDOC);
	else if (ft_strcmp(str, ">>") == 0 && quo == NO_QUOTE)
		return (APPEND);
	else if (ft_strcmp(str, "<") == 0 && quo == NO_QUOTE)
		return (DIR_IN);
	else if (ft_strcmp(str, ">") == 0 && quo == NO_QUOTE)
		return (DIR_OUT);
	return (0);
}
