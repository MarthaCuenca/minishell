/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:06:07 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/08/28 18:20:44 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	del_char_ptr(void *str)
{
	char	*tmp;

	if (!str)
		return ;
	tmp = (char *)str;
	free(str);
}

void	ft_free_2p(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
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

void	del_t_redir(void *dir_nd)
{
	t_redir	*tmp;

	if (!dir_nd)
		return ;
	tmp = (t_redir *)dir_nd;
	if (tmp->file)
		free(tmp->file);
	free(tmp);
}

void	del_t_cmmd(void *cmmd_nd)
{
	t_cmmd	*tmp;

	if (!cmmd_nd)
		return ;
	tmp = (t_cmmd *)cmmd_nd;
	del_char_ptr(tmp->cmmd);
	ft_free_2p(tmp->args);
	del_t_redir(tmp->infile);
	del_t_redir(tmp->outfile);
	free(tmp);
}
