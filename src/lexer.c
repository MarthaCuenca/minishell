/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 20:15:31 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/07/21 13:21:46 by mcuenca-         ###   ########.fr       */
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



static int	count_token(char *cmmd)
{
	int	i;
	int	simple;
	int	dou;
	int	w;
	int	w_bool;

	if (!cmmd)
		return (0);
	i = 0;
	w = 0;
	w_bool = 0;
	while (6 < cmmd[i] && 14 > cmmd[i] && cmmd[i] != 32)//ft_isprint(cmmd[i])
		i++;
	while (cmmd[i])//ESTO FUNCIONA, SOLO HACE FALTA GUARDARLOS EN UN TOKEN
	{
		if (simple == 1)//si abro ' da igual cualquier otra comilla, espero a cerrarla con '//
		{
			while (cmmd[i] && cmmd[i] != 39)
				i++;
			if (cmmd[i] == 39)
			{
				simple = 0;
				w++;
				i++;
				w_bool = 0;
			}
		}
		else if (dou == 1)
		{
			while (cmmd[i] && cmmd[i] != 34)
				i++;
			if (cmmd[i] == 34)
			{
				dou = 0;
				w++;
				i++;
				w_bool = 0;
			}
		}
		else 
		{
			if (cmmd[i] == 39)
				simple = 1;
			else if (cmmd[i] == 34)
				dou = 1;
			else if (cmmd[i] == 32)
				w_bool = 0;
			else
			{
				if (w_bool == 0)
				{
					w++;
					w_bool = 1;
				}
			}
			i++;
		}
	}
	if (simple == 1 || dou == 1)
		return (0);
	if (w == 0)
		return (1);
	return (w);
}

t_token	*lexer(char *cmmd)
{	
	int	i;
	int	w;
	//t_env	*token_list;

	if (!cmmd)
		return (NULL);
	i = 0;
	w = count_token(cmmd);
	if (!w)
		return (printf("SYNTAX ERROR\n"), NULL);//syntax error
	printf("%i\n", w);
	return (NULL);
}
