/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 20:15:31 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/07/22 11:06:58 by mcuenca-         ###   ########.fr       */
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
	 * echo   "123    "    "456" <- printea 123      456
	 * echo 123"456" <- printea 123456
	 * echo 123"456"789 <- printea 123456789
	 * "
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

t_list	*lexer(char *cmmd)
{
	//int	count_tk;
	t_list	*token_list;
	t_list	*tmp;//

	if (!cmmd)
		return (NULL);
	/*count_tk = count_token(cmmd);	
	if (!count_tk)
		return (printf("SYNTAX ERROR\n"), NULL);//syntax error
	printf("%i\n", count_tk);*/
	token_list = save_token(cmmd);
	if (!token_list)
		return (NULL);
	tmp = token_list;//
	while (tmp)//QUIZAS ESTO HACE QE IMPRIMA ESPACIOS, PERO PORQUE NO HAY NADA??
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (token_list);
}
