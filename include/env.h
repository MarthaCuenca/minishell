/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:12:38 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/07/10 18:25:08 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include <stdio.h>
#include <stdlib.h>
/*	*"var": duplicado de la env_var original
	*"id_len": el espacio que ocupa el nombre de la variable
por ej.:  LESS=-R, ocupa 4, SHLVL=1, ocupa 5, PWD=..., ocupa 3
para que es esto? pues cuando haya que buscar PWD para sobreescribilar/modificarla
habremos de comparar todas las variables hasta encontrar PWD para poderla cambiar
para mejorar el redimiento pues solo analizaremos si coninciden sus id_len,
y si coinciden pues haremos un ft_strncmp
    *"content": donde empieza el contenido de una variable, 
tambien sirve para calcular id_len
	*"i": numero de indice, por si lo hago alfabeticamente el orden de las vars */
typedef struct s_env
{
	struct s_env	*prev;
	char			*var;
	int				id_len;
	char			*content;
	int				i;
	struct s_env	*next;
}	t_env;

t_env	*ft_env_dup(char **env_ori);
void    ft_env_free(t_env **env_lst);
//char	**ft_env_dup(char **env_ori);

#endif
