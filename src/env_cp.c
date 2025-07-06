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

void	ft_2p_free(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char	**ft_p2_dup(char **arr_ori)
{
	int		i;
	int		j;
	char	**cp;

	if (!arr_ori)
		return (NULL);
	i = 0;
	j = 0;
	while (arr_ori[j] != NULL)
		j++;
	//printf("%i\n", j);//
	cp = malloc((j + 1) * sizeof(char *));//malloc(len * sizeof()) para inicializaciones inmediatas
										  //calloc(len, sizoef()) para ser seguro pero menos optimo
	while (i < j)
	{
		cp[i] = ft_strdup(arr_ori[i]);
		if (!cp[i])
			ft_2p_free(cp);
		i++;
	}
	cp[i] = NULL;
	return (cp);
}

char	**ft_env_dup(char **env_ori)
{
	char	**env_cp;

	if (!env_ori)//Derebia comprobar que !*env_ori tambien es correcto o acepto NULL?
		return (NULL);
	env_cp = ft_p2_dup(env_ori);
	if (!env_cp)
		return (NULL);
	return (env_cp);
}

//BORRAR
/*int	main(int argc, char **argv, char **env)
{
	int		j;
	char	**env_cp;

	j = 0;
	env_cp = ft_env_dup(env);
	if (!env_cp)
		return (1);
	while (env_cp[j] != NULL)//
		printf("%s\n", env_cp[j++]);//
	ft_2p_free(env_cp);//
	return (0);
}*/
