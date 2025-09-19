/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_v2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:13:52 by mcuenca-          #+#    #+#             */
/*   Updated: 2025/09/19 14:03:44 by mcuenca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	env_nd_free(t_env *nd)
{
	if (!nd)
		return ;
	free(nd->var);
	free(nd);
}

void	env_free(t_env **env_lst)
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
}

t_env	*env_nd_data(char *var)
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

int	env_array_to_list_2(t_env **new_nd, t_env **head, char *env_ori)
{
	t_env	*tmp;

	tmp = *new_nd;
	*new_nd = ft_env_nd_data(env_ori);
	if (!*new_nd)
		return (ft_env_free(new_nd), FALSE);
	if (!*head)
		*head = *new_nd;
	if (tmp)
	{
		tmp->next = *new_nd;
		(*new_nd)->prev = tmp;
	}
	return (TRUE);
}

t_env	*env_array_to_list(char **env_ori)
{
	int		i;
	t_env	*head;
	t_env	*new_nd;

	if (!env_ori)
		return (NULL);
	i = 0;
	head = NULL;
	new_nd = NULL;
	while (env_ori[i])
		if (!ft_env_array_to_list_2(&new_nd, &head, env_ori[i++]))
			return (ft_env_free(&new_nd), NULL);
	return (head);
}

t_env	*env_dup(char **env_ori)
{
	t_env	*env_cp;

	if (!env_ori)
		return (NULL);
	env_cp = ft_env_array_to_list(env_ori);
	if (!env_cp)
		return (NULL);
	return (env_cp);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_cp;
	t_env	*tmp;

	(void)argc;
	(void)argv;
	env_cp = ft_env_dup(env);
	if (!env_cp)
		return (1);
	tmp = env_cp;
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
	ft_env_free(&env_cp);
	return (0);
}
