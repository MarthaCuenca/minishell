/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:36:38 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/29 19:50:46 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

static t_state	bi_cd(t_env **mini_env, char *cmmd)
{
	char	*new_pwd;
	char	*tmp;
	t_state	state;

	state = check_path(*mini_env, cmmd, &tmp);
	if (state == ST_ERR || state == ST_ERR_MALLOC)
		return (state);
	if (chdir(tmp) != 0)
		return (free(tmp), chdir_err_mng(cmmd));
	free(tmp);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (getpwd_err_mng());
	if (update_path(mini_env, new_pwd, cmmd) == ST_ERR_MALLOC)
		return (free(new_pwd), ST_ERR_MALLOC);
	free(new_pwd);
	return (ST_OK);
}

int	builtin_cd(t_env *mini_env, char **cmmd)
{
	int	state;

	state = 0;
	if (cmmd[1])
	{
		if (cmmd[2])
			return (bi_err_mng(1, cmmd[0], NULL), ST_ERR);
		else
			state = bi_cd(&mini_env, cmmd[1]);
	}
	else
		state = bi_cd(&mini_env, NULL);
	return (state);
}
