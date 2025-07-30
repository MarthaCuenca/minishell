/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token_v2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:13:08 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/07/30 19:52:06 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

#define I 2
#define BOOL 3

//void	remove_quotes(char	*str)
/*void	remove_quotes(char	*str, char *c, int c_start)
{
	int		i;
	char	*start;
	char	*end;

	if (c[c_start] == '\'' || c[c_start] == '\"' || c[c_start - 1] == '$')
		return ;
	i = -1;
	start = ft_strchr(str, '\'');
	end = ft_strrchr(str, '\'');
	if (!start || !end)
	{
		start = ft_strchr(str, '\"');
		end = ft_strrchr(str, '\"');
	}
	while (str[++i])
	{
		if (&str[i] >= start)
		{
			if (str[i + 1] && &str[i + 1] >= end)
				str[i] = str[i + 2];
			else if (&str[i + 1] != end)
				str[i] = str[i + 1];
		}
	}
}*/

/*4.1.1: analizamos el tipo de token segun como empicen.
 * En el caso de EXP comprobamos que si es NO_QUOTE o DOUBLE_QUOTE pueda expandirse*/
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
	return (WORD);
}

/*4.1: creamos los datos de la struct t_token
 * tememos el token(str)
 * que tipo de comillas: NO_QUOTE, SIMPLE_QUOTE, DOUBLE_QUOTE
 * y el tipo de token*/
static t_token	*token_data(char *cmmd, int *util)
{
	char	*new_str;
	t_token	*new_token;

	//if (cmmd[util[START]] == '\'' || cmmd[util[START]] == '\"')
	//	new_str = ft_substr(cmmd, util[START] + 1, util[END] - util[START] - 1);
	//else
	new_str = ft_substr(cmmd, util[START], (util[END] - util[START] + 1));
	if (!new_str)
		return (NULL);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (free(new_str), NULL);
	new_token->token = new_str;
	if (cmmd[util[START]] == '\'')
		new_token->quote_type = SIMPLE_QUOTE;
	else if (cmmd[util[START]] == '\"')
		new_token->quote_type = DOUBLE_QUOTE;
	else
		new_token->quote_type = NO_QUOTE;
	new_token->type = token_type(new_token);
	/*if (ft_strchr(new_str, '\'') || ft_strchr(new_str, '\"'))
		remove_quotes(new_token->token, cmmd, util[START]);*/
	/*if (cmmd[util[START]] == '\'' || cmmd[util[START]] == '\"')
		remove_quotes(new_token->token);*/
	return (new_token);
}

/*4: creamos el token en forma de t_list, que su content es un t_token
 * si exite algun token previo de engancha al final
 * si no pues el el primero
 * reiniciamos START y END*/
static void	*token(t_list **head, char *cmmd, int *util)
{
	t_list	*new_nd;
	t_token	*nd_data;

	nd_data = token_data(cmmd, util);
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
	util[START] = -1;
	util[END] = -1;
	return (*head);
}

/*3.3.3: marcamos el inicio de una substr
 * con la BOOL impedimos que vuelva a entrar aqui y no crear nuevos inicios*/
static void	no_quo_stdchr_3(char *cmmd, int *util)
{
	if (cmmd[util[I]] != ' ' && util[BOOL] == TRUE)
	{
		util[START] = util[I];
		util[BOOL] = FALSE;
	}
}

/*3.3.2: si existe una char solo antes de "\0"*/
static void	no_quo_stdchr_2(char *cmmd, int *util)
{
	if (cmmd[util[I]] != ' ')
	{
		if (util[BOOL] == TRUE)
		{
			util[START] = util[I];
			util[BOOL] = FALSE;
		}
		util[END] = util[I];
		util[BOOL] = TRUE;
	}
}

/*3.1.1: marco el final de una str*/
static void	no_quo_stdchr_1(int *util)
{
	util[END] = util[I] - 1;
	util[BOOL] = TRUE;
}

/*3: estamos es token SIN comillas
 * aqui verificamos que hemos encontrado una comilla o no
 * * para marcar el inicio de una substr, solo si:
 * * *si el char anterior es ' '
 * * *si el char anterior es "\'"
 * * *si el char anterior es "\""
 * * si no solo activamos el estado coorespondiente para que str itere
 * ante un char normal hay otras funciones(3.3)
 * * si es ' ' (3.3.1)
 * * si el siguiente es "\0" (3.3.2)
 * * cualquier otro char (3.3.3)*/
static void	no_quote(char *cmmd, int *quote_state, int *util)
{
	if (cmmd[util[I]] == '\'')
	{
		if (cmmd[util[I] - 1] == ' '
			|| !cmmd[util[I] - 1] || cmmd[util[I] - 1] == '\'')
			util[START] = util[I];
		*quote_state = SIMPLE_QUOTE;
	}
	else if (cmmd[util[I]] == '\"')
	{
		if (cmmd[util[I] - 1] == ' '//|| cmmd[util[I] - 1] == '$' 
			|| !cmmd[util[I] - 1] || cmmd[util[I] - 1] == '\"')
			util[START] = util[I];
		*quote_state = DOUBLE_QUOTE;
	}
	else
	{
		if (cmmd[util[I]] == ' ' && util[BOOL] == FALSE)
			no_quo_stdchr_1(util);
		else if (!cmmd[util[I] + 1])
			no_quo_stdchr_2(cmmd, util);
		else
			no_quo_stdchr_3(cmmd, util);
	}
	util[I]++;
}

/*3: estamos dentro de un token-comilla-SIMPLE
 * hasta cerrar es 1 solo token
 * * NO encuentra "\'" para cerrar no cambia el estado, esto no hara la lista
 * * SI encuentra "\'" cambiara el quote_state, saltara la comilla y comprobara:
 * * *si despues hay ' ': da por finalizado el token
 * * *si despues hay "\0": da por finalizado el token
 * * *si despues hay "\"": da por finalizado el token
 * * *con cualquier otro char el token no finaliza
 * */
static void	sim_quote(char *cmmd, int *quote_state, int *util)
{
	while (cmmd[util[I]] && cmmd[util[I]] != 39)
		util[I]++;
	if (cmmd[util[I]] == 39)
	{
		*quote_state = NO_QUOTE;
		if (cmmd[util[I] + 1] == ' '
			|| !cmmd[util[I] + 1] || cmmd[util[I] + 1] == '\'')
		{
			util[END] = util[I];
			util[BOOL] = TRUE;
		}
		util[I]++;
	}
}
/*3: estamos dentro de un token-comilla-DOBLE
 * hasta cerrar es 1 solo token
 * * NO encuentra "\"" para cerrar no cambia el estado, esto no hara la lista
 * * SI encuentra "\"" cambiara el quote_state, saltara las comillas y comprobara:
 * * *si despues hay ' ': da por finalizado el token
 * * *si despues hay "\0": da por finalizado el token
 * * *si despues hay "\"": da por finalizado el token
 * * *con cualquier otro char el token no finaliza
 * */
static void	dou_quote(char *cmmd, int *quote_state, int *util)
{
	while (cmmd[util[I]] && cmmd[util[I]] != 34)
		util[I]++;
	if (cmmd[util[I]] == 34)
	{
		*quote_state = NO_QUOTE;
		if (cmmd[util[I] + 1] == ' '
			|| !cmmd[util[I] + 1] || cmmd[util[I] + 1] == '\"')
		{
			util[END] = util[I];
			util[BOOL] = TRUE;
		}
		util[I]++;
	}
}
/*2: opciones para cada tipo de char:
 * * si estamos en un "\'"
 * * si estamos en un "\""
 * * si no estamos dentro de un token-comilla
 * tambien comprobamos que tengo un valor de START y END para crea un nuevo token*/
int	during_cmmd_loop(t_list **head, char *cmmd, int *quote_state, int *util)
{
	if (*quote_state == SIMPLE_QUOTE)
		sim_quote(cmmd, quote_state, util);
	else if (*quote_state == DOUBLE_QUOTE)
		dou_quote(cmmd, quote_state, util);
	else
		no_quote(cmmd, quote_state, util);
	if (util[START] != -1 && util[END] != -1)
	{
		token(head, cmmd, util);
		if (!*head)
			return (FALSE);
	}
	return (TRUE);
}
/*1: Vamos iterando el cmmd(que es un str).
 * En las VARIALES hay:
 * * quote_state que indica si estamos con un token normal o con comillas
 * * util[START] indica el comienzo de la substr
 * * util[END] indica el final de la substr
 * * util[I] para poder iterar la str y guarda el valor de START y END
 * * util[BOOL] la usamos para ver si ya podemos reiniciar START y END, para caso de +1 ' '*/
t_list	*save_token(char *cmmd)
{
	int		quote_state;
	int		util[4];
	t_list	*head;

	if (!cmmd)
		return (0);
	quote_state = NO_QUOTE;
	util[START] = -1;
	util[END] = -1;
	util[BOOL] = TRUE;
	util[I] = 0;
	head = NULL;
	while (cmmd[util[I]])
		if (!during_cmmd_loop(&head, cmmd, &quote_state, util))
			break ;
	if (quote_state != NO_QUOTE)
		return (ft_lstclear(&head, &del_t_token), NULL);
	return (head);
}
