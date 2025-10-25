/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:54:38 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/10/25 19:47:39 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

t_cmmd	*create_cmmd_node(char **arg_arr, t_redir *dir_arr)
{
	t_cmmd	*new_nd;

	new_nd = (t_cmmd *)malloc(sizeof(t_cmmd));
	if (!new_nd)
		return (malloc_err(), NULL);
	new_nd->cmmd = arg_arr;
	new_nd->redir = dir_arr;
	return (new_nd);
}

t_cmmd	*get_cmmd_data(t_list *lex, int n_dir, int n_arg)
{
	char	**arg_arr;
	t_redir	*dir_arr;
	t_cmmd	*nd;

	if (!create_arg_array(lex, &arg_arr, n_arg))
		return (NULL);
	if (!create_dir_array(lex, &dir_arr, n_dir))
		return (ft_free_2p(arg_arr), NULL);
	nd = create_cmmd_node(arg_arr, dir_arr);
	if (!nd)
	{
		ft_free_2p(arg_arr);
		del_t_redir(dir_arr);
		return (malloc_err(), NULL);
	}
	return (nd);
}

t_cmmd	*token_to_cmmd(t_list **head, t_list *lex)
{
	int		n_dir;
	int		n_arg;
	t_list	*new_nd;
	t_cmmd	*data;

	n_dir = count_token_until_pipe(lex, REDIR);
	n_arg = count_token_until_pipe(lex, WORD)
		+ count_token_until_pipe(lex, EXP) - n_dir;
	data = get_cmmd_data(lex, n_dir, n_arg);
	if (!data)
		return (NULL);
	new_nd = ft_lstnew(data);
	if (!new_nd)
	{
		del_t_cmmd(data);
		return (malloc_err(), NULL);
	}
	if (!*head)
		*head = new_nd;
	else
		ft_lstadd_back(head, new_nd);
	return (data);
}

t_list	*save_cmmd(t_list **lex)
{
	t_list	*tmp;
	t_list	*head;

	tmp = *lex;
	head = NULL;
	while (tmp)
	{
		if (!token_to_cmmd(&head, tmp))
			return (NULL);
		tmp = next_pipe(tmp);
	}
	return (head);
}
