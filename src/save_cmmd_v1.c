/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmmd_v1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:54:38 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/19 13:21:25 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	count_token_until_pipe(t_list *lex, t_token_type target_type)
{
	int				count;
	t_list			*tmp;
	t_token_type	curr_type;

	count = 0;
	tmp = lex;
	curr_type = ((t_token *)tmp->content)->type;
	while (tmp && curr_type != PIPE)
	{
		curr_type = ((t_token *)tmp->content)->type;
		if (curr_type == target_type)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

t_cmmd	*create_cmmd_node(char **arg_arr, t_redir *dir_arr)
{
	t_cmmd	*new_nd;

	new_nd = (t_cmmd *)malloc(sizeof(t_cmmd));
	if (!new_nd)
		return (malloc_err(), NULL);
	new_nd->cmmd = arg_arr;
	new_nd->dir = dir_arr;
	return (new_nd);
}

static int	redir_type(t_token *nd)
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

void	fill_dir_array(t_list *lex, t_redir	*array)
{
	int		j;
	t_list	*tmp;
	t_token	*tk;

	j = 0;
	tmp = lex;
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
	{
		tk = (t_token *)tmp->content;
		if (tk->type == REDIR)
		{
			array[j].type = redir_type(tk);
			tmp = tmp->next;
			tk = (t_token *)tmp->content;
			ft_swap_str(&array[j].file, &tk->token);
			j++;
		}
		if (tmp)
			tmp = tmp->next;
	}
	array[j].file = NULL;
}

t_bool	create_dir_array(t_list *lex, t_redir **dir_array, int n_dir)
{
	*dir_array = (t_redir *)ft_calloc((n_dir + 1), sizeof(t_redir));
	if (!dir_array)
		return (malloc_err(), FALSE);
	fill_dir_array(lex, *dir_array);
	return (TRUE);
}

void	fill_arg_array(t_list *lex, char **array)
{
	int		j;
	t_list	*tmp;
	t_token	*tk;

	j = 0;
	tmp = lex;
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
	{
		tk = (t_token *)tmp->content;
		if (tk->type == REDIR)
			tmp = tmp->next->next;
		else if (tk->type == WORD || tk->type == EXP)
		{
			ft_swap_str(&array[j], &tk->token);
			j++;
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	array[j] = NULL;
}

t_bool	create_arg_array(t_list *lex, char ***arg_arr, int n_arg)
{
	*arg_arr = (char **)ft_calloc((n_arg + 1), sizeof(char *));
	if (!arg_arr)
		return (malloc_err(), FALSE);
	fill_arg_array(lex, *arg_arr);
	return (TRUE);
}

t_cmmd	*get_cmmd_data(t_list *lex, int n_dir, int n_arg)
{
	char	**arg_arr;
	t_redir	*dir_arr;
	t_cmmd	*nd;

	arg_arr = NULL;
	if (n_arg > 0)
		if (!create_arg_array(lex, &arg_arr, n_arg))
			return (NULL);
	dir_arr = NULL;
	if (n_dir > 0)
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

t_list	*next_pipe(t_list *tmp)
{
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp->next);
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
