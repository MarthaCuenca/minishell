/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:06:07 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/13 13:47:21 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	del_char_ptr(void *str)
{
	char	*tmp;

	if (!str)
		return ;
	tmp = (char *)str;
	free(str);
}

void	del_t_env(void	*minishell_env)
{
	t_env	*tmp;

	if (!minishell_env)
		return ;
	tmp = (t_env *)minishell_env;
	ft_lstclear(&tmp->vars, &del_char_ptr);
}

void	del_t_token(void *tk_nd)
{
	t_token	*tmp;

	if (!tk_nd)
		return ;
	tmp = (t_token *)tk_nd;
	del_char_ptr(tmp->token);
	free(tk_nd);
}

void	del_t_redir(void *dir_array)
{
	int		i;
	t_redir	*tmp;

	if (!dir_array)
		return ;
	i = 0;
	tmp = (t_redir *)dir_array;
	while (tmp[i].file)
	{
		del_char_ptr(tmp[i].file);
		i++;
	}
	free(tmp);
}

void	del_t_cmmd(void *cmmd_nd)
{
	t_cmmd	*tmp;

	if (!cmmd_nd)
		return ;
	tmp = (t_cmmd *)cmmd_nd;
	ft_free_2p(tmp->cmmd);
	del_t_redir(tmp->dir);
	free(tmp);
}
