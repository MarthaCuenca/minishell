/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token_v3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:13:08 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/08/06 18:39:40 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	token_type(t_token *nd)
{
	if (ft_strncmp(nd->token, "<<", 2) == 0 && nd->quote_type == NO_QUOTE)
		return (HEREDOC);
	else if (ft_strncmp(nd->token, ">>", 2) == 0 && nd->quote_type == NO_QUOTE)
		return (APPEND);
	else if (ft_strncmp(nd->token, "<", 1) == 0 && nd->quote_type == NO_QUOTE)
		return (DIR_IN);
	else if (ft_strncmp(nd->token, ">", 1) == 0 && nd->quote_type == NO_QUOTE)
		return (DIR_OUT);
	else if (ft_strncmp(nd->token, "|", 1) == 0 && nd->quote_type == NO_QUOTE)
		return (PIPE);
	else if (ft_strncmp(nd->token, "$", 1) == 0
		|| (nd->quote_type != SIMPLE_QUOTE && ft_strchr(nd->token, '$')))
		return (EXP);
/*Si hay comillas simples: NO se expande nada dentro de ellas
Si hay comillas dobles: sí se expande si hay $VAR
Si está fuera de comillas: se expande
Si hay una mezcla: permite expansión solo fuera de comillas simples*/
	return (WORD);
}

t_bool	between_matchchr(char *str, char match, char avoid)
{
	int		i;
	t_bool	open;

	open = FALSE;
	i = 0;
	while (str[i])
	{
		if (str[i] == avoid && open == FALSE)
			return (FALSE);
		if (str[i] == match)
		{
			if (!open)
				open = TRUE;
			else
				open = FALSE;
		}
		i++;
	}
	return (TRUE);
}

static t_quote	token_quo_type(t_token *nd)
{
	int	len;

	len = ft_strlen(nd->token) - 1;
	if (!ft_strchr(nd->token, '\'') && !ft_strchr(nd->token, '\"'))
		return (NO_QUOTE);
	else if ((nd->token[0] == '\'' && nd->token[len] == '\'')
		|| between_matchchr(nd->token, '\'', '\"'))
		return (SIMPLE_QUOTE);
	else if ((nd->token[0] == '\"' && nd->token[len] == '\"')
		|| between_matchchr(nd->token, '\"', '\''))
		return (DOUBLE_QUOTE);
	return (MIXED_QUOTE);
}

static t_token	*token_data(char *cmmd, int start, int end)
{
	char	*new_str;
	t_token	*new_token;

	new_str = ft_substr(cmmd, start, end - start + 1);
	if (!new_str)
		return (NULL);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (free(new_str), NULL);
	new_token->token = new_str;
	new_token->quote_type = token_quo_type(new_token);
	new_token->type = token_type(new_token);
	return (new_token);
}

static void	*new_token(t_list **head, char *cmmd, int start, int end)
{
	t_list	*new_nd;
	t_token	*nd_data;

	nd_data = token_data(cmmd, start, end);
	if (!nd_data)
	{
		if (!head)
			return (NULL);
		else
			return (ft_lstclear(head, &del_t_token), NULL);
	}
	new_nd = ft_lstnew(nd_data);
	if (!new_nd)
		return (ft_lstclear(head, &del_t_token), NULL);
	if (!*head)
		*head = new_nd;
	else
		ft_lstadd_back(head, new_nd);
	start = 0;
	end = 0;
	return (*head);
}

int	double_quo(char *cmmd, int *sq, int *i)
{
	int	tmp;

	tmp = *i + 1;
	*sq = DOUBLE_QUOTE;
	while (cmmd[tmp] && cmmd[tmp] != '\"')
		tmp++;
	if (cmmd[tmp] == '\"')
	{
		*sq = NO_QUOTE;
		*i = tmp;
		return (tmp);
	}
	return (-1);
}

int	simple_quo(char *cmmd, int *sq, int *i)
{
	int	tmp;

	tmp = *i + 1;
	*sq = SIMPLE_QUOTE;
	while (cmmd[tmp] && cmmd[tmp] != '\'')
		tmp++;
	if (cmmd[tmp] == '\'')
	{
		*sq = NO_QUOTE;
		*i = tmp;
		return (tmp);
	}
	return (-1);
}

int	std_char(t_list	**head, char *cmmd, int *sd)
{
	int	i;
	int	quote_state;

	i = 0;
	quote_state = NO_QUOTE;
	while (cmmd[i] && cmmd[i] != ' ' && quote_state == NO_QUOTE)
	{
		if (cmmd[i] == '\'')
			sd[END] = simple_quo(cmmd, &quote_state, &i);
		else if (cmmd[i] == '\"')
			sd[END] = double_quo(cmmd, &quote_state, &i);
		if (sd[END] == -1)
			return (-1);
		i++;
	}
	if (sd[END] == -1)
		return (ft_lstclear(head, &del_t_token), -1);
	if (!sd[END] || sd[END] != i)
		sd[END] = i - 1;
	if (quote_state == NO_QUOTE)
		if (!new_token(head, cmmd, sd[START], sd[END]))
			return (ft_lstclear(head, &del_t_token), -1);
	return (i);
}

int	spc_char(char *cmmd)
{
	int	i;

	i = 0;
	while (cmmd[i] && (cmmd[i] == ' ' || cmmd[i] == '\t'))
		i++;
	return (i);
}

t_bool	cmmd_loop(t_list **head, char *cmmd, int *i)
{
	int	tmp;
	int	sd[2];

	sd[START] = 0;
	sd[END] = 0;
	tmp = 0;
	if (!cmmd || !i)
		return (FALSE);
	if (cmmd[*i] == ' ')
		tmp = spc_char(&cmmd[*i]);
	else
		tmp = std_char(head, &cmmd[*i], sd);
	if (tmp == -1)
		return (ft_lstclear(head, &del_t_token), FALSE);
	*i += tmp;
	return (TRUE);
}

t_list	*save_token(char *cmmd)
{
	int		i;	
	t_list	*head;

	if (!cmmd)
		return (NULL);
	i = 0;
	head = NULL;
	while (cmmd[i])
		if (!cmmd_loop(&head, cmmd, &i))
			break ;
	return (head);
}

//int main(int argc, char **argv)
//{
/*** ***	t_bool	cmmd_loop(t_list **head, char *cmmd, int *i) *** ***/
	/*int 	i;
	t_list *token;

	if (argc != 2)
		return (1);
	i = 0;
	token = NULL;	
	while (argv[1][i])
	{
		printf("%c\n", argv[1][i]);
		if (!cmmd_loop(&token, argv[1], &i))
			break ;
	}*/

/*** ***	static void *token(t_list **head, char *cmmd, int start, int end)	*** ***/
/***		static t_token  *token_data(char *cmmd, int start, int end)	***/

	/*t_list	*token;

	if (argc != 4)
		return (0);
	token = NULL;
	new_token(&token, argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
	printf("cmmd: %s\n%i: %s\n%i: %s", 
			((t_token *)token->content)->token,
			((t_token *)token->content)->type, 
			type_to_str(((t_token *)token->content)->type), 
			((t_token *)token->content)->quote_type, 
			quote_to_str(((t_token *)token->content)->quote_type));
	del_t_token(token);*/

/*** ***	int token_type(t_token_type *token)	*** ***/
/*** ***	static t_quote	token_quo_type(t_token *nd)	*** ***/
/***		t_bool	between_matchchr(char *str, char match, char avoid)	***/
	/*char	*str;
	t_token	*token;

	if (argc != 2)
		return (0);
	token = (t_token *)malloc(1 * sizeof(t_token));
	str = ft_strdup(argv[1]);
	token->token = str;
	token->quote_type = token_quo_type(token);
	token->type = token_type(token);
	printf("cmmd: %s\n%i: %s\n%i: %s", 
			token->token,
			token->type, 
			type_to_str(token->type), 
			token->quote_type, 
			quote_to_str(token->quote_type));
	del_t_token(token);*/
//	return (0);
//}
