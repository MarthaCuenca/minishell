/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:56:52 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 21:00:08 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

t_bool	dir_loop(t_env *env, t_redir *dir)
{
	int	j;

	j = 0;
	if (!dir)
		return (TRUE);
	while (dir[j].file)
	{
		if (dir[j].type != HEREDOC)
			if (!exp_mng(env, &dir[j].file, FALSE))
				return (FALSE);
		j++;
	}
	return (TRUE);
}

t_bool	arg_loop(t_env *env, char **arg)
{
	int	j;

	j = 0;
	if (!arg)
		return (TRUE);
	while (arg[j])
	{
		if (!exp_mng(env, &arg[j], FALSE))
			return (FALSE);
		j++;
	}
	return (TRUE);
}

int	expander(t_env *env, t_list **pars)
{
	t_list	*tmp;
	t_cmmd	*curr_cmmd;
	t_redir	*dir;
	char	**arg;

	if (!pars || !env)
		return (ST_ERR);
	tmp = *pars;
	while (tmp)
	{
		curr_cmmd = (t_cmmd *)tmp->content;
		arg = curr_cmmd->cmmd;
		dir = (t_redir *)curr_cmmd->redir;
		if (!arg_loop(env, arg))
			return (ST_ERR_MALLOC);
		if (!dir_loop(env, dir))
			return (ST_ERR_MALLOC);
		tmp = tmp->next;
	}
	return (ST_OK);
}
