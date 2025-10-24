/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:36:38 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/24 19:08:24 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

t_state	update_curr(t_list **curr, char *new_pwd)
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

t_state	update_old(t_list **old, char *curr_pwd)
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

t_state	oldpwd_path(t_env *mini_env, char **result)
{
	char	*value;

	value = obtain_env_var_value(mini_env, NULL, "OLDPWD");
	if (!value || (value && value[0] == '\0'))
		return (bi_err_mng(2, "cd", "OLDPWD"), ST_ERR);
	*result = ft_strdup(value);
	if (!*result)
		return (ST_ERR_MALLOC);
	return (ST_OK);
}

char	*home_path_result(char *match, char *ptr)
{
	char	*tmp;

	if (ptr)
		tmp = ft_strjoin(match, ptr);
	else
		tmp = ft_strdup(match);
	if (!tmp)
		return (NULL);
	return (tmp);
}

t_state	home_path(t_env *mini_env, char *cmmd, char **result)
{
	char	*ptr;
	char	*value;

	value = obtain_env_var_value(mini_env, NULL, "HOME");
	if (!value || (value && value[0] == '\0'))
		return (bi_err_mng(2, "cd", "HOME"), ST_ERR);
	ptr = NULL;
	if (cmmd && cmmd[0] && cmmd[1] && cmmd[1] != '/')
		return (ST_ERR);
	else if (cmmd && cmmd[0] && cmmd[1] && cmmd[1] == '/')
		ptr = &cmmd[1];
	*result = home_path_result(value, ptr);
	if (!*result)
		return (ST_ERR_MALLOC);
	return (ST_OK);
}

t_state	check_path(t_env *mini_env, char *cmmd, char **result)
{
	t_state	state;

	state = ST_OK;
	if (cmmd == NULL || (cmmd && cmmd[0] == '~'))
		state = home_path(mini_env, cmmd, result);
	else if (cmmd && cmmd[0] == '-' && !cmmd[1])
		state = oldpwd_path(mini_env, result);
	else
	{
		*result = ft_strdup(cmmd);
		if (!*result)
			state = ST_ERR_MALLOC;
	}
	return (state);
}

t_state	bi_cd(t_env **mini_env, char *cmmd)
{
	char	*new_pwd;
	char	*tmp;
	t_state	state;

	state = check_path(*mini_env, cmmd, &tmp);
	if (state == ST_ERR || state == ST_ERR_MALLOC)
		return (state);
	if (access(tmp, F_OK) != 0)
		return (bi_err_mng(3, "cd", cmmd), free(tmp), ST_ERR);
	else if (chdir(tmp) != 0)
		return (bi_err_mng(4, "cd", cmmd), free(tmp), ST_ERR);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (ST_ERR_MALLOC);
	if (update_path(mini_env, new_pwd, cmmd) == ST_ERR_MALLOC)
		return (ST_ERR_MALLOC);
	free(new_pwd);
	free(tmp);
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
