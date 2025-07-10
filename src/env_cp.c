/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:13:52 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/07/10 19:43:28 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*PODER CREAR VARIABLES DE ENTORNO ->
* export + "HOLA=mundo"
* tomar la str, dividirla por el "="
* poner condiciones para el nombre_var "HOLA", nums validos, signos no validos
* poner condiciones para la def "mundo"
* poner al final
* env muestra las variables
* export (con argumentos):
* muestra las variables alfabeticamente/ascii (1ro MAYUS, luego min)*/

/*PODER ELIMINAR VARIABLES DE ENTORNO -> unset + "EL_NOMBRE_EXACTO_DE_LA_VAR"*/

/*RECUERDA SIEMPRE ACTUALIZAR EL ENVIRONMENT 
CUANDO HAGAS CUALQUIER COSAS Y/O LO BUILT-INS DE env I export*/

#include "env.h"/*Cambiar a minishell.h*/
#include "libft.h"

/*Esta funcion sirve para hacer free de todos los miembros del nodo que ocupen
memoria dinamica (creados con malloc). Solo "var" es un duplicado (malloc)*/
void	ft_env_nd_free(t_env *nd)
{
	if (!nd)
		return ;
	free(nd->var);
	free(nd);
}

/*Esta funcion sirve para liberar la lista doble enlazada, pasando por cada nodo
y por cada miembro de cada nodo. 
NO hago free de t_env ** porque es memoria estatica creada en el main.*/
void	ft_env_free(t_env **env_lst)
{
	size_t	i;
	t_env	*tmp;

	i = 0;
	tmp = *env_lst;
	while (*env_lst)
	{
		tmp = (*env_lst)->next;
		ft_env_nd_free(*env_lst);
		*env_lst = tmp;
	}
	/*free(env_lst);//NO es memoria dinamica*/
}

/*Aqui voy crando los datos de cada miembro de un nodo.
malloc(len * sizeof()) para inicializaciones inmediatas
calloc(len, sizoef()) para ser seguro pero menos optimo*/
t_env	*ft_env_nd_data(char *var)
{
	t_env	*new_nd;
	char	*tmp;

	if (!var)
		return (NULL);
	new_nd = malloc(sizeof(t_env));
	if (!new_nd)
		return (NULL);
	new_nd->prev = NULL;
	new_nd->var = ft_strdup(var);
	if (!new_nd->var)
		return (NULL);
	tmp = ft_strchr(new_nd->var, '=');
	new_nd->content = tmp + 1;
	new_nd->id_len = (tmp - 1) - new_nd->var;
	new_nd->next = NULL;
	return (new_nd);
}

/*2da parte de donde itero para crear la lista doble enlazada.
return int: lo hago funcionar como un bolean, si sale bien 1, sino 0*/
int	ft_env_array_to_list_2(t_env **new_nd, t_env **head, char *env_ori)
{
	t_env	*tmp;

	tmp = *new_nd;
	*new_nd = ft_env_nd_data(env_ori);
	if (!*new_nd)
		return (ft_env_free(new_nd), 0);
	if (!*head)
		*head = *new_nd;
	if (tmp)
	{
		tmp->next = *new_nd;
		(*new_nd)->prev = tmp;
	}
	return (1);
}

/*Creo la lista doble enlazada de environment,
teniendo en cuenta que es el environment orignal es un char**
y nosotros queremos una lista.*/
t_env	*ft_env_array_to_list(char **env_ori)
{
	int		i;
	int		j;
	t_env	*head;
	t_env	*new_nd;

	if (!env_ori)
		return (NULL);
	i = 0;
	j = 0;
	head = NULL;
	new_nd = NULL;
	while (env_ori[j] != NULL)
		j++;
	while (env_ori[i] && i < j)
		if (!ft_env_array_to_list_2(&new_nd, &head, env_ori[i++]))
			return (ft_env_free(&new_nd), NULL);
	return (head);
}

/*Esta funcion es como un "init_env_dup", solo va llamando a las funciones 
 para poder hacer el resultado final.
 SI TODO SALE BIEN, ANTES DE CERRAR EL PROGRAMA (exit) LIBERA EL ENV*/
t_env	*ft_env_dup(char **env_ori)
{
	t_env	*env_cp;

	if (!env_ori)
		return (NULL);
	env_cp = ft_env_array_to_list(env_ori);
	if (!env_cp)
		return (NULL);
	return (env_cp);
}
