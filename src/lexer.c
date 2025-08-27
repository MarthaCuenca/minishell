/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 20:15:31 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/08/19 13:04:32 by mcuenca-         ###   ########.fr       */
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
	split = ft_split(cmmd, ' ');
	while (split[i])
		printf("%s\n",split[i++]);
	return ;
}*/

t_bool	delete_empty_token(t_list **token_list)
{
	int		len;
	t_list	**tmp;
	t_list	*next;

	tmp = token_list;
	while (*tmp)
	{
		len = ft_strlen(((t_token *)(*tmp)->content)->token);
		if (len == 2
			&& (ft_strncmp(((t_token *)(*tmp)->content)->token, "\"\"", 2) == 0
			|| ft_strncmp(((t_token *)(*tmp)->content)->token, "\'\'", 2) == 0))
		{
			next = (*tmp)->next;
			ft_lstunlink(tmp, *tmp, del_t_token);
			*tmp = next;
		}
		else
			tmp = &(*tmp)->next;
	}
	return (TRUE);
}

t_list	*lexer(char *cmmd)
{
	t_list	*token_list;

	if (!cmmd)
		return (NULL);
	token_list = save_token(cmmd);
	if (!token_list)
		return (NULL);
	if (!split_one_token(&token_list))
		return (NULL);
	if (!delete_empty_token(&token_list))
		return (NULL);
	return (token_list);
}
