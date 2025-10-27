/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_up_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:44:29 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/27 13:07:30 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static t_state	update_curr(t_list **curr, char *new_pwd)
{
	char	*result;

	if (*curr)
	{
		result = ft_strjoin("PWD=", new_pwd);
		if (!result)
			return (ST_ERR_MALLOC);
		free((*curr)->content);
		(*curr)->content = result;
	}
	return (ST_OK);
}

static t_state	update_old(t_list **old, char *curr_pwd)
{
	char	*up_old;
	char	*result;

	if (*old)
	{
		up_old = ft_strchr(curr_pwd, '=') + 1;
		result = ft_strjoin("OLDPWD=", up_old);
		if (!result)
			return (ST_ERR_MALLOC);
		free((*old)->content);
		(*old)->content = result;
	}
	return (ST_OK);
}

t_state	update_path(t_env **mini_env, char *new_pwd, char *cmmd)
{
	t_list	*old;
	t_list	*curr;

	old = check_env_var("OLDPWD", 6, (*mini_env)->vars);
	curr = check_env_var("PWD", 3, (*mini_env)->vars);
	if (old && curr)
	{
		if (update_old(&old, (char *)curr->content) == ST_ERR_MALLOC)
			return (free(new_pwd), ST_ERR_MALLOC);
		if (update_curr(&curr, new_pwd) == ST_ERR_MALLOC)
			return (free(new_pwd), ST_ERR_MALLOC);
		if (cmmd && cmmd[0] == '-' && !cmmd[1])
			printf("%s\n", ft_strchr((char *)curr->content, '=') + 1);
	}
	return (ST_OK);
}
