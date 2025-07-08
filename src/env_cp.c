/*PODER CREAR VARIABLES DE ENTORNO ->
* export + "HOLA=mundo"
* tomar la str, dividirla por el "="
* poner condiciones para el nombre_var "HOLA", nums validos, signos no validos
* poner condiciones para la def "mundo"
* poner al final
* env muestra las variables
* export (con argumentos) muesstra las variables alfabeticamente/ascii (1ro MAYUS, luego min)
*/
/*PODER ELIMINAR VARIABLES DE ENTORNO ->
* unset + "EL_NOMBRE_EXACTO_DE_LA_VAR"
*/

#include "env.h"//Cambiar a minishell.h
#include "libft.h"
void	ft_env_nd_free(t_env *nd)
{
	if (!nd)
		return ;
	free(nd->var);
	//free(nd->id);
	//free(nd->content);
	free(nd);
}

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
	//free(env_lst);//NO es memoria dinamica
}

t_env	*ft_env_nd_data(char *var)
{
	t_env	*new_nd;

	if (!var)
		return (NULL);
	new_nd = malloc(sizeof(t_env));//malloc(len * sizeof()) para inicializaciones inmediatas
								   //calloc(len, sizoef()) para ser seguro pero menos optimo
	if (!new_nd)
		return (NULL);
	new_nd->prev = NULL;
	new_nd->var = var;
	new_nd->next = NULL;
	return (new_nd);
}

t_env	*ft_env_array_to_list(char **env_ori)
{
	int		i;
	int		j;
	char	*new_var;
	t_env	*head;
	t_env	*new_nd;
	t_env	*tmp;

	if (!env_ori)
		return (NULL);
	i = 0;
	j = 0;
	head = NULL;
	new_nd = NULL;
	while (env_ori[j] != NULL)
		j++;
	printf("%i\n", j);//
	while (env_ori[i] && i < j)
	{
		new_var = ft_strdup(env_ori[i]);
		if (!new_var)
			return (ft_env_free(&new_nd), NULL);
		new_nd = ft_env_nd_data(new_var);
		//printf("%i *** %s\n", i, new_nd->var);//
		if (!new_nd)
			return (ft_env_free(&new_nd), NULL);
		if (!head)
			head = new_nd;
		if (tmp)
		{
			tmp->next = new_nd;
			new_nd->prev = tmp;
		}
		tmp = new_nd;
		/*tmp = new_nd;
		tmp->next = new_nd;//AQUI MUERE
		new_nd->prev = tmp;
		tmp = new_nd;*/
		i++;
	}
	return (head);
}

t_env	*ft_env_dup(char **env_ori)
{
	t_env	*env_cp;

	if (!env_ori)//Deberia comprobar que !*env_ori tambien es correcto o acepto NULL?
		return (NULL);
	env_cp = ft_env_array_to_list(env_ori);
	if (!env_cp)
		return (NULL);
	return (env_cp);
}
