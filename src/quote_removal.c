/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:13:08 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 19:01:28 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

t_bool	dir_quote_rm_loop(t_redir *dir)
{
	int	j;

	j = 0;
	if (!dir)
		return (TRUE);
	while (dir[j].file)
	{
		rm_quote_mng(&dir[j].file);
		j++;
	}
	return (TRUE);
}

t_bool	arg_rm_quote_loop(char **arg)
{
	int	j;

	j = 0;
	if (!arg)
		return (TRUE);
	while (arg[j])
	{
		rm_quote_mng(&arg[j]);
		j++;
	}
	return (TRUE);
}

int	quote_removal(t_list **pars)
{
	t_list	*tmp;
	t_cmmd	*curr_cmmd;
	t_redir	*dir;
	char	**arg;

	if (!pars)
		return (ST_ERR);
	tmp = *pars;
	while (tmp)
	{
		curr_cmmd = (t_cmmd *)tmp->content;
		arg = curr_cmmd->cmmd;
		dir = (t_redir *)curr_cmmd->redir;
		if (!arg_rm_quote_loop(arg))
			return (ST_ERR_MALLOC);
		if (!dir_quote_rm_loop(dir))
			return (ST_ERR_MALLOC);
		tmp = tmp->next;
	}
	return (ST_OK);
}
