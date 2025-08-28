/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token_v5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:13:08 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/08/28 19:52:50 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

t_bool	is_special_dollar(char *str, int len)
{
	if (ft_strncmp(str, "$?", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "$$", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "$!", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "$#", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "$@", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "$0", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "$1", len) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "${", 2) == 0 && ft_strrchr(str, '}') == &str[len])
		return (TRUE);
	return (FALSE);
}

static int	token_type(t_token *nd)//y esto casos ";, &, \ "?
{
	char	*str;
	int		quo;
	int		len;

	str = nd->token;
	quo = nd->quote_type;
	len = ft_strlen(str);
	if (ft_strcmp(str, "<<") == 0 && quo == NO_QUOTE)
		return (HEREDOC);
	else if (ft_strcmp(str, ">>") == 0 && quo == NO_QUOTE)
		return (APPEND);
	else if (ft_strcmp(str, "<") == 0 && quo == NO_QUOTE)
		return (DIR_IN);
	else if (ft_strcmp(str, ">") == 0 && quo == NO_QUOTE)
		return (DIR_OUT);
	else if (ft_strcmp(str, "|") == 0 && quo == NO_QUOTE)
		return (PIPE);
	else if (is_special_dollar(str, len)
		|| (quo == DOUBLE_QUOTE && ft_strchr(str, '$'))
		|| (quo == NO_QUOTE && (count_c_char(str, '$') == 1 && str[0] == '$')))
		return (EXP);
	return (WORD);
}

t_bool	edge_quotes(char *str, char c)
{
	int	i;
	int	len;

	if (!str || !c)
		return (FALSE);
	i = 1;
	len = ft_strlen(str);
	if (str[0] != c && str[len] != c)
		return (FALSE);
	while (str[i] && i < len - 1)
	{
		if (str[i] == c)
		{
			if (i > 0 && str[i - 1] != '\\')
				return (FALSE);
			i++;
		}
		i++;
	}
	return (TRUE);
}

t_bool	between_matchchr(char *str, char match, char avoid)
{
	int		i;
	int		quotes_inside;
	t_bool	open;

	open = FALSE;
	quotes_inside = FALSE;
	i = 0;
	while (str[i])
	{
		if (i > 0 && str[i] == match && str[i - 1] == '\\')
			i++;
		if (str[i] == avoid && open == FALSE)
			return (FALSE);
		if (str[i] == match)
		{
			quotes_inside = TRUE;
			if (!open)
				open = TRUE;
			else
				open = FALSE;
		}
		i++;
	}
	return (quotes_inside);
}

t_bool	no_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			if (i > 0 && str[i - 1] != '\\')
				return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_quote	token_quo_type(t_token *nd)
{
	if (no_quotes(nd->token))
		return (NO_QUOTE);
	else if (edge_quotes(nd->token, '\''))
		return (SIMPLE_QUOTE);
	else if (between_matchchr(nd->token, '\'', '\"'))
		return (SIMPLE_QUOTE_IN);
	else if (edge_quotes(nd->token, '\"'))
		return (DOUBLE_QUOTE);
	else if (between_matchchr(nd->token, '\"', '\''))
		return (DOUBLE_QUOTE_IN);
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

void	*new_token(t_list **head, char *cmmd, int start, int end)
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

int	double_quo(char *cmmd, int *qs, int *i)
{
	int	tmp;

	tmp = *i + 1;
	*qs = DOUBLE_QUOTE;
	while (cmmd[tmp] && cmmd[tmp] != '\"')
	{
		if (cmmd[tmp] == '\\' && cmmd[tmp + 1] == '\"')
			tmp++;
		tmp++;
	}
	if (cmmd[tmp] == '\"')
	{
		*qs = NO_QUOTE;
		*i = tmp;
		return (tmp);
	}
	return (-1);
}

int	simple_quo(char *cmmd, int *qs, int *i)
{
	int	tmp;

	tmp = *i + 1;
	*qs = SIMPLE_QUOTE;
	while (cmmd[tmp] && cmmd[tmp] != '\'')
	{
		if (cmmd[tmp] == '\\' && cmmd[tmp + 1] == '\'')
			tmp++;
		tmp++;
	}
	if (cmmd[tmp] == '\'')
	{
		*qs = NO_QUOTE;
		*i = tmp;
		return (tmp);
	}
	return (-1);
}

void	quote_mng(char *cmmd, int *quote_state, int *end, int *i)
{
	if (cmmd[*i - 1] != '\\')
	{
		if (cmmd[*i] == '\'')
			*end = simple_quo(cmmd, quote_state, i);
		else if (cmmd[*i] == '\"')
			*end = double_quo(cmmd, quote_state, i);
	}
}

int	std_char(t_list	**head, char *cmmd, int *sd)
{
	int	i;
	int	quote_state;

	i = 0;
	quote_state = NO_QUOTE;
	while (cmmd[i] && cmmd[i] != ' ' && quote_state == NO_QUOTE)
	{
		quote_mng(cmmd, &quote_state, &sd[END], &i);
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

/*** static void *token(t_list **head, char *cmmd, int start, int end) ***/
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
