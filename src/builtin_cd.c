/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:36:38 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/11 16:34:01 by mcuenca-         ###   ########.fr       */
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

	result = ft_strjoin("PWD=", new_pwd);
	if (!result)
		return (ST_ERR_MALLOC);
	free((*curr)->content);
	(*curr)->content = result;
	return (ST_OK);
}

t_state	update_old(t_list **old, char *curr_pwd)
{
	char	*up_old;
	char	*result;

	up_old = ft_strchr(curr_pwd, '=') + 1;
	result = ft_strjoin("OLDPWD=", up_old);
	if (!result)
		return (ST_ERR_MALLOC);
	free((*old)->content);
	(*old)->content = result;
	return (ST_OK);
}

t_state	update_path(t_env **mini_env, char *new_pwd, char *cmmd)
{
	t_list	*tmp;
	t_list	*old;
	t_list	*curr;

	tmp = (t_list *)(*mini_env)->vars;
	old = check_env_var("OLDPWD", 6, (*mini_env)->vars);
	curr = check_env_var("PWD", 3, (*mini_env)->vars);
	if (update_old(&old, (char *)curr->content) == ST_ERR_MALLOC)
		return (free(new_pwd), ST_ERR_MALLOC);
	if (update_curr(&curr, new_pwd) == ST_ERR_MALLOC)
		return (free(new_pwd), ST_ERR_MALLOC);
	if (cmmd && cmmd[0] == '-' && !cmmd[1])
		printf("%s\n", ft_strchr((char *)curr->content, '=') + 1);
	return (ST_OK);
}

char	*relative_path(t_env *mini_env, char *cmmd)
{
	int		pwd_len;
	int		cmmd_len;
	char	*match_val;
	char	*result;
	t_list	*match;

	match = check_env_var("PWD", 3, mini_env->vars);
	match_val = ft_strchr((char *)match->content, '=') + 1;
	pwd_len = ft_strlen(match_val);
	cmmd_len = ft_strlen(cmmd);
	result = ft_calloc((pwd_len + cmmd_len + 1 + 1), sizeof(char));
	if (!result)
		return (NULL);
	ft_memmove(result, match_val, pwd_len);
	ft_strlcat(result, "/", pwd_len + cmmd_len + 1 + 1);
	ft_strlcat(result, cmmd, pwd_len + cmmd_len + 1 + 1);
	result[pwd_len + cmmd_len + 1] = '\0';
	return (result);
}

char	*oldpwd_path(t_env *mini_env)
{
	char	*match_val;
	char	*result;
	t_list	*match;

	match = check_env_var("OLDPWD", 6, mini_env->vars);
	match_val = ft_strchr((char *)match->content, '=') + 1;
	result = ft_strdup(match_val);
	if (!result)
		return (NULL);
	return (result);
}

char	*home_path_result(char *match_val, char *ptr)
{
	char	*tmp;

	tmp = ft_strdup(match_val);
	if (!tmp)
		return (NULL);
	if (ptr)
	{
		tmp = ft_strjoin(match_val, ptr);
		free(ptr);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

char	*home_path(t_env *mini_env, char *cmmd)
{
	char	*ptr;
	char	*match_val;
	char	*result;
	t_list	*match;

	ptr = NULL;
	match = check_env_var("HOME", 4, mini_env->vars);
	match_val = ft_strchr((char *)match->content, '=') + 1;
	if (cmmd && cmmd[1] == '/' && cmmd[2])
	{
		ptr = ft_strdup(&cmmd[2]);
		if (!ptr)
			return (NULL);
	}
	result = home_path_result(match_val, ptr);
	if (!result)
		return (NULL);
	return (result);
}

char	*check_path(t_env *mini_env, char *cmmd)
{
	char	*result;

	if (cmmd == NULL || (cmmd && cmmd[0] == '~'))
		result = home_path(mini_env, cmmd);
	else if (cmmd && cmmd[0] == '/')
		result = ft_strdup(cmmd);
	else if (cmmd && cmmd[0] == '-' && !cmmd[1])
		result = oldpwd_path(mini_env);
	else
		result = relative_path(mini_env, cmmd);
	if (!result)
		return (NULL);
	return (result);
}

t_state	bi_cd(t_env **mini_env, char *cmmd)
{
	char	*new_pwd;
	char	*tmp;

	tmp = check_path(*mini_env, cmmd);
	if (!tmp)
		return (ST_ERR_MALLOC);
	if (access(tmp, F_OK) != 0)
		return (ST_ERR);
	else if (chdir(tmp) != 0)
		return (ST_ERR);
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
			return (ST_ERR);//"bash: cd: too many arguments.
		else
			state = bi_cd(&mini_env, cmmd[1]);
	}
	else
		state = bi_cd(&mini_env, NULL);
	return (state);
}
