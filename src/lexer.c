/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 20:15:31 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/08/06 19:30:16 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

/*void	lexer(char *cmmd)
{
	//IDEA para TESTER probar todo esos casos de comillas:
	* "1 2 3"
	 * '1 2 3'
	 * '6'
	 * 1 "2 3"
	 * "1 2 '3'"
	 *'1 "2" 3'
	 * "123 123
	 * '123 123
	 * 123 123"
	 * 123 123'
	 * "'123 123"' <- eso no esta cerrado, espera ' para cerrarse 
	 * '"123 123'" <- eso no esta cerrado, espera " para cerrarse
	 * """123""" <- solo printea 123
	 * """123"" <- eso no esta cerrado, espera " para cerrarse 
	 * "123" "456" esto son 2 argumentos
	 * echo   "123"    "456" <- printea 123 456
	 * echo   "123    "    "    456" <- printea 123      456
	 * echo 123"456" <- printea 123456, si no hay espacios, entonces todo se fusiona en un solo argumento 
	 * echo 123"456"789 <- printea 123456789 
	 * echo te vi." <- espera a que cierre comillas !!!
	 * 1
	 * 12345
	 * 1 2 3 (con ' ' al final)
	 * 1 2 3(sin ' ' al final)
	 * hola mundo!
	 * $"jon
	 * 123""hola""tk
	 * 123""hola''tk
	 * 11"2222"3333"444"5555
	 * 11"2222"3333'444'5555
	 * abc"ddddd"
	 * "hola mundo"
	*MALLOC de 1 nodo, 
	*Verificar si las comillas estan cerradas: 
	*IDEA: default: bool = 0,
	*encontre comilla abierta, bool = 1 hasta que la cierres
	*si bool != 0, error, syntax error
	t_token	**tk*;
	char	**split;
	int	i;

	i = 0;
	*COMPROBAR SI TENGO COMILLAS ABIERTAS Y CERRADAS
	split = ft_split(cmmd, ' ');//echo "hola mundo!", aqui hay 3 str pero debe ser 2 tokens
	while (split[i])
		printf("%s\n",split[i++]);
	return ;
}*/

static const char *quote_to_str(t_quote q)
{
	switch (q)
	{
		case NO_QUOTE:
			return ("NO_QUOTE");
		case SIMPLE_QUOTE:
			return ("SIMPLE_QUOTE");
		case DOUBLE_QUOTE:
			return ("DOUBLE_QUOTE");
		case MIXED_QUOTE:
			return ("MIXED_QUOTE");
		default:
			return ("UNKNOWN_QUOTE");
	}
}

static const char *type_to_str(t_token_type tt)
{
	switch (tt)
	{
		case WORD:
			return ("WORD");
		case EXP:
			return ("EXP");
		case PIPE:
			return ("PIPE");
		case DIR_IN:
			return ("DIR_IN");
		case DIR_OUT:
			return ("DIR_OUT");
		case APPEND:
			return ("APPEND");
		case HEREDOC:
			return ("HEREDOC");
		default:
			return ("UNKNOWN_TYPE");
	}
}


t_list	*lexer(char *cmmd)
{
	t_list	*token_list;
	t_list	**tmp;
	t_list	*next;

	if (!cmmd)
		return (NULL);
	token_list = save_token(cmmd);
	if (!token_list)
		return (NULL);
	tmp = &token_list;
	while (*tmp)
	{
		if (ft_strlen(((t_token *)(*tmp)->content)->token) == 2)
		{	if (ft_strncmp(((t_token *)(*tmp)->content)->token, "\"\"", 2) == 0
				|| ft_strncmp(((t_token *)(*tmp)->content)->token, "\'\'", 2) == 0)
			{
				next = (*tmp)->next;
				ft_lstunlink(&token_list, *tmp, del_t_token);
				*tmp = next;
			}
		}
		else
			tmp = &(*tmp)->next;
	}
	tmp = &token_list;
	while (*tmp)
	{
		printf("[TOKEN]\n%s\n%i: %s\n%i: %s\n\n", ((t_token *)(*tmp)->content)->token, 
				((t_token *)((*tmp)->content))->quote_type,
				quote_to_str(((t_token *)((*tmp)->content))->quote_type), 
				((t_token *)((*tmp)->content))->type,
				type_to_str(((t_token *)((*tmp)->content))->type));
		tmp = &(*tmp)->next;
	}
	return (token_list);
}
